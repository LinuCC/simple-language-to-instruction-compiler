%{     /* PARSER */

#include "parser.hh"
#include "scanner.hh"
#include "../tac.hh"

// Verlinke den C++ Flex Scanner mit dem Bison Parser mit diesem Alias
#define yylex driver.scanner->yylex
%}

%code requires
{
  #include <iostream>
  #include "driver.hh"
  #include "location.hh"
  #include "position.hh"
  #include "../tac.hh"
}

%code provides
{
  namespace slang_parser
  {
    // Forward declaration of the FrontendDriver class
    class FrontendDriver;

    inline void
    yyerror (const char* msg)
    {
      std::cerr << msg << std::endl;
    }
  }

  
}

%require "3.2"
%language "C++"
%locations
%defines
%debug
%define api.namespace {slang_parser}
%define api.parser.class {Parser}
%param {FrontendDriver &driver}
%define parse.error verbose

/**
 * Der Typ, mit dem wir Daten durch den Syntaxbaum reichen
 *
 *  NOTE: Bei Übergabe von Zeigern direkt aus den union Daten nicht `strdup` vergessen! 
 */
%union
{
  /* Ein Integer-Wert für Nummer-Konstanten */
  int int_val;
  /* Ein String-Wert für Identifier wie Variablennamen oder Funktionsnamen */
  char* str_val;

  /* Speichert Werte von Typen */
  struct {
    slicc_tac::SymbolType symbol_type;
    /* Ein Array muss eine Anzahl an Elementen angeben, die hier gespeichert werden */
    int arr_element_amount;
  } type_val;
}

/* 
 * Tokens für den Lexer definieren (werden in `scan.ll` referenziert)
 */
%token TOK_EOF 0
// Tokens für die Kontrollstruktur
%token TOK_PROGRAM TOK_IF TOK_ELSE TOK_FOR TOK_FUNC TOK_RETURN
// Tokens für Typen
%token TOK_INT TOK_INT_ARRAY TOK_VOID TOK_REF
/*
 * Für Daten, die aus den Token direkt vom Lexer kommen, müssen wir die Typen definieren.
 */
%type<int_val> TOK_INT_ARRAY
%token <int_val> TOK_INT_LITERAL
%token <str_val> TOK_ID
// Klammern
%token TOK_LBRACKET TOK_RBRACKET TOK_LPAREN TOK_RPAREN TOK_LBRACE TOK_RBRACE
// Tokens für einzelne Operationen
%token TOK_SEMICOLON TOK_COMMA
%token TOK_ASSIGN 
%token TOK_PLUS TOK_MINUS TOK_MUL TOK_DIV
%token TOK_EQ TOK_NEQ TOK_LT TOK_LEQ TOK_GT TOK_GEQ

/**
 * Der Parser muss wissen, welche Regeln welche Typen aus der %union benutzen, um den Rückgabewert $$ zu setzen.
 * Das definieren wir mit %type.
 * So wird hier z.B. definiert, dass der Typ `type` den Typ `type_val` aus der %union benutzt.
 * Damit ist der Typ von `$$` vom Code in der Regel `type` ein `type_val`, und es kann z.B. `$$.symbol_type` oder `$$.arr_element_amount` gesetzt werden.
 */
%type<type_val> type

/* Das erste Symbol, mit dem der Syntaxparser gestartet wird */
%start main

%%

main:
    program |
    program func_def_list

/* Wir erwarten zuerst ein "program { ... }" */
program:
  TOK_PROGRAM TOK_ID[prog_name] block
    {
      /* Setze für alle Symboltabelleneinträge, die in dem Block definiert wurden, den Programmnamen als parent */
      char* parent = strdup($prog_name);
      driver.add_symbol_table_entry(
        parent,
        slicc_tac::SymbolType::PROGRAM,
        0,
        0,
        strdup("main"),
        0,
        false
      );
      driver.identify_parent(parent);
    }
  ;

/* 
 * Ein Block, der lokale Definitionen und Ausführungen enthält.
 * Hier werden Variablen definiert und Aufrufe durchgeführt.
 * Wir beschränken das definieren von Variablen auf den Anfang, bevor Aufrufe und Kalkulationen durchgeführt werden.
 */
block:
      TOK_LBRACE block_body TOK_RBRACE
    ;
/* 
 * Ein Block, der lokale Definitionen und Ausführungen enthält.
 */
block_body:
  variable_list statement_list
  | statement_list
    ;

variable_list: 
  variable_declaration 
  | variable_declaration variable_list
  ;

/* Deklaration einer Variable, z.B. int num = 0; */
variable_declaration:
 
  type TOK_ID[name] TOK_SEMICOLON {
      std::cout << "PARSER: Variable declaration: " << $name << " Type: " << $type.symbol_type << std::endl;
      char* name = strdup($name);
      driver.add_symbol_table_entry(
        name,
        $type.symbol_type,
        0,
        $type.arr_element_amount,
        NULL, // Parent nicht bekannt
        0,
        false
      );

      // In arg1 ist die `0` für int_val der tatsächliche Wert
      TacArg arg1 = { NULL, NULL, 0, };
      // arg2 wird nicht benutzt
      TacArg arg2 = { NULL, NULL, 0, };
      driver.add_tac_entry(
        TacOperation::ASSIGN,
        arg1,
        arg2,
        name
      );
    }
  | type TOK_ID[name] TOK_ASSIGN TOK_INT_LITERAL[value] TOK_SEMICOLON {
      std::cout << "PARSER: Variable declaration: " << $name << " Type: " << $type.symbol_type << std::endl;
      char* name = strdup($name);
      driver.add_symbol_table_entry(
        name,
        $type.symbol_type,
        0,
        0,
        NULL, // Parent nicht bekannt
        0,
        false
      );
      driver.add_tac_entry(
        TacOperation::ASSIGN,
        { NULL, NULL, $value, },
        { NULL, NULL, 0, },
        name
      );
    }
  ; 

/* Eine Liste an Ausführungen */
statement_list:
  statement
  | statement statement_list
  ;

/* Ausführungen */
statement:
  statement_assignment TOK_SEMICOLON
  | if
  | for
  | func_call TOK_SEMICOLON
  | TOK_RETURN expression TOK_SEMICOLON
  ;

/* Eine Zuweisung, z.B. num = num + 5; */
statement_assignment:
  TOK_ID TOK_ASSIGN expression
  | TOK_ID TOK_LBRACKET TOK_INT_LITERAL TOK_RBRACKET TOK_ASSIGN expression
  | TOK_ID TOK_LBRACKET TOK_ID TOK_RBRACKET TOK_ASSIGN expression
  ;

/* Der rechte Teil einer Zuweisung */
expression:
  TOK_INT_LITERAL
  | TOK_ID
  | func_call
  | expression TOK_PLUS expression
  | expression TOK_MINUS expression
  | expression TOK_MUL expression
  | expression TOK_DIV expression
  | expression TOK_EQ expression
  | expression TOK_NEQ expression
  | expression TOK_LT expression
  | expression TOK_LEQ expression
  | expression TOK_GT expression
  | expression TOK_GEQ expression
  | TOK_LPAREN expression TOK_RPAREN
  ;

comparison_operator:
  TOK_EQ
  | TOK_NEQ
  | TOK_LT
  | TOK_LEQ
  | TOK_GT
  | TOK_GEQ
  ;

compare_expression:
  TOK_ID comparison_operator TOK_ID
  | TOK_ID comparison_operator TOK_INT_LITERAL
  | TOK_INT_LITERAL comparison_operator TOK_ID
  | TOK_INT_LITERAL comparison_operator TOK_INT_LITERAL
  ;

/* 
 * Ein if block, mit optionalem else
 */
if:
      TOK_IF TOK_LPAREN compare_expression TOK_RPAREN block
    | TOK_IF TOK_LPAREN compare_expression TOK_RPAREN block TOK_ELSE block
    ;

/*
 * Eine for-Schleife mit Abbruchbedingung und Zuweisung einer Variable mit jedem Durchlauf
 */
for:
      TOK_FOR TOK_LPAREN compare_expression TOK_SEMICOLON statement_assignment TOK_RPAREN block
    ;


/*
 * Mögliche Typendefinitionen. Wir erlauben momentan nur `int` und ein Array davon
 */
type:
  TOK_INT { 
    $$.symbol_type = slicc_tac::SymbolType::INT; 
    $$.arr_element_amount = 0;
  } 
  | TOK_INT_ARRAY TOK_INT_LITERAL[elem_count] TOK_RBRACKET { 
    $$.symbol_type = slicc_tac::SymbolType::INT_ARRAY; 
    $$.arr_element_amount = $2;
  }
  ;


/* Ein Funktionsaufruf mit Argumenten */
func_call:
  TOK_ID TOK_LPAREN func_args TOK_RPAREN
  ;

func_args:
  expression
  | expression TOK_COMMA func_args
  ;

func_def_list:
  func_def
  | func_def func_def_list 
  ;

func_def:
    TOK_FUNC type     TOK_ID[func_name] TOK_LPAREN func_args_def TOK_RPAREN block
      {
        driver.add_symbol_table_entry(
          strdup($func_name),
          slicc_tac::SymbolType::FUNCTION,
          0,
          0,
          strdup("main"),
          0,
          false
        );
        driver.identify_parent(strdup($func_name));
      }
  | TOK_FUNC TOK_VOID TOK_ID[func_name] TOK_LPAREN func_args_def TOK_RPAREN block
      {
        driver.add_symbol_table_entry(
          strdup($func_name),
          slicc_tac::SymbolType::FUNCTION,
          0,
          0,
          strdup("main"),
          0,
          false
        );
        driver.identify_parent(strdup($func_name));
      }
  ;

func_args_def:
  func_arg_def
  | func_arg_def TOK_COMMA func_args_def
  ;

func_arg_def:
  type TOK_ID
  | TOK_REF type TOK_ID
  ;

%%

/*
 * Simple Fehlerbehandlung für den Parser
 */
namespace slang_parser
{
    void Parser::error(const location& l, const std::string& m)
    {
        std::cerr << l << ": " << m << std::endl;
        driver.error = (driver.error == 127 ? 127 : driver.error + 1);
    }
}

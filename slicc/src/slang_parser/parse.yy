%{     /* PARSER */

#include "parser.hh"
#include "scanner.hh"

#define yylex driver.scanner_->yylex
%}

%code requires
{
  #include <iostream>
  #include "driver.hh"
  #include "location.hh"
  #include "position.hh"
}

%code provides
{
  namespace slang_parser
  {
    // Forward declaration of the Driver class
    class Driver;

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
%parse-param {Driver &driver}
%lex-param {Driver &driver}
%define parse.error verbose

/**
 * Der Typ, mit dem wir Daten von Flex zu Bison übergeben.
 */
%union
{
  /* Ein Integer-Wert für Nummer-Konstanten */
  int int_val;
  /* Ein String-Wert für Identifier wie Variablennamen oder Funktionsnamen */
  char* str_val;
}

/* 
 * Tokens für den Lexer definieren (werden in `scan.ll` referenziert)
 */
%token TOK_EOF 0
// Tokens für die Kontrollstruktur
%token TOK_PROGRAM TOK_IF TOK_ELSE TOK_FOR TOK_FUNC
// Tokens für Typen
%token TOK_INT TOK_INT_ARRAY TOK_VOID
// Tokens mit Daten
%token <int_val> TOK_INT_LITERAL
%token <str_val> TOK_ID
// Klammern
%token TOK_LBRACKET TOK_RBRACKET TOK_LPAREN TOK_RPAREN TOK_LBRACE TOK_RBRACE
// Tokens für einzelne Operationen
%token TOK_SEMICOLON
%token TOK_ASSIGN 
%token TOK_PLUS TOK_MINUS TOK_MUL TOK_DIV
%token TOK_EQ TOK_NEQ TOK_LT TOK_LEQ TOK_GT TOK_GEQ

/* Das erste Symbol, mit dem der Syntaxparser gestartet wird */
%start program

%%

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


/* Wir erwarten zuerst ein "program { ... }" */
program:
  TOK_PROGRAM block
  ;

variable_list: 
  variable_declaration 
  | variable_declaration variable_list
  ;

/* Deklaration einer Variable, z.B. int num = 0; */
variable_declaration:
  type TOK_ID TOK_ASSIGN TOK_INT_LITERAL TOK_SEMICOLON
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
  ;

/* Eine Zuweisung, z.B. num = num + 5; */
statement_assignment:
  TOK_ID TOK_ASSIGN expression
  ;

/* Der rechte Teil einer Zuweisung */
expression:
  TOK_INT_LITERAL
  | TOK_ID
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
  TOK_INT | TOK_INT_ARRAY
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
        driver.error_ = (driver.error_ == 127 ? 127 : driver.error_ + 1);
    }
}

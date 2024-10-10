%{

#include "parser.hh"
#include "scanner.hh"
#include "driver.hh"
#include "strdup.hh"

/*  Defines some macros to update locations */
#define STEP()                                      \
  do {                                              \
    yylloc->step ();                      \
  } while (0)

#define COL(Col)				                            \
  yylloc->columns (Col)

#define LINE(Line)				                          \
  do{						                                    \
    yylloc->lines (Line);		              \
 } while (0)

#define YY_USER_ACTION				                      \
  COL(yyleng);

/**
 * Vorgefertigte Tokens von flex' slang_parser::Parser::token abkürzen
 * 
 * Die Tokens werden mit Bison in der Datei `parse.yy` referenziert und dadurch hier rein generiert.
 * Um weitere Tokens im Lexer zu parsen, müssen diese in `parse.yy` referenziert werden.
 */
typedef slang_parser::Parser::token token;
typedef slang_parser::Parser::token_type token_type;

#define yyterminate() return token::TOK_EOF

%}

%option debug
%option c++
%option noyywrap
%option never-interactive
%option yylineno
%option nounput
%option batch
%option prefix="ParserGen"

/*
%option stack
*/

/* Abbreviations.  */

blank   [ \t]+
eol     [\n\r]+
digit   [0-9]
id      [a-z][a-z0-9_]*

%%

 /* The rules.  */
%{
  STEP();
%}

  /* Tokens für die Kontrollstruktur */
"program"          { return token::TOK_PROGRAM; }
"if"          { return token::TOK_IF; }
"else"          { return token::TOK_ELSE; }
"for"          { return token::TOK_FOR; }
"func"          { return token::TOK_FUNC; }
"return"           {return  token::TOK_RETURN; }
  /* Tokens für Typen */
"void"              { return token::TOK_VOID; }
"int"              { return token::TOK_INT; }
"ref"              { return token::TOK_REF; }
"int["             { return token::TOK_INT_ARRAY; }
  /* Tokens für Konstanten */
{digit}+           { 
  /* Übersetzt die gelesenen Zeichen zu einer Nummer und speichert sie in das Objekt dass an Bison übergeben wird */
  yylval->int_val = atoi(yytext); 
  return token::TOK_INT_LITERAL; 
}
  /* Umschliessende Klammern */
"{"                { return token::TOK_LBRACE; }
"}"                { return token::TOK_RBRACE; }
"("                { return token::TOK_LPAREN; }
")"                { return token::TOK_RPAREN; }
  /* Momentan nur für Arrays benutzt */
"["                { return token::TOK_LBRACKET; } 
"]"                { return token::TOK_RBRACKET; }
  /* Mehr Zeichen */
";"                { return token::TOK_SEMICOLON; }
","                { return token::TOK_COMMA; }
"="                { return token::TOK_ASSIGN; }
  /* Operatoren */
"+"                { return token::TOK_PLUS; }
"-"                { return token::TOK_MINUS; }
"*"                { return token::TOK_MUL; }
"/"                { return token::TOK_DIV; }

  /* Vergleiche */
"=="               { return token::TOK_EQ; }
"!="               { return token::TOK_NEQ; }
"<="               { return token::TOK_LEQ; }
">="               { return token::TOK_GEQ; }
"<"                { return token::TOK_LT; }
">"                { return token::TOK_GT; }

  /* Jede Zeile die mit "/" und "*" beginnt wird ignoriert, wir überspringen diese einfach */
"//".*     { }

{id}         { 
  yylval->str_val = strdup(yytext); /* Don't forget to `strdup`! */
  return token::TOK_ID; 
}

  /* Leerzeichen */
{blank}        STEP();
{eol}          LINE(yyleng);


.             {
                std::cerr << *yylloc << " Unerwartetes Token : "
                                              << *yytext << std::endl;
                driver.error = (driver.error == 127 ? 127
                                : driver.error + 1);
                /* Wenn wir das Token nicht parsen können, überspringen wir es einfach */
                STEP ();
              }

%%


/*

   CUSTOM C++ CODE

*/

namespace slang_parser
{

    Scanner::Scanner()
    : ParserGenFlexLexer()
    {
    }

    Scanner::~Scanner()
    {
    }

    void Scanner::set_debug(bool b)
    {
        yy_flex_debug = b;
    }
}

#ifdef yylex
# undef yylex
#endif

int ParserGenFlexLexer::yylex()
{
  std::cerr << "call ParserGenpitFlexLexer::yylex()!" << std::endl;
  return 0;
}

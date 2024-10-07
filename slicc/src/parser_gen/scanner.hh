#ifndef SCANPIT_HH_
#define SCANPIT_HH_

#include "parser.hh"

#ifndef YY_DECL
#define YY_DECL                                                                \
  parser_gen::Parser::token_type parser_gen::Scanner::yylex(                   \
      parser_gen::Parser::semantic_type *yylval,                               \
      parser_gen::Parser::location_type *yylloc, parser_gen::Driver &driver)
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer parseFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

namespace parser_gen {
class Scanner : public parseFlexLexer {
public:
  Scanner();

  virtual ~Scanner();

  virtual Parser::token_type yylex(Parser::semantic_type *yylval,
                                   Parser::location_type *yylloc,
                                   Driver &driver);

  void set_debug(bool b);
};
} // namespace parser_gen

#endif // SCANPIT_HH_

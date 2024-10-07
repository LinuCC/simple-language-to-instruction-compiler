#ifndef SCANPIT_HH_
#define SCANPIT_HH_

#include "parser.hh"

#ifndef YY_DECL
#define YY_DECL                                                                \
  slang_parser::Parser::token_type slang_parser::Scanner::yylex(               \
      slang_parser::Parser::semantic_type *yylval,                             \
      slang_parser::Parser::location_type *yylloc,                             \
      slang_parser::Driver &driver)
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer ParserGenFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

namespace slang_parser {
class Scanner : public ParserGenFlexLexer {
public:
  Scanner();

  virtual ~Scanner();

  virtual Parser::token_type yylex(Parser::semantic_type *yylval,
                                   Parser::location_type *yylloc,
                                   Driver &driver);

  void set_debug(bool b);
};
} // namespace slang_parser

#endif // SCANPIT_HH_

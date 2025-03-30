/**
 * Typen, die im Parser benutzt werden.
 */
#ifndef PARSER_TYPES_HH_
#define PARSER_TYPES_HH_

#include "../tac.hh"

using namespace slicc_tac;

namespace slang_parser {

/**
 * Repraesentiert ein Argument eines geparsten Ausdrucks
 */
struct ParsedExpressionArg {
  bool is_int_literal;
  char *var_ref;
  int int_val;
};

/**
 * Repraesentiert einen geparsten Ausdruck oder Vergleich
 */
struct ParsedExpression {
  ParsedExpressionArg left;
  ParsedExpressionArg right;
  TacOperation op;
};

} // namespace slang_parser

#endif /* !PARSER_TYPES_HH_ */

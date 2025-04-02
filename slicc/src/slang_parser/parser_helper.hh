#ifndef PARSER_HELPER_HH_
#define PARSER_HELPER_HH_

#include "driver.hh"
#include "parser_types.hh"

using namespace slicc_tac;

namespace slang_parser {

class Parser;
class Scanner;
class location;

class ParserHelper {
public:
  ParserHelper(FrontendDriver &driver);
  ~ParserHelper();

  /**
   * Erstellt TAC-Einträge für eine Zuweisung
   */
  int tac_statement_assignment(char *target_name, char *expr_result_name);

  /**
   * Erstellt TAC-Einträge für Ausdrücke
   *
   * Gibt den Namen der Zwischenvariable zurück, in der das Ergebnis des
   * Ausdrucks gespeichert wird.
   */
  string tac_sub_expression(ParsedExpression sub_expression);

  /**
   * Erstellt TAC-Eintrag für einen Vergleich und speichert den Wert zwischen
   */
  string tac_comparison_declaration(ParsedExpression &parsed_comparison);

  /**
   * Erstellt TAC-Einträge für den Kopf einer If-Regel
   */
  int tac_if_midrule_declaration(ParsedExpression &parsed_comparison);

  /**
   * Erstellt TAC-Einträge für den start eines else-blocks
   */
  int tac_else_midrule_declaration();

  /**
   * Erstellt TAC-Einträge für das Ende einer If-Regel
   */
  int tac_if_after_block_declaration();

  /**
   * Erstellt TAC-Einträge für das Ende einer Else-Regel
   */
  int tac_else_after_block_declaration();

private:
  FrontendDriver &driver;
};

} // namespace slang_parser

#endif /* !PARSER_HELPER_HH_ */

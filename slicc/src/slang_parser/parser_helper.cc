#include "parser_helper.hh"
#include "strdup.hh"

using namespace slang_parser;

namespace slang_parser {

ParserHelper::ParserHelper(FrontendDriver &driver) : driver(driver) {}

ParserHelper::~ParserHelper() {}

/**
 * Erstellt TAC-Eintrag für einen Vergleich und speichert den Wert zwischen
 */
string
ParserHelper::tac_comparison_declaration(ParsedExpression &parsed_comparison) {
  TacArg arg1 = {NULL, NULL, 0};
  TacArg arg2 = {NULL, NULL, 0};
  TacOperation op;

  if (parsed_comparison.left.is_int_literal) {
    arg1.int_val = parsed_comparison.left.int_val;
  } else {
    arg1.var_ref = strdup2(parsed_comparison.left.var_ref);
  }

  if (parsed_comparison.right.is_int_literal) {
    arg2.int_val = parsed_comparison.right.int_val;
  } else {
    arg2.var_ref = strdup2(parsed_comparison.right.var_ref);
  }

  op = parsed_comparison.op;

  string target_name = driver.add_temporary_var(SymbolType::INT);
  char *target_name_c = strdup2(target_name.c_str());
  driver.add_tac_entry(op, arg1, arg2, target_name_c);

  return target_name;
}

/**
 * Erstellt TAC-Einträge für den Kopf einer If-Regel
 */
int ParserHelper::tac_if_midrule_declaration(
    ParsedExpression &parsed_comparison) {
  // Zuerst erstellen wir den Vergleich und speichern das Ergebnis in einem
  string comparison_result = tac_comparison_declaration(parsed_comparison);

  int id = driver.get_unique_symbol_id();
  string target_name = "AFTER_IF_" + to_string(id);
  char *target_name_c = strdup2(target_name.c_str());
  TacArg arg1 = {strdup2(comparison_result.c_str()), NULL, 0};
  TacArg arg2 = {NULL, NULL, 0};
  // Wenn der Vergleich nicht zutrifft, springen wir zum Ende des If-Blocks
  driver.add_tac_entry(TacOperation::NOT_GOTO, arg1, arg2, target_name_c);
  // Wir merken uns das Label, um es spaeter zu referenzieren
  driver.push_block_context(target_name);

  return 0;
}

/**
 * Erstellt TAC-Einträge für den start eines else-blocks
 */
int ParserHelper::tac_else_midrule_declaration() {
  string if_block_end_label = driver.pop_block_context();

  // Der vorhergehende if-Block ist jetzt zu Ende, wir ueberspringen den
  // else-Block
  int id = driver.get_unique_symbol_id();
  string target_name = "AFTER_ELSE_" + to_string(id);
  driver.push_block_context(target_name);
  driver.add_tac_entry(TacOperation::GOTO, {nullptr, nullptr, 0},
                       {nullptr, nullptr, 0}, strdup2(target_name.c_str()));

  // Wir haben im Kopf der If-Regel ein NOT_GOTO auf ein Label gesetzt, dass wir
  // jetzt hinzufuegen, um den if-Block in dem Fall zu ueberspringen
  char *target_name_c = strdup2(if_block_end_label.c_str());
  driver.add_tac_entry(TacOperation::LABEL, {nullptr, nullptr, 0},
                       {nullptr, nullptr, 0}, target_name_c);

  return 0;
}

/**
 * Erstellt TAC-Einträge für das Ende einer If-Regel
 */
int ParserHelper::tac_if_after_block_declaration() {
  // Wir haben im Kopf der If-Regel ein Goto auf ein Label gesetzt, dass wir
  // jetzt hinzufuegen
  string if_block_end_label = driver.pop_block_context();
  char *target_name_c = strdup2(if_block_end_label.c_str());
  driver.add_tac_entry(TacOperation::LABEL, {nullptr, nullptr, 0},
                       {nullptr, nullptr, 0}, target_name_c);

  return 0;
}

/**
 * Erstellt TAC-Einträge für das Ende einer Else-Regel
 */
int ParserHelper::tac_else_after_block_declaration() {
  // Wir haben im Kopf der Else-Regel ein Goto auf ein Label gesetzt, dass wir
  // jetzt hinzufuegen
  string else_block_end_label = driver.pop_block_context();
  char *target_name_c = strdup2(else_block_end_label.c_str());
  driver.add_tac_entry(TacOperation::LABEL, {nullptr, nullptr, 0},
                       {nullptr, nullptr, 0}, target_name_c);

  return 0;
}

/**
 * Erstellt TAC-Einträge für Ausdrücke
 *
 * Gibt den Namen der Zwischenvariable zurück, in der das Ergebnis des Ausdrucks
 * gespeichert wird.
 */
string ParserHelper::tac_sub_expression(ParsedExpression sub_expression) {
  // if (sub_expression.op == TacOperation::ASSIGN) {
  //   // Zuweisungen in Sub-Expressions stellen eine einfache Konstante oder
  //   // Variable dar
  //   // TODO: Kann optimiert werden indem die Zwischenvariable entfernt wird
  //   und
  //   // der Wert direkt eingesetzt wird
  //
  //   bool is_int_literal = sub_expression.left.is_int_literal;
  //   TacArg arg1 = {is_int_literal ? NULL :
  //   strdup2(sub_expression.left.var_ref),
  //                  NULL, is_int_literal ? sub_expression.left.int_val : 0};
  //   string var_name = driver.get_unique_var_name();
  //   driver.add_tac_entry(TacOperation::ASSIGN, arg1, {NULL, NULL, 0},
  //                        strdup2(var_name.c_str()));
  //   return var_name;
  // }
  switch (sub_expression.op) {
  case TacOperation::ASSIGN: {
    bool is_int_literal = sub_expression.left.is_int_literal;
    char *var_ref =
        is_int_literal ? NULL : strdup2(sub_expression.left.var_ref);
    int int_val = is_int_literal ? sub_expression.left.int_val : 0;
    TacArg arg1 = {var_ref, NULL, int_val};
    string var_name = driver.add_temporary_var(SymbolType::INT);
    driver.add_tac_entry(TacOperation::ASSIGN, arg1, {NULL, NULL, 0},
                         strdup2(var_name.c_str()));
    return var_name;
  }
  case TacOperation::ADD:
  case TacOperation::SUB:
  case TacOperation::MUL:
  case TacOperation::DIV: {
    bool is_left_int_literal = sub_expression.left.is_int_literal;
    bool is_right_int_literal = sub_expression.right.is_int_literal;
    TacArg arg1 = {is_left_int_literal ? NULL
                                       : strdup2(sub_expression.left.var_ref),
                   NULL, is_left_int_literal ? sub_expression.left.int_val : 0};
    TacArg arg2 = {
        is_right_int_literal ? NULL : strdup2(sub_expression.right.var_ref),
        NULL, is_right_int_literal ? sub_expression.right.int_val : 0};
    string var_name = driver.add_temporary_var(SymbolType::INT);
    driver.add_tac_entry(sub_expression.op, arg1, arg2,
                         strdup2(var_name.c_str()));
    return var_name;
  }
  default:
    return "<NOT_IMPLEMENTED>";
  }
}
} // namespace slang_parser

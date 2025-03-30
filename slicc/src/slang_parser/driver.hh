#ifndef SLANG_PARSER_FRONTEND_DRIVER_HH_
#define SLANG_PARSER_FRONTEND_DRIVER_HH_

#include "../tac.hh"
#include <list>
#include <stack>
#include <string>

using namespace slicc_tac;
using namespace std;

namespace slang_parser {

/// Forward declarations of classes
class Parser;
class Scanner;
class ParserHelper;
class location;

class FrontendDriver {
public:
  FrontendDriver();
  ~FrontendDriver();

  int parse();
  int parse_file(std::string &path);

  void reset();

  /**
   * Fügt ein Eintrag der Symboltabelle hinzu.
   * Ist der `parent` `NULL`, wird der Eintrag den `parent_unknown_symbol_table`
   * hinzugefügt und, sobald der Parent des Symbols identifiziert wird,
   * verändert. "root" als Parent sollte für  Funktionsdefinitionen gesetzt
   * werden.
   */
  int add_symbol_table_entry(char *name, SymbolType type, unsigned int line,
                             unsigned int elementCount, char *parent,
                             unsigned int funcArgPosition, bool isRef);

  int add_tac_entry(slicc_tac::TacOperation op, slicc_tac::TacArg arg1,
                    slicc_tac::TacArg arg2, char *res_ref);

  /**
   * Gibt eine eindeutige ID für Zwischenvariablen zurück
   */
  string get_unique_var_name();

  /**
   * Fügt eine temporäre Variable zur Symboltabelle hinzu
   */
  string add_temporary_var(SymbolType type);

  /**
   * Gibt eine eindeutige ID für Symbole oder GOTO-Labels zurück
   */
  int get_unique_symbol_id();

  /**
   * Fügt einen neuen Blockkontext hinzu.
   *
   * Dieser kann spaeter gepopt werden, um bei dem Blockende z.b.
   * ein Goto-Label zu referenzieren.
   */
  void push_block_context(string block_name);

  /**
   * Entfernt den letzten Blockkontext.
   */
  string pop_block_context();

  /**
   * Weist alle momentan noch unbekannten Symboleinträge diesem Parent hinzu
   */
  void identify_parent(char *name);

  const char *symbol_table_type_to_string(SymbolType type);

  void pretty_print();

  Scanner *scanner;
  Parser *parser;
  ParserHelper *helper;

  /**
   * Die Zwischensprache des geparsten Codes
   */
  list<slicc_tac::TacEntry> tac_entries;

  /**
   * Die Symboltabelle des geparsten Codes
   */
  list<slicc_tac::SymbolTableEntry> symbol_table;

  /**
   * Die Symbole die beim parsen noch nicht ihren parent gefunden haben weil
   * der Bottom-Up Parser diese noch nicht reduzieren konnte.
   */
  list<slicc_tac::SymbolTableEntry> parent_unknown_symbol_table;
  int error;

private:
  /**
   * Eindeutige ID für Symbole oder GOTO-Labels
   */
  int unique_symbol_id = 0;

  /**
   * Eindeutige ID für Zwischenvariablen
   */
  int unique_var_id = 0;

  stack<string> block_context;
};

} // namespace slang_parser

#endif /* !SLANG_PARSER_FRONTEND_DRIVER_HH_ */

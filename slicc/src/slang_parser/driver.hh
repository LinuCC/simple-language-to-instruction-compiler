#ifndef DRIVER_HH_
#define DRIVER_HH_

#include "../tac.hh"
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace slicc_tac;
using namespace std;

namespace slang_parser {

/// Forward declarations of classes
class Parser;
class Scanner;
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
   * Weisst alle momentan noch unbekannten Symboleinträge diesem Parent hinzu
   */
  void identify_parent(char *name);

  void print_symbol_table();

  void print_tac_entries();

  Scanner *scanner;
  Parser *parser;

  /**
   * Die Zwischensprache des geparsten Codes
   */
  list<slicc_tac::TacEntry> tac_entries;

  /**
   * Die Symboltabelle des geparsten Codes
   */
  list<slicc_tac::SymbolTableEntry> symbol_table;

  /**
   * Die Symbole die beim parsen noch nicht ihren parent gefunden haben weil der
   * Bottom-Up Parser diese noch nicht reduzieren konnte.
   */
  list<slicc_tac::SymbolTableEntry> parent_unknown_symbol_table;
  int error;
};

} // namespace slang_parser

#endif /* !DRIVER_HH_ */

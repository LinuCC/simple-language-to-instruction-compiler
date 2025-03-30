#ifndef PRETTY_PARSER_HH_
#define PRETTY_PARSER_HH_

#include "../tac.hh"
#include <list>

using namespace slicc_tac;
using namespace std;

namespace slang_parser {

class FrontendDriver;

/**
 * Zeigt Daten des Parsers lesbar an
 */
class PrettyParser {
public:
  PrettyParser();
  ~PrettyParser();

  void print_symbol_table(
      list<slicc_tac::SymbolTableEntry> symbol_table,
      list<slicc_tac::SymbolTableEntry> parent_unknown_symbol_table);

  void print_tac_entries(list<slicc_tac::TacEntry> tac_entries);
};

} // namespace slang_parser

#endif /* !PRETTY_PARSER_HH_ */

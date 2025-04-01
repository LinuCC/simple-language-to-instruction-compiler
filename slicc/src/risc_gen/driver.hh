#ifndef RISC_GEN_BACKEND_DRIVER_HH_
#define RISC_GEN_BACKEND_DRIVER_HH_

#include "../tac.hh"
#include "riscv_types.hh"
#include <list>
#include <map>
#include <string>

using namespace slicc_tac;
using namespace std;

namespace risc_gen {

class CodeGenerator;

/**
 * Der RISC Backend Treiber generiert Maschinencode aus der geparsten
 * Zwischensprache
 */
class BackendDriver {
public:
  BackendDriver();
  ~BackendDriver();

  /**
   * Generiert Maschinencode aus TAC-Einträgen und Symboltabelle, die die
   * Zwischensprache darstellen
   */
  int generate_machine_code(list<slicc_tac::TacEntry> tac_entries,
                            list<slicc_tac::SymbolTableEntry> symbol_table);

  /**
   * Schreibt den generierten Maschinencode in eine Datei
   */
  int write_to_file(string &path);

  list<slicc_tac::TacEntry> tac_entries;
  list<slicc_tac::SymbolTableEntry> symbol_table;
  /**
   * Mapped die Variablen der Symboltabelle auf Register
   */
  map<string, Register> symbol_table_map;

  /**
   * Der generierte Maschinencode
   */
  string machine_code;

  /**
   * Hilfsklasse die den Maschinencode generiert
   */
  CodeGenerator *code_generator;
};

} // namespace risc_gen

#endif /* !RISC_GEN_BACKEND_DRIVER_HH_  */

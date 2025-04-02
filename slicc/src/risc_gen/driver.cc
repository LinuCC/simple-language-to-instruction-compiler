#include "driver.hh"
#include "../tac.hh"
#include "code_generator.hh"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>

using namespace slicc_tac;
using namespace std;

namespace risc_gen {

BackendDriver::BackendDriver() {
  this->code_generator = new CodeGenerator(*this);

  this->tac_entries = list<TacEntry>();
  this->symbol_table = list<SymbolTableEntry>();
  this->machine_code = "";
}
BackendDriver::~BackendDriver() {}

/**
 * Generiert Maschinencode aus TAC-Einträgen und Symboltabelle, die die
 * Zwischensprache darstellen
 */
int BackendDriver::generate_machine_code(
    list<slicc_tac::TacEntry> tac_entries,
    list<slicc_tac::SymbolTableEntry> symbol_table) {
  this->tac_entries = tac_entries;
  this->symbol_table = symbol_table;

  return this->code_generator->generate_machine_code();
}

/**
 * Schreibt den generierten Maschinencode in eine Datei
 */
int BackendDriver::write_to_file(string &path) {
  ofstream file;
  file.open(path);

  if (!file.is_open()) {
    cerr << "Could not open file " << path << " for writing" << endl;
    return 1;
  }

  file << machine_code;

  cout << "==== Wrote machine code to " << path << endl << endl;

  cout << "==== Machine code:" << endl << machine_code << endl;

  file.close();

  return 0;
}

} // namespace risc_gen

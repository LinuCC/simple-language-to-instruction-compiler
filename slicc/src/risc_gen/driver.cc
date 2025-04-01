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

  cout << "\n\n==== Symbol Assignments" << endl;
  cout << right << setw(20) << "Parent" << left << " " << setw(15) << "Name"
       << left << setw(10) << "Register" << endl;

  Register reg = Register::RA;
  // Mapped die Variablen der Symboltabelle auf Register
  for (auto entry : symbol_table) {
    if (entry.type != SymbolType::INT) {
      continue;
    }
    symbol_table_map[entry.name] = reg;
    // FIXME: Grosser Hack, bei dem wir einfach Register hochzählen und
    // zuweisen. Explodiert mit mehr als 31 Variablen. Super stumpf.
    reg = static_cast<Register>(static_cast<int>(reg) + 1);
    cout << right << setw(20) << entry.parent << left << " " << setw(13)
         << entry.name << "  " << left << "x" << symbol_table_map[entry.name]
         << endl;
  }

  for (auto entry : tac_entries) {
    if (entry.op == TacOperation::ASSIGN) {
      string ref;
      if (entry.arg1.var_ref == nullptr) {
        ref = to_string(entry.arg1.int_val);
      } else {
        ref = "x" +
              to_string(static_cast<int>(symbol_table_map[entry.arg1.var_ref]));
      }
      machine_code += "li ";
      machine_code +=
          "x" + to_string(static_cast<int>(symbol_table_map[entry.res_ref]));
      machine_code += ", " + ref + "\n";
    }
  }

  return 0;
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

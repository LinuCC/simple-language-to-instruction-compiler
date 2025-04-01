#include "code_generator.hh"

#include "../tac.hh"

using namespace slicc_tac;

namespace risc_gen {

CodeGenerator::CodeGenerator(BackendDriver &backend_driver) {
  this->backend_driver = &backend_driver;
  this->pretty_code_generator = new PrettyCodeGenerator(backend_driver);
}

CodeGenerator::~CodeGenerator() {}

/**
 * Generiert Maschinencode aus TAC-Einträgen und Symboltabelle, die die
 * Zwischensprache darstellen
 */
int CodeGenerator::generate_machine_code() {
  Register reg = Register::RA;
  // Mapped die Variablen der Symboltabelle auf Register
  for (SymbolTableEntry entry : backend_driver->symbol_table) {
    if (entry.type != SymbolType::INT) {
      continue;
    }
    backend_driver->symbol_table_map[entry.name] = reg;
    // FIXME: Grosser Hack, bei dem wir einfach Register hochzählen und
    // zuweisen. Explodiert mit mehr als 31 Variablen. Super stumpf.
    reg = static_cast<Register>(static_cast<int>(reg) + 1);
  }
  this->pretty_code_generator->print_symbol_assignments();

  for (TacEntry entry : backend_driver->tac_entries) {
    switch (entry.op) {
    case TacOperation::ASSIGN:
      this->op_assign(entry.arg1, entry.res_ref);
      break;
    }
  }

  return 0;
}

string CodeGenerator::ref_var(char *var_ref) {
  // Variablen werden momentan direkt auf Register gemappt
  return "x" +
         to_string(static_cast<int>(backend_driver->symbol_table_map[var_ref]));
}

int CodeGenerator::op_assign(TacArg from, char *to) {
  string cmd = "li";
  string arg1 = this->ref_var(to);
  string arg2;
  if (from.var_ref == nullptr) {
    arg2 = to_string(from.int_val);
  } else {
    arg2 = this->ref_var(from.var_ref);
  }
  backend_driver->machine_code += cmd + " " + arg1 + ", " + arg2 + "\n";
  return 0;
}

} // namespace risc_gen

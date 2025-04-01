#include "pretty_code_generator.hh"
#include "driver.hh"

#include "../tac.hh"
#include <iomanip>
#include <iostream>

using namespace slicc_tac;

namespace risc_gen {

PrettyCodeGenerator::PrettyCodeGenerator(BackendDriver &backend_driver) {
  this->backend_driver = &backend_driver;
}

PrettyCodeGenerator::~PrettyCodeGenerator() {}

void PrettyCodeGenerator::print_symbol_assignments() {
  cout << "\n\n==== Symbol Assignments" << endl;
  cout << right << setw(20) << "Parent" << left << " " << setw(15) << "Name"
       << left << setw(10) << "Register" << endl;

  for (auto entry : backend_driver->symbol_table) {
    cout << right << setw(20) << entry.parent << left << " " << setw(13)
         << entry.name << "  " << left << "x"
         << backend_driver->symbol_table_map[entry.name] << endl;
  }
}

} // namespace risc_gen

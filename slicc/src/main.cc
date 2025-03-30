#include "risc_gen/driver.hh"
#include "slang_parser/driver.hh"
#include <iostream>

int main() {
  slang_parser::FrontendDriver driver;
  // return driver.parse();
  std::string input_file = "./examples/simple-if.slang";
  int parse_ret = driver.parse_file(input_file);
  if (parse_ret != 0) {
    return parse_ret;
  }
  std::cout << "== Successful Parse" << std::endl;
  driver.pretty_print();

  // TODO: Optimize step

  risc_gen::BackendDriver backend_driver;
  backend_driver.generate_machine_code(driver.tac_entries, driver.symbol_table);
  std::string output_file = "./examples/simple-if.risc";
  return backend_driver.write_to_file(output_file);

  return 0;
}

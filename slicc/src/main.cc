#include "slang_parser/driver.hh"

int main() {
  slang_parser::Driver driver;
  // return driver.parse();
  std::string input_file = "./input.slang";
  int parse_ret = driver.parse_file(input_file);
  if (parse_ret != 0) {
    return parse_ret;
  }
  std::cout << "== Successful Parse" << std::endl;
  driver.print_symbol_table();
  driver.print_tac_entries();
  return 0;
}

#include "slang_parser/driver.hh"

int main() {
  slang_parser::Driver driver;
  // return driver.parse();
  std::string input_file = "./input.pc";
  return driver.parse_file(input_file);
}

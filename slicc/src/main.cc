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
  return 0;
}

#ifndef DRIVER_HH_
#define DRIVER_HH_

#include <fstream>
#include <iostream>
#include <string>

namespace parser_gen {

/// Forward declarations of classes
class Parser;
class Scanner;
class location;

class Driver {
public:
  Driver();
  ~Driver();

  int parse();
  int parse_file(std::string &path);

  void reset();

private:
  Scanner *scanner_;
  Parser *parser_;
  int error_;

  /// Allows Parser and Scanner to access private attributes
  /// of the Driver class
  friend class Parser;
  friend class Scanner;
};

} // namespace parser_gen

#endif /* !DRIVER_HH_ */

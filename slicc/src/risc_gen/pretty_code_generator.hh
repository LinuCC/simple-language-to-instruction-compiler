#ifndef PRETTY_CODE_GENERATOR_HH_
#define PRETTY_CODE_GENERATOR_HH_

#include "driver.hh"
#include <iostream>

namespace risc_gen {

/**
 * Funktionen um Infos über die Generierung anzuzeigen
 */
class PrettyCodeGenerator {
public:
  PrettyCodeGenerator(BackendDriver &backend_driver);
  ~PrettyCodeGenerator();

  void print_symbol_assignments();

private:
  BackendDriver *backend_driver;
};

} // namespace risc_gen

#endif /* !PRETTY_CODE_GENERATOR_HH_ */

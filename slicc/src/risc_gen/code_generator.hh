#ifndef CODE_GENERATOR_HH_
#define CODE_GENERATOR_HH_

#include <iostream>

#include "../tac.hh"
#include "pretty_code_generator.hh"

using namespace slicc_tac;

namespace risc_gen {

class BackendDriver;

/**
 * Der Codegenerator generiert Maschinencode aus der geparsten Zwischensprache
 */
class CodeGenerator {
public:
  CodeGenerator(BackendDriver &backend_driver);
  ~CodeGenerator();

  /**
   * Generiert Maschinencode aus TAC-Einträgen und Symboltabelle, die die
   * Zwischensprache darstellen
   */
  int generate_machine_code();

private:
  /**
   * Ladet den Wert einer Variable
   */
  string ref_var(char *var_ref);

  /**
   * Generiert Maschinencode für eine Zuweisung
   */
  int op_assign(TacArg from, char *to);

  BackendDriver *backend_driver;
  PrettyCodeGenerator *pretty_code_generator;
};

} // namespace risc_gen

#endif /* !CODE_GENERATOR_HH_ */

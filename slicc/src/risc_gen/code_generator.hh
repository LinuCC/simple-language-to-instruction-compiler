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
   * Ueberprueft ob ein TacArg einen konstanten int-Wert enthaelt
   */
  bool is_tac_arg_const(TacArg arg);

  /**
   * Uebersetzt den Wert einer Arg zu Maschinencode
   */
  string unwrap_tac_arg(TacArg arg);

  /**
   * Baut eine Zeile Maschinencode mit einer Anweisung mit zwei Adressen
   * zusammen
   */
  string assembly_two_address(string cmd, string arg1, string arg2);

  /**
   * Baut eine Zeile Maschinencode mit einer Anweisung mit zwei Adressen
   * zusammen
   */
  string assembly_three_address(string cmd, string arg1, string arg2,
                                string arg3);

  /**
   * Generiert Maschinencode für eine Zuweisung
   */
  int op_assign(TacArg from, char *to);

  /**
   * Generiert Maschinencode für eine Addition
   */
  int op_add(TacArg arg1, TacArg arg2, char *res);

  /**
   * Generiert Maschinencode für eine Subtraktion
   */
  int op_sub(TacArg arg1, TacArg arg2, char *res);

  /**
   * Generiert Maschinencode für eine Multiplikation
   */
  int op_mul(TacArg arg1, TacArg arg2, char *res);

  /**
   * Generiert Maschinencode für eine Division
   */
  int op_div(TacArg arg1, TacArg arg2, char *res);

  /**
   * Generiert Maschinencode für eine Modulo-Operation
   */
  int op_mod(TacArg arg1, TacArg arg2, char *res);

  /**
   * Vergleicht zwei Werte (Kleiner als)
   */
  int op_lt(TacArg arg1, TacArg arg2, char *res);

  /**
   * Vergleicht zwei Werte (Größer als)
   */
  int op_gt(TacArg arg1, TacArg arg2, char *res);

  /**
   * Vergleicht zwei Werte (Kleiner gleich)
   */
  int op_le(TacArg arg1, TacArg arg2, char *res);

  /**
   * Vergleicht zwei Werte (Größer gleich)
   */
  int op_ge(TacArg arg1, TacArg arg2, char *res);

  /**
   * Vergleicht zwei Werte (Gleich)
   */
  int op_eq(TacArg arg1, TacArg arg2, char *res);

  /**
   * Vergleicht zwei Werte (Ungleich)
   */
  int op_ne(TacArg arg1, TacArg arg2, char *res);

  /**
   * Negiert einen Wert
   */
  int op_negate(TacArg arg1, char *res);

  /**
   * Generiert Maschinencode für einen Sprung
   */
  int op_goto(TacArg arg1, char *label);

  /**
   * Generiert Maschinencode für einen negierten Sprung
   */
  int op_not_goto(TacArg arg1, char *label);

  /**
   * Generiert Maschinencode für ein Label
   */
  int op_label(char *label);

  int get_unique_id();

  /**
   * Zählt wieviele der zwei Argumente eine Konstante sind
   */
  int get_const_arg_count(TacArg arg1, TacArg arg2);

  BackendDriver *backend_driver;
  PrettyCodeGenerator *pretty_code_generator;

  /**
   * Eindeutige ID für Zwischenvariablen / Label
   */
  int unique_id;
};

} // namespace risc_gen

#endif /* !CODE_GENERATOR_HH_ */

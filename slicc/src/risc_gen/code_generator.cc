#include "code_generator.hh"

#include "../tac.hh"
#include "strdup.hh"
#include <iomanip>
#include <sstream>
#include <tuple>
#include <utility>

using namespace slicc_tac;

namespace risc_gen {

/**
 * RISC-V ISA gehen von 0 als Wahr und 1 als Falsch aus
 */
static const int TRUTHY = 0;

static const TacArg TRUTHY_ARG = {NULL, NULL, 0};
/**
 * Das Register `x0` ist immer 0.
 *
 * Befehle wie `bne` und `beq` nehmen nur Register als Argumente entgegen (nicht
 * Konstanten wie `0`).
 * Da `x0` immer 0 ist, koennen wir es als Vergleichswert
 * fuer solche Operationen verwenden.
 */
static const char *REG_ZERO = "x0";

static const char *REG_TEMP = "x31";

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
    // zuweisen. Explodiert mit mehr als 30 Variablen. Super stumpf.
    reg = static_cast<Register>(static_cast<int>(reg) + 1);
  }
  this->pretty_code_generator->print_symbol_assignments();

  for (TacEntry entry : backend_driver->tac_entries) {
    switch (entry.op) {
    case TacOperation::ASSIGN:
      this->op_assign(entry.arg1, entry.res_ref);
      break;
    case TacOperation::ADD:
      this->op_add(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::SUB:
      this->op_sub(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::MUL:
      this->op_mul(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::DIV:
      this->op_div(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::MOD:
      this->op_mod(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::LT:
      this->op_lt(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::GT:
      this->op_gt(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::LE:
      this->op_le(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::GE:
      this->op_ge(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::EQ:
      this->op_eq(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::NE:
      this->op_ne(entry.arg1, entry.arg2, entry.res_ref);
      break;
    case TacOperation::GOTO:
      this->op_goto(entry.arg1, entry.res_ref);
      break;
    case TacOperation::NOT_GOTO:
      this->op_not_goto(entry.arg1, entry.res_ref);
      break;
    case TacOperation::LABEL:
      this->op_label(entry.res_ref);
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

bool CodeGenerator::is_tac_arg_const(TacArg arg) {
  return arg.var_ref == nullptr;
}

string CodeGenerator::unwrap_tac_arg(TacArg arg) {
  if (this->is_tac_arg_const(arg)) {
    return to_string(arg.int_val);
  }
  return this->ref_var(arg.var_ref);
}

string CodeGenerator::assembly_two_address(string cmd, string arg1,
                                           string arg2) {
  stringstream ss;
  ss << setw(4) << left << cmd << " " << setw(3) << arg1 << ", " << setw(3)
     << arg2 << endl;
  return ss.str();
}

string CodeGenerator::assembly_three_address(string cmd, string arg1,
                                             string arg2, string arg3) {
  stringstream ss;
  ss << setw(4) << left << cmd << " " << setw(3) << arg1 << ", " << setw(3)
     << arg2 << ", " << setw(3) << arg3 << endl;
  return ss.str();
}

int CodeGenerator::op_assign(TacArg from, char *to) {
  string arg1 = this->unwrap_tac_arg(from);
  string res = this->ref_var(to);

  if (this->is_tac_arg_const(from)) {
    // Konstanten werden mit `li` geladen
    string cmd = "li";
    backend_driver->machine_code += this->assembly_two_address(cmd, res, arg1);

    return 0;

    // Alternative Implementierung mit `addi` (manche emulatoren implementieren
    // kein `li`):
    // string cmd = "addi"; backend_driver->machine_code +=
    //     this->assembly_three_address(cmd, res, REG_ZERO, arg1);
    // return 0;
  }

  // Um eine int von einem Register in ein anderes zu kopieren, wird dieses mit
  // `0` summiert
  string cmd = "addi";
  string arg2 = "0";
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, res, arg1, arg2);
  return 0;
}

int CodeGenerator::get_unique_id() { return this->unique_id++; }

int CodeGenerator::get_const_arg_count(TacArg arg1, TacArg arg2) {
  int count = 0;
  if (this->is_tac_arg_const(arg1)) {
    count++;
  }
  if (this->is_tac_arg_const(arg2)) {
    count++;
  }
  return count;
}

int CodeGenerator::op_add(TacArg arg1, TacArg arg2, char *res_ref) {
  string cmd;
  // bool arg1_const = this->is_tac_arg_const(arg1);
  // bool arg2_const = this->is_tac_arg_const(arg2);
  // if (arg1_const && !arg2_const) {
  //   cmd = "addi";
  // } else if (!arg1_const && arg2_const) {
  //   cmd = "addi";
  //   // Vertausche arg1 und arg2
  //   TacArg tmp = arg1;
  //   arg1 = arg2;
  //   arg2 = tmp;
  // } else if (arg1_const && arg2_const) {
  //   cerr << "Cannot add two constants" << endl;
  //   return 1;
  // } else {
  //   cmd = "add";
  // }
  // Je nach Anzahl der Konstanten in den Argumenten müssen wir den
  // Maschinencode anpassen
  switch (this->get_const_arg_count(arg1, arg2)) {
  case 0:
    cmd = "add";
    break;
  case 1:
    cmd = "addi";
    if (this->is_tac_arg_const(arg1)) {
      // Vertausche arg1 und arg2 damit die Konstante immer hinten steht
      swap(arg1, arg2);
    }
    break;
  case 2:
    // Es gibt keinen Befehl um zwei Konstanten zu addieren.
    // Alternativ speichern wir eine in einem temporären Register.
    cmd = "addi";
    this->op_assign(arg2, res_ref);
    arg2 = {res_ref, NULL, 0};
    break;
  }
  string arg1_str = this->unwrap_tac_arg(arg1);
  string arg2_str = this->unwrap_tac_arg(arg2);
  string res_str = this->ref_var(res_ref);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, res_str, arg1_str, arg2_str);
  return 0;
}

int CodeGenerator::op_sub(TacArg arg1, TacArg arg2, char *res_ref) {
  string cmd = "sub";
  string arg1_str = this->unwrap_tac_arg(arg1);
  string arg2_str = this->unwrap_tac_arg(arg2);
  string res_str = this->ref_var(res_ref);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, res_str, arg1_str, arg2_str);
  return 0;
}

int CodeGenerator::op_mul(TacArg arg1, TacArg arg2, char *res_ref) {
  string cmd = "mul";
  string arg1_str = this->unwrap_tac_arg(arg1);
  string arg2_str = this->unwrap_tac_arg(arg2);
  string res_str = this->ref_var(res_ref);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, res_str, arg1_str, arg2_str);
  return 0;
}

int CodeGenerator::op_div(TacArg arg1, TacArg arg2, char *res_ref) {
  string cmd = "div";
  string arg1_str = this->unwrap_tac_arg(arg1);
  string arg2_str = this->unwrap_tac_arg(arg2);
  string res_str = this->ref_var(res_ref);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, res_str, arg1_str, arg2_str);
  return 0;
}

int CodeGenerator::op_mod(TacArg arg1, TacArg arg2, char *res_ref) {
  string cmd = "rem";
  string arg1_str = this->unwrap_tac_arg(arg1);
  string arg2_str = this->unwrap_tac_arg(arg2);
  string res_str = this->ref_var(res_ref);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, res_str, arg1_str, arg2_str);
  return 0;
}

int CodeGenerator::op_negate(TacArg arg1, char *res_ref) {
  string cmd = "xori";
  string arg1_str = this->unwrap_tac_arg(arg1);
  string res_str = this->ref_var(res_ref);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, res_str, arg1_str, "1");
  return 0;
}

// int CodeGenerator::op_lt(TacArg arg1, TacArg arg2, char *res_ref) {
//   // `slt` setzt das Zielregister auf `1` wenn arg1 < arg2, wir wollen aber
//   // `0` als Wahr und `1` als Falsch behandeln.
//   // Daher benutzen wir diesen Befehl invertiert.
//   string cmd;
//   switch (this->get_const_arg_count(arg1, arg2)) {
//   case 0:
//     cmd = "slt";
//     break;
//   case 1:
//     cmd = "slti";
//     if (this->is_tac_arg_const(arg1)) {
//       swap(arg1, arg2);
//     }
//     break;
//   case 2:
//     cmd = "slti";
//     this->op_assign(arg2, res_ref);
//     arg2 = {res_ref, NULL, 0};
//     break;
//   }
//
//   string arg1_str = this->unwrap_tac_arg(arg1);
//   string arg2_str = this->unwrap_tac_arg(arg2);
//   string res_str = this->ref_var(res_ref);
//   backend_driver->machine_code +=
//       this->assembly_three_address(cmd, res_str, arg1_str, arg2_str);
//   return 0;
// }
//
// int CodeGenerator::op_gt(TacArg arg1, TacArg arg2, char *res_ref) {
//   return this->op_lt(arg2, arg1, res_ref);
// }
//
// int CodeGenerator::op_le(TacArg arg1, TacArg arg2, char *res_ref) {
//   this->op_gt(arg2, arg1, res_ref);
//   return this->op_negate({res_ref, NULL, 0}, res_ref);
// }
//
// int CodeGenerator::op_ge(TacArg arg1, TacArg arg2, char *res_ref) {
//   this->op_lt(arg2, arg1, res_ref);
//   return this->op_negate({res_ref, NULL, 0}, res_ref);
// }

int CodeGenerator::op_ge(TacArg arg1, TacArg arg2, char *res_ref) {
  // `slt` setzt das Zielregister auf `1` wenn arg1 < arg2, ansonsten auf `0`.
  // Wir wollen aber `0` als Wahr und `1` als Falsch behandeln.
  // Daher benutzen wir diesen Befehl invertiert.
  string cmd;
  switch (this->get_const_arg_count(arg1, arg2)) {
  case 0:
    cmd = "slt";
    break;
  case 1:
    if (this->is_tac_arg_const(arg1)) {
      // Arg 1 ist eine Konstante, kann aber an der Position nicht von `slti`
      // verwendet werden (nur arg2 kann eine Konstante sein).
      cmd = "slt";
      this->op_assign(arg1, res_ref);
      arg1 = {res_ref, NULL, 0};
    } else {
      cmd = "slti";
    }
    break;
  case 2:
    cmd = "slti";
    this->op_assign(arg2, res_ref);
    arg2 = {res_ref, NULL, 0};
    break;
  }

  string arg1_str = this->unwrap_tac_arg(arg1);
  string arg2_str = this->unwrap_tac_arg(arg2);
  string res_str = this->ref_var(res_ref);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, res_str, arg1_str, arg2_str);
  return 0;
}

int CodeGenerator::op_le(TacArg arg1, TacArg arg2, char *res_ref) {
  return this->op_ge(arg2, arg1, res_ref);
}

int CodeGenerator::op_gt(TacArg arg1, TacArg arg2, char *res_ref) {
  this->op_ge(arg2, arg1, res_ref);
  return this->op_negate({res_ref, NULL, 0}, res_ref);
}

int CodeGenerator::op_lt(TacArg arg1, TacArg arg2, char *res_ref) {
  this->op_ge(arg1, arg2, res_ref);
  return this->op_negate({res_ref, NULL, 0}, res_ref);
}

int CodeGenerator::op_eq(TacArg arg1, TacArg arg2, char *res_ref) {
  // Temporaere Register um int Konstanten zu speichern da `beq` nur Register
  // als Argumente entgegennimmt
  const char *reg_temp_1 = REG_TEMP;
  const char *reg_temp_2 = strdup2(this->ref_var(res_ref).c_str());
  // Vergleiche zweier Werte auf Gleichheit wird mit einem bedingten Sprung
  // geloest. Wenn die Werte gleich sind, wird der Sprung ausgefuehrt und das
  // `res_ref` Register auf 0 gesetzt. Andernfalls wird das Ergebnis mittels
  // eines anderen Sprunges auf 1 gesetzt.
  string cmd = "beq";
  string arg1_str = this->unwrap_tac_arg(arg1);
  string arg2_str = this->unwrap_tac_arg(arg2);
  if (this->is_tac_arg_const(arg1)) {
    this->op_assign(arg1, strdup2(reg_temp_1));
    arg1_str = reg_temp_1;
  }
  if (this->is_tac_arg_const(arg2)) {
    this->op_assign(arg2, strdup2(reg_temp_2));
    arg2_str = reg_temp_2;
  }
  int id = this->get_unique_id(); // Eindeutige ID fuer Labels
  string not_true_label = "CODEGEN_EQ_NOT_TRUE_" + to_string(id);
  string end_label = "CODEGEN_EQ_END_" + to_string(id);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, arg1_str, arg2_str, not_true_label);
  this->op_assign({NULL, NULL, 0}, res_ref);
  this->op_goto(TRUTHY_ARG, strdup2(end_label.c_str()));
  this->op_label(strdup2(not_true_label.c_str()));
  this->op_assign({NULL, NULL, 1}, res_ref);
  this->op_label(strdup2(end_label.c_str()));
  return 0;
}

int CodeGenerator::op_ne(TacArg arg1, TacArg arg2, char *res_ref) {
  // Inverse von `op_eq`
  string cmd = "bne";
  const char *reg_temp_1 = REG_TEMP;
  const char *reg_temp_2 = strdup2(this->ref_var(res_ref).c_str());
  string arg1_str = this->unwrap_tac_arg(arg1);
  string arg2_str = this->unwrap_tac_arg(arg2);
  if (this->is_tac_arg_const(arg1)) {
    this->op_assign(arg1, strdup2(reg_temp_1));
    arg1_str = reg_temp_1;
  }
  if (this->is_tac_arg_const(arg2)) {
    this->op_assign(arg2, strdup2(reg_temp_2));
    arg2_str = reg_temp_2;
  }
  int id = this->get_unique_id(); // Eindeutige ID für Labels
  string not_true_label = "CODEGEN_NE_NOT_TRUE_" + to_string(id);
  string end_label = "CODEGEN_NE_END_" + to_string(id);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, arg1_str, arg2_str, not_true_label);
  this->op_assign({NULL, NULL, 0}, res_ref);
  this->op_goto(TRUTHY_ARG, strdup2(end_label.c_str()));
  this->op_label(strdup2(not_true_label.c_str()));
  this->op_assign({NULL, NULL, 1}, res_ref);
  this->op_label(strdup2(end_label.c_str()));
  return 0;
}

int CodeGenerator::op_goto(TacArg arg1, char *label) {

  if (arg1.var_ref == nullptr) {
    // Unbedingter Sprung
    string cmd = "jal";
    string arg1_str = REG_ZERO;
    string arg2_str = string(label);
    backend_driver->machine_code +=
        this->assembly_two_address(cmd, arg1_str, arg2_str);
    return 0;
  }

  // Bedingter Sprung, wird ausgeführt wenn arg1 == 0
  string cmd = "beq";
  string arg1_str = REG_ZERO;
  string arg2_str = this->ref_var(arg1.var_ref);
  string arg3_str = string(label);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, arg1_str, arg2_str, arg3_str);
  return 0;
}

int CodeGenerator::op_not_goto(TacArg arg1, char *label) {
  // Bedingter Sprung, wird ausgeführt wenn arg1 != 0
  string cmd = "bne";
  string arg1_str = REG_ZERO;
  string arg2_str = this->ref_var(arg1.var_ref);
  string arg3_str = string(label);
  backend_driver->machine_code +=
      this->assembly_three_address(cmd, arg1_str, arg2_str, arg3_str);
  return 0;
}

int CodeGenerator::op_label(char *label) {
  backend_driver->machine_code += string(label) + ":\n";
  return 0;
}

} // namespace risc_gen

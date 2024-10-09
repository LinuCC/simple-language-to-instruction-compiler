#include "driver.hh"
#include "../tac.hh"
#include "parser.hh"
#include "scanner.hh"
#include <list>

using namespace slang_parser;

namespace slang_parser {
FrontendDriver::FrontendDriver() {
  this->scanner = new Scanner();
  this->parser = new Parser(*this);
  this->error = 0;
  this->symbol_table = list<SymbolTableEntry>();
  this->parent_unknown_symbol_table = list<SymbolTableEntry>();
}

FrontendDriver::~FrontendDriver() {
  delete parser;
  delete scanner;
}

void FrontendDriver::reset() { error = 0; }

int FrontendDriver::parse() {
  std::cout << "\n\nStarting parsing stdin" << std::endl << std::endl;
  scanner->switch_streams(&std::cin, &std::cerr);
  parser->parse();
  return error;
}

int FrontendDriver::parse_file(std::string &path) {
  std::cout << "\n\nStarting parsing file " << path << std::endl << std::endl;
  std::ifstream s(path.c_str(), std::ifstream::in);
  scanner->switch_streams(&s, &std::cerr);

  parser->parse();

  s.close();

  std::cout << "\n\n==== Parsing done" << std::endl << std::endl;

  return error;
}

int FrontendDriver::add_symbol_table_entry(
    char *name, SymbolType type, unsigned int line, unsigned int elementCount,
    char *parent, unsigned int funcArgPosition, bool isRef) {
  SymbolTableEntry entry = {
      name, type, line, elementCount, parent, funcArgPosition, isRef};

  if (parent == nullptr) {
    parent_unknown_symbol_table.push_back(entry);
    return 0;
  }

  symbol_table.push_back(entry);
  return 0;
}

int FrontendDriver::add_tac_entry(slicc_tac::TacOperation op,
                                  slicc_tac::TacArg arg1,
                                  slicc_tac::TacArg arg2, char *res_ref) {
  slicc_tac::TacEntry entry = {op, arg1, arg2, res_ref};
  tac_entries.push_back(entry);
}

void FrontendDriver::identify_parent(char *parent_name) {
  for (auto &entry : parent_unknown_symbol_table) {
    entry.parent = parent_name;
    symbol_table.push_back(entry);
  }
  parent_unknown_symbol_table.clear();
}

std::string tacOperationToString(TacOperation op) {
  switch (op) {
  case ADD:
    return "ADD";
  case SUB:
    return "SUB";
  case MUL:
    return "MUL";
  case DIV:
    return "DIV";
  case MOD:
    return "MOD";
  case AND:
    return "AND";
  case OR:
    return "OR";
  case NOT:
    return "NOT";
  case LT:
    return "LT";
  case GT:
    return "GT";
  case LE:
    return "LE";
  case GE:
    return "GE";
  case EQ:
    return "EQ";
  case NE:
    return "NE";
  case ASSIGN:
    return "ASSIGN";
  case GOTO:
    return "GOTO";
  case LABEL:
    return "LABEL";
  default:
    return "UNKNOWN";
  }
}

void FrontendDriver::print_symbol_table() {
  std::cout << "\n\n==== Symbol Table" << std::endl;

  std::cout << std::right << std::setw(30) << "Name" << "  " << std::left
            << std::setw(10) << "Type" << std::left << std::setw(15)
            << "ElementCount" << std::left << std::setw(7) << "Line"
            << std::left << std::setw(12) << "FuncArgPos" << std::left
            << std::setw(12) << "IsRef" << std::left << std::setw(15)
            << "Parent" << std::endl;

  for (auto entry : symbol_table) {
    // Format the table nicely
    std::cout << std::right << std::setw(30) << entry.name << "  " << std::left
              << std::setw(10) << entry.type << std::left << std::setw(15)
              << entry.elementCount << std::left << std::setw(7) << entry.line
              << std::left << std::setw(12) << entry.funcArgPosition
              << std::left << std::setw(12) << entry.isRef << std::left
              << std::setw(15) << entry.parent << std::endl;
  }

  if (parent_unknown_symbol_table.empty()) {
    return;
  }
  /*
   * Wir sollten hier nie landen, da wir nach dem parsen alle Parents von
   * Symbolen identifiziert und zugeordnet haben sollten.
   */
  std::cout << "\n!! Unknown Parents" << std::endl;
  for (auto entry : parent_unknown_symbol_table) {
    std::cout << "    Name: " << entry.name << std::endl;
    std::cout << "    Type: " << entry.type << std::endl;
    std::cout << "    Line: " << entry.line << std::endl;
    std::cout << "    ElementCount: " << entry.elementCount << std::endl;
    if (entry.parent == nullptr) {
      std::cout << "    Parent: nullptr" << std::endl;
    } else {
      std::cout << "    Parent: " << entry.parent << std::endl;
    }
    std::cout << "    FuncArgPosition: " << entry.funcArgPosition << std::endl;
    std::cout << "    IsRef: " << entry.isRef << std::endl << std::endl;
  }
}

void FrontendDriver::print_tac_entries() {
  std::cout << "\n\n==== TAC Entries" << std::endl;

  // typedef struct _TacArg {
  //   char *var_ref;
  //   char *func_ref;
  //   int int_val;
  // } TacArg;

  std::cout << std::right << std::setw(15) << "Operation" << "  " << std::left
            << std::setw(15) << "Arg1.var_ref" << std::left << std::setw(15)
            << "Arg1.func_ref" << std::left << std::setw(15) << "Arg1.int_val"
            << std::left << std::setw(15) << "Arg2.var_ref" << std::left
            << std::setw(15) << "Arg2.func_ref" << std::left << std::setw(15)
            << "Arg2.int_val" << std::left << std::setw(15) << "Result"
            << std::endl;

  for (auto entry : tac_entries) {
    // Format the table nicely
    const char *arg1_var_ref =
        entry.arg1.var_ref != nullptr ? entry.arg1.var_ref : "NULL";
    const char *arg1_func_ref =
        entry.arg1.func_ref != nullptr ? entry.arg1.func_ref : "NULL";
    const int arg1_int_val = entry.arg1.int_val;
    const char *arg2_var_ref =
        entry.arg2.var_ref != nullptr ? entry.arg2.var_ref : "NULL";
    const char *arg2_func_ref =
        entry.arg2.func_ref != nullptr ? entry.arg2.func_ref : "NULL";
    const int arg2_int_val = entry.arg2.int_val;
    const char *result = entry.res_ref != nullptr ? entry.res_ref : "NULL";
    std::cout << std::right << std::setw(15) << tacOperationToString(entry.op)
              << "  " << std::left << std::setw(15) << arg1_var_ref << std::left
              << std::setw(15) << arg1_func_ref << std::left << std::setw(15)
              << arg1_int_val << std::left << std::setw(15) << arg2_var_ref
              << std::left << std::setw(15) << arg2_func_ref << std::left
              << std::setw(15) << arg2_int_val << std::left << std::setw(15)
              << result << std::endl;
  }
}

} // namespace slang_parser

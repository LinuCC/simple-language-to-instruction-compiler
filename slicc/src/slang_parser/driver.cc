#include "driver.hh"
#include "../tac.hh"
#include "parser.hh"
#include "parser_helper.hh"
#include "pretty_parser.hh"
#include "scanner.hh"
#include <fstream>
#include <iostream>
#include <list>

using namespace slang_parser;

namespace slang_parser {
FrontendDriver::FrontendDriver() {
  this->scanner = new Scanner();
  this->parser = new Parser(*this);
  this->helper = new ParserHelper(*this);
  this->error = 0;
  this->symbol_table = list<SymbolTableEntry>();
  this->parent_unknown_symbol_table = list<SymbolTableEntry>();
  this->tac_entries = list<TacEntry>();
  this->block_context = stack<string>();
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
  return 0;
}

string FrontendDriver::get_unique_var_name() {
  int id = this->unique_var_id++;
  return ":t" + to_string(id);
}

int FrontendDriver::get_unique_symbol_id() { return this->unique_symbol_id++; }

void FrontendDriver::push_block_context(string block_name) {
  block_context.push(block_name);
}

string FrontendDriver::pop_block_context() {
  string block_name = string(block_context.top());
  block_context.pop();
  return block_name;
}

void FrontendDriver::identify_parent(char *parent_name) {
  for (auto &entry : parent_unknown_symbol_table) {
    entry.parent = parent_name;
    symbol_table.push_back(entry);
  }
  parent_unknown_symbol_table.clear();
}

void FrontendDriver::pretty_print() {
  PrettyParser pretty_parser = PrettyParser();
  pretty_parser.print_symbol_table(this->symbol_table,
                                   this->parent_unknown_symbol_table);
  pretty_parser.print_tac_entries(this->tac_entries);
}

} // namespace slang_parser

// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 1 "parse.yy"
     /* PARSER */

#include "parser.hh"
#include "scanner.hh"
#include "../tac.hh"
#include "strdup.hh"
#include "parser_types.hh"
#include "parser_helper.hh"

// Verlinke den C++ Flex Scanner mit dem Bison Parser mit diesem Alias
#define yylex driver.scanner->yylex

#line 54 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"


#include "parser.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 47 "parse.yy"
namespace slang_parser {
#line 152 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"

  /// Build a parser object.
  Parser::Parser (FrontendDriver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}


  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 4: // program: TOK_PROGRAM TOK_ID block
#line 123 "parse.yy"
    {
      /* Setze für alle Symboltabelleneinträge, die in dem Block definiert wurden, den Programmnamen als parent */
      char* parent = strdup2((yystack_[1].value.str_val));
      driver.add_symbol_table_entry(
        parent,
        slicc_tac::SymbolType::PROGRAM,
        yystack_[2].location.begin.line,
        0,
        strdup2("main"),
        0,
        false
      );
      driver.identify_parent(parent);
    }
#line 638 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 10: // variable_declaration: type TOK_ID TOK_SEMICOLON
#line 163 "parse.yy"
                                  {
      std::cout << "PARSER: Variable declaration: " << (yystack_[1].value.str_val) << " Type: " << (yystack_[2].value.type_val).symbol_type << std::endl;
      char* name = strdup2((yystack_[1].value.str_val));
      driver.add_symbol_table_entry(
        name,
        (yystack_[2].value.type_val).symbol_type,
        yystack_[2].location.begin.line,
        (yystack_[2].value.type_val).arr_element_amount,
        NULL, // Parent nicht bekannt
        0,
        false
      );

      // In arg1 ist die `0` für int_val der tatsächliche Wert
      TacArg arg1 = { NULL, NULL, 0, };
      // arg2 wird nicht benutzt
      TacArg arg2 = { NULL, NULL, 0, };
      driver.add_tac_entry(
        TacOperation::ASSIGN,
        arg1,
        arg2,
        name
      );
    }
#line 667 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 11: // variable_declaration: type TOK_ID TOK_ASSIGN TOK_INT_LITERAL TOK_SEMICOLON
#line 187 "parse.yy"
                                                                      {
      std::cout << "PARSER: Variable declaration: " << (yystack_[3].value.str_val) << " Type: " << (yystack_[4].value.type_val).symbol_type << std::endl;
      char* name = strdup2((yystack_[3].value.str_val));
      driver.add_symbol_table_entry(
        name,
        (yystack_[4].value.type_val).symbol_type,
        yystack_[4].location.begin.line,
        0,
        NULL, // Parent nicht bekannt
        0,
        false
      );
      driver.add_tac_entry(
        TacOperation::ASSIGN,
        { NULL, NULL, (yystack_[1].value.int_val), },
        { NULL, NULL, 0, },
        name
      );
    }
#line 691 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 19: // statement_assignment: TOK_ID TOK_ASSIGN expression
#line 225 "parse.yy"
                               {
    std::cout << "PARSER: Assignment: " << (yystack_[2].value.str_val) << " " << std::endl;
    driver.helper->tac_statement_assignment((yystack_[2].value.str_val), (yystack_[0].value.str_val));
  }
#line 700 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 22: // expression: TOK_INT_LITERAL
#line 235 "parse.yy"
                  {
    (yylhs.value.str_val) = strdup2(driver.helper->tac_sub_expression({ { true, NULL, (yystack_[0].value.int_val), }, { false, NULL, 0, }, TacOperation::ASSIGN }).c_str());
  }
#line 708 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 23: // expression: TOK_ID
#line 238 "parse.yy"
           {
    (yylhs.value.str_val) = (yystack_[0].value.str_val);
  }
#line 716 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 24: // expression: expression TOK_PLUS expression
#line 242 "parse.yy"
                                   {
    (yylhs.value.str_val) = strdup2(driver.helper->tac_sub_expression({ { false, (yystack_[2].value.str_val), 0, }, { false, (yystack_[0].value.str_val), 0, }, TacOperation::ADD }).c_str());
  }
#line 724 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 25: // expression: expression TOK_MINUS expression
#line 245 "parse.yy"
                                   {
    (yylhs.value.str_val) = strdup2(driver.helper->tac_sub_expression({ { false, (yystack_[2].value.str_val), 0, }, { false, (yystack_[0].value.str_val), 0, }, TacOperation::SUB }).c_str());
  }
#line 732 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 26: // expression: expression TOK_MUL expression
#line 248 "parse.yy"
                                 {
    (yylhs.value.str_val) = strdup2(driver.helper->tac_sub_expression({ { false, (yystack_[2].value.str_val), 0, }, { false, (yystack_[0].value.str_val), 0, }, TacOperation::MUL }).c_str());
  }
#line 740 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 27: // expression: expression TOK_DIV expression
#line 251 "parse.yy"
                                 {
    (yylhs.value.str_val) = strdup2(driver.helper->tac_sub_expression({ { false, (yystack_[2].value.str_val), 0, }, { false, (yystack_[0].value.str_val), 0, }, TacOperation::DIV }).c_str());
  }
#line 748 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 28: // expression: expression TOK_MOD expression
#line 254 "parse.yy"
                                 {
    (yylhs.value.str_val) = strdup2(driver.helper->tac_sub_expression({ { false, (yystack_[2].value.str_val), 0, }, { false, (yystack_[0].value.str_val), 0, }, TacOperation::MOD }).c_str());
  }
#line 756 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 29: // comparison_operator: TOK_EQ
#line 267 "parse.yy"
         {
    (yylhs.value.op) = TacOperation::EQ;
  }
#line 764 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 30: // comparison_operator: TOK_NEQ
#line 270 "parse.yy"
            {
    (yylhs.value.op) = TacOperation::NE;
  }
#line 772 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 31: // comparison_operator: TOK_LT
#line 273 "parse.yy"
           {
    (yylhs.value.op) = TacOperation::LT;
  }
#line 780 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 32: // comparison_operator: TOK_LEQ
#line 276 "parse.yy"
            {
    (yylhs.value.op) = TacOperation::LE;
  }
#line 788 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 33: // comparison_operator: TOK_GT
#line 279 "parse.yy"
           {
    (yylhs.value.op) = TacOperation::GT;
  }
#line 796 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 34: // comparison_operator: TOK_GEQ
#line 282 "parse.yy"
            {
    (yylhs.value.op) = TacOperation::GE;
  }
#line 804 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 35: // compare_expression: TOK_ID comparison_operator TOK_ID
#line 288 "parse.yy"
                                    {
    (yylhs.value.expression_val).left.is_int_literal = false; (yylhs.value.expression_val).right.is_int_literal = false;
    (yylhs.value.expression_val).left.var_ref = (yystack_[2].value.str_val); (yylhs.value.expression_val).op = (yystack_[1].value.op); (yylhs.value.expression_val).right.var_ref = (yystack_[0].value.str_val);
  }
#line 813 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 36: // compare_expression: TOK_ID comparison_operator TOK_INT_LITERAL
#line 292 "parse.yy"
                                               {
    (yylhs.value.expression_val).left.is_int_literal = false; (yylhs.value.expression_val).right.is_int_literal = true;
    (yylhs.value.expression_val).left.var_ref = (yystack_[2].value.str_val); (yylhs.value.expression_val).op = (yystack_[1].value.op); (yylhs.value.expression_val).right.int_val = (yystack_[0].value.int_val);
  }
#line 822 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 37: // compare_expression: TOK_INT_LITERAL comparison_operator TOK_ID
#line 296 "parse.yy"
                                               {
    (yylhs.value.expression_val).left.is_int_literal = true; (yylhs.value.expression_val).right.is_int_literal = false;
    (yylhs.value.expression_val).left.int_val = (yystack_[2].value.int_val); (yylhs.value.expression_val).op = (yystack_[1].value.op); (yylhs.value.expression_val).right.var_ref = (yystack_[0].value.str_val);
  }
#line 831 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 38: // compare_expression: TOK_INT_LITERAL comparison_operator TOK_INT_LITERAL
#line 300 "parse.yy"
                                                        {
    (yylhs.value.expression_val).left.is_int_literal = true; (yylhs.value.expression_val).right.is_int_literal = true;
    (yylhs.value.expression_val).left.int_val = (yystack_[2].value.int_val); (yylhs.value.expression_val).op = (yystack_[1].value.op); (yylhs.value.expression_val).right.int_val = (yystack_[0].value.int_val);
  }
#line 840 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 39: // if: if_head block
#line 311 "parse.yy"
      {
      std::cout << "PARSER: IF declaration end: " << " " << std::endl;

      driver.helper->tac_if_after_block_declaration();
    }
#line 850 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 40: // $@1: %empty
#line 316 "parse.yy"
                             {
      std::cout << "PARSER: ELSE declaration start: " << std::endl;

      driver.helper->tac_else_midrule_declaration();
    }
#line 860 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 41: // if: if_head block TOK_ELSE $@1 block
#line 321 "parse.yy"
      {
      std::cout << "PARSER: ELSE declaration end: " << " " << std::endl;

      driver.helper->tac_else_after_block_declaration();
    }
#line 870 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 42: // if_head: TOK_IF TOK_LPAREN compare_expression TOK_RPAREN
#line 336 "parse.yy"
    {
      std::cout << "PARSER: IF declaration start: " << std::endl;

      driver.helper->tac_if_midrule_declaration((yystack_[1].value.expression_val));
    }
#line 880 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 44: // type: TOK_INT
#line 354 "parse.yy"
          { 
    (yylhs.value.type_val).symbol_type = slicc_tac::SymbolType::INT; 
    (yylhs.value.type_val).arr_element_amount = 0;
  }
#line 889 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 45: // type: TOK_INT_ARRAY TOK_INT_LITERAL TOK_RBRACKET
#line 358 "parse.yy"
                                                           { 
    (yylhs.value.type_val).symbol_type = slicc_tac::SymbolType::INT_ARRAY; 
    (yylhs.value.type_val).arr_element_amount = (yystack_[1].value.int_val);
  }
#line 898 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 51: // func_def: TOK_FUNC type TOK_ID TOK_LPAREN func_args_def TOK_RPAREN block
#line 382 "parse.yy"
      {
        driver.add_symbol_table_entry(
          strdup2((yystack_[4].value.str_val)),
          slicc_tac::SymbolType::FUNCTION,
          yystack_[6].location.begin.line,
          0,
          strdup2("main"),
          0,
          false
        );
        driver.identify_parent(strdup2((yystack_[4].value.str_val)));
      }
#line 915 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;

  case 52: // func_def: TOK_FUNC TOK_VOID TOK_ID TOK_LPAREN func_args_def TOK_RPAREN block
#line 395 "parse.yy"
      {
        driver.add_symbol_table_entry(
          strdup2((yystack_[4].value.str_val)),
          slicc_tac::SymbolType::FUNCTION,
          yystack_[6].location.begin.line,
          0,
          strdup2("main"),
          0,
          false
        );
        driver.identify_parent(strdup2((yystack_[4].value.str_val)));
      }
#line 932 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"
    break;


#line 936 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -50;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      21,     5,    27,    60,    15,   -50,    54,   -50,    60,     1,
     -50,   -50,    72,    47,    59,   -50,    58,    69,    55,     3,
      67,     8,    62,   -50,     8,    73,   -50,    15,   -50,    74,
      75,    77,    78,    80,    64,    64,   -50,   -50,     4,    66,
      55,    55,   -50,   -50,   -50,   -50,   -50,    84,   -15,   -50,
     -50,    48,    48,    16,    16,    81,    79,   -50,    55,    55,
      55,    55,    55,    82,    85,    11,    86,    28,   -50,   -50,
      89,    62,    91,    88,    87,    90,   -50,   -50,   -50,   -50,
     -50,   -50,    68,    70,   -50,    93,    28,    28,    28,    28,
      28,    92,    94,    55,   -50,    15,    95,    96,   -50,    15,
      48,    15,   -50,   -50,   -50,   -50,    -2,   100,    55,    55,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,    15,    28,    28,
     -50
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     1,     0,     3,    49,     0,
       4,    44,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     8,     7,    12,     0,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,    22,    23,     0,     0,
       0,     0,     5,     6,     9,    13,    14,    39,     0,    17,
      45,     0,     0,     0,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,    47,     0,    19,    40,    10,
       0,     0,     0,     0,    53,     0,    29,    30,    31,    32,
      33,    34,     0,     0,    42,     0,    24,    25,    26,    27,
      28,     0,     0,     0,    46,     0,     0,     0,    55,     0,
       0,     0,    38,    37,    36,    35,     0,     0,     0,     0,
      48,    41,    11,    56,    52,    54,    51,     0,    20,    21,
      43
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -50,   -50,   -50,   -25,   -50,    97,   -50,    38,   -50,    18,
     -18,    57,    98,   -50,   -50,   -50,   -50,    -5,   -50,    19,
     105,   -50,   -49,   -50
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,    10,    20,    21,    22,    23,    24,    25,
      65,    82,    55,    26,    95,    27,    28,    72,    30,    66,
       7,     8,    73,    74
  };

  const signed char
  Parser::yytable_[] =
  {
      38,    14,    47,    75,    29,    16,    69,    17,    70,    18,
      11,    12,    16,    39,    17,    19,    18,    29,    39,     4,
      40,    41,    19,    67,     1,    57,    41,     5,    58,    59,
      60,    61,    62,    93,     9,    58,    59,    60,    61,    62,
      86,    87,    88,    89,    90,    76,    77,    78,    79,    80,
      81,   115,    58,    59,    60,    61,    62,    11,    12,    43,
      71,    32,    45,    11,    12,    13,    97,     6,    36,    37,
     111,    11,    12,    33,   114,    34,   116,    53,    54,    63,
      64,   102,   103,   104,   105,    31,    35,    42,    48,    68,
     118,   119,   120,    50,    46,    51,    49,    52,    91,    84,
      85,    92,    96,   107,    94,    98,    99,   106,   101,   100,
     113,    83,   110,    15,     0,   108,   112,   109,   117,    44,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    56
  };

  const signed char
  Parser::yycheck_[] =
  {
      18,     6,    27,    52,     9,     4,    21,     6,    23,     8,
       9,    10,     4,    15,     6,    14,     8,    22,    15,    14,
      17,    23,    14,    41,     3,    21,    23,     0,    24,    25,
      26,    27,    28,    22,    19,    24,    25,    26,    27,    28,
      58,    59,    60,    61,    62,    29,    30,    31,    32,    33,
      34,   100,    24,    25,    26,    27,    28,     9,    10,    21,
      12,    14,    24,     9,    10,    11,    71,     7,    13,    14,
      95,     9,    10,    14,    99,    17,   101,    13,    14,    13,
      14,    13,    14,    13,    14,    13,    17,    20,    14,     5,
     108,   109,   117,    16,    21,    17,    21,    17,    16,    18,
      21,    16,    13,    85,    18,    14,    18,    14,    18,    22,
      14,    54,    93,     8,    -1,    23,    21,    23,    18,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,    36,    37,    14,     0,     7,    55,    56,    19,
      38,     9,    10,    11,    52,    55,     4,     6,     8,    14,
      39,    40,    41,    42,    43,    44,    48,    50,    51,    52,
      53,    13,    14,    14,    17,    17,    13,    14,    45,    15,
      17,    23,    20,    42,    40,    42,    21,    38,    14,    21,
      16,    17,    17,    13,    14,    47,    47,    21,    24,    25,
      26,    27,    28,    13,    14,    45,    54,    45,     5,    21,
      23,    12,    52,    57,    58,    57,    29,    30,    31,    32,
      33,    34,    46,    46,    18,    21,    45,    45,    45,    45,
      45,    16,    16,    22,    18,    49,    13,    52,    14,    18,
      22,    18,    13,    14,    13,    14,    14,    44,    23,    23,
      54,    38,    21,    14,    38,    57,    38,    18,    45,    45,
      38
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    35,    36,    36,    37,    38,    39,    39,    40,    40,
      41,    41,    42,    42,    43,    43,    43,    43,    43,    44,
      44,    44,    45,    45,    45,    45,    45,    45,    45,    46,
      46,    46,    46,    46,    46,    47,    47,    47,    47,    48,
      49,    48,    50,    51,    52,    52,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     3,     2,     1,     1,     2,
       3,     5,     1,     2,     2,     1,     1,     2,     3,     3,
       6,     6,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     2,
       0,     5,     4,     7,     1,     3,     4,     1,     3,     1,
       2,     7,     7,     1,     3,     2,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "TOK_EOF", "error", "\"invalid token\"", "TOK_PROGRAM", "TOK_IF",
  "TOK_ELSE", "TOK_FOR", "TOK_FUNC", "TOK_RETURN", "TOK_INT",
  "TOK_INT_ARRAY", "TOK_VOID", "TOK_REF", "TOK_INT_LITERAL", "TOK_ID",
  "TOK_LBRACKET", "TOK_RBRACKET", "TOK_LPAREN", "TOK_RPAREN", "TOK_LBRACE",
  "TOK_RBRACE", "TOK_SEMICOLON", "TOK_COMMA", "TOK_ASSIGN", "TOK_PLUS",
  "TOK_MINUS", "TOK_MUL", "TOK_DIV", "TOK_MOD", "TOK_EQ", "TOK_NEQ",
  "TOK_LT", "TOK_LEQ", "TOK_GT", "TOK_GEQ", "$accept", "main", "program",
  "block", "block_body", "variable_list", "variable_declaration",
  "statement_list", "statement", "statement_assignment", "expression",
  "comparison_operator", "compare_expression", "if", "$@1", "if_head",
  "for", "type", "func_call", "func_args", "func_def_list", "func_def",
  "func_args_def", "func_arg_def", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   117,   117,   118,   122,   145,   151,   152,   156,   157,
     163,   187,   210,   211,   216,   217,   218,   219,   220,   225,
     229,   230,   235,   238,   242,   245,   248,   251,   254,   267,
     270,   273,   276,   279,   282,   288,   292,   296,   300,   310,
     316,   316,   335,   346,   354,   358,   367,   371,   372,   376,
     377,   381,   394,   410,   411,   415,   416
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
    };
    // Last valid token kind.
    const int code_max = 289;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 47 "parse.yy"
} // slang_parser
#line 1536 "/Users/linucc/code/projects/slic/slicc/src/slang_parser/parser.cc"

#line 419 "parse.yy"


/*
 * Simple Fehlerbehandlung für den Parser
 */
namespace slang_parser
{
    void Parser::error(const location& l, const std::string& m)
    {
        std::cerr << l << ": " << m << std::endl;
        driver.error = (driver.error == 127 ? 127 : driver.error + 1);
    }
}

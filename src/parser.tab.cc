// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 41 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"

    #include <iostream>
    #include <cstdlib>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <algorithm>
    #include <tuple>
    /* include for all driver functions */
    #include "tt.h"

    extern TOY_COMPILER::GlobalSymbol *globalsymtab;

    extern TOY_COMPILER::rootProgram * root;

#undef yylex
#define yylex scanner.yylex

#line 65 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"


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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 20 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
namespace TOY_COMPILER {
#line 158 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"

  /// Build a parser object.
  Parser::Parser (Scanner &scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.copy< abstractExpr * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_simple_type_decl: // simple_type_decl
        value.copy< abstractSimpleDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_non_label_stmt: // non_label_stmt
      case symbol_kind::S_else_clause: // else_clause
        value.copy< abstractStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.copy< abstractTypeDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type_decl: // array_type_decl
        value.copy< arrayDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.copy< assignStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_direction: // direction
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.copy< caseNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_stmt: // case_stmt
      case symbol_kind::S_case_expr_list: // case_expr_list
        value.copy< caseStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.copy< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_const_part: // const_part
      case symbol_kind::S_const_expr_list: // const_expr_list
        value.copy< constDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_REAL: // REAL
        value.copy< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.copy< field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_stmt: // for_stmt
        value.copy< forStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_stmt: // proc_stmt
        value.copy< functionCall * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_procedure_decl: // procedure_decl
        value.copy< functionNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_goto_stmt: // goto_stmt
        value.copy< gotoStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.copy< ifStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SYS_CON: // SYS_CON
      case symbol_kind::S_SYS_FUNCT: // SYS_FUNCT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_SYS_PROC: // SYS_PROC
      case symbol_kind::S_SYS_TYPE: // SYS_TYPE
      case symbol_kind::S_INTEGER: // INTEGER
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_const_value: // const_value
        value.copy< literal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_para_type_list: // para_type_list
        value.copy< parameter * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_record_type_decl: // record_type_decl
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.copy< recordDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_repeat_stmt: // repeat_stmt
        value.copy< repeatStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine: // routine
      case symbol_kind::S_sub_routine: // sub_routine
        value.copy< rootProgram* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine_head: // routine_head
        value.copy< std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program_head: // program_head
        value.copy< std::string* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_head: // function_head
        value.copy< std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_procedure_head: // procedure_head
        value.copy< std::tuple<std::string, std::vector<parameter *> *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_args_list: // args_list
        value.copy< std::vector<abstractExpr *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine_part: // routine_part
        value.copy< std::vector<functionNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_para_decl_list: // para_decl_list
        value.copy< std::vector<parameter *>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name_list: // name_list
      case symbol_kind::S_var_para_list: // var_para_list
      case symbol_kind::S_val_para_list: // val_para_list
        value.copy< std::vector<std::string>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine_body: // routine_body
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< stmtList * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_part: // type_part
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.copy< typeDefDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_part: // var_part
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.copy< varDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_definition: // type_definition
      case symbol_kind::S_var_decl: // var_decl
        value.copy< varNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.copy< whileStmt* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



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
    switch (this->kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< abstractExpr * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_simple_type_decl: // simple_type_decl
        value.move< abstractSimpleDecl * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_non_label_stmt: // non_label_stmt
      case symbol_kind::S_else_clause: // else_clause
        value.move< abstractStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< abstractTypeDeclNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_array_type_decl: // array_type_decl
        value.move< arrayDecl* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.move< assignStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_direction: // direction
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.move< caseNode* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_case_stmt: // case_stmt
      case symbol_kind::S_case_expr_list: // case_expr_list
        value.move< caseStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.move< char > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_const_part: // const_part
      case symbol_kind::S_const_expr_list: // const_expr_list
        value.move< constDecl * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_REAL: // REAL
        value.move< double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< field* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_for_stmt: // for_stmt
        value.move< forStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_proc_stmt: // proc_stmt
        value.move< functionCall * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_procedure_decl: // procedure_decl
        value.move< functionNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_goto_stmt: // goto_stmt
        value.move< gotoStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ifStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_SYS_CON: // SYS_CON
      case symbol_kind::S_SYS_FUNCT: // SYS_FUNCT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_SYS_PROC: // SYS_PROC
      case symbol_kind::S_SYS_TYPE: // SYS_TYPE
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_const_value: // const_value
        value.move< literal* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_para_type_list: // para_type_list
        value.move< parameter * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_record_type_decl: // record_type_decl
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< recordDecl * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_repeat_stmt: // repeat_stmt
        value.move< repeatStmt* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_routine: // routine
      case symbol_kind::S_sub_routine: // sub_routine
        value.move< rootProgram* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_routine_head: // routine_head
        value.move< std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program_head: // program_head
        value.move< std::string* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_function_head: // function_head
        value.move< std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_procedure_head: // procedure_head
        value.move< std::tuple<std::string, std::vector<parameter *> *> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_args_list: // args_list
        value.move< std::vector<abstractExpr *> * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_routine_part: // routine_part
        value.move< std::vector<functionNode *> * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_para_decl_list: // para_decl_list
        value.move< std::vector<parameter *>* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_name_list: // name_list
      case symbol_kind::S_var_para_list: // var_para_list
      case symbol_kind::S_val_para_list: // val_para_list
        value.move< std::vector<std::string>* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_routine_body: // routine_body
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< stmtList * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_part: // type_part
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.move< typeDefDecl * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_var_part: // var_part
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.move< varDecl * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_definition: // type_definition
      case symbol_kind::S_var_decl: // var_decl
        value.move< varNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< whileStmt* > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  Parser::by_kind::clear ()
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
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.YY_MOVE_OR_COPY< abstractExpr * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_simple_type_decl: // simple_type_decl
        value.YY_MOVE_OR_COPY< abstractSimpleDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_non_label_stmt: // non_label_stmt
      case symbol_kind::S_else_clause: // else_clause
        value.YY_MOVE_OR_COPY< abstractStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.YY_MOVE_OR_COPY< abstractTypeDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type_decl: // array_type_decl
        value.YY_MOVE_OR_COPY< arrayDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.YY_MOVE_OR_COPY< assignStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_direction: // direction
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.YY_MOVE_OR_COPY< caseNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_stmt: // case_stmt
      case symbol_kind::S_case_expr_list: // case_expr_list
        value.YY_MOVE_OR_COPY< caseStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.YY_MOVE_OR_COPY< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_const_part: // const_part
      case symbol_kind::S_const_expr_list: // const_expr_list
        value.YY_MOVE_OR_COPY< constDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_REAL: // REAL
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.YY_MOVE_OR_COPY< field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_stmt: // for_stmt
        value.YY_MOVE_OR_COPY< forStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_stmt: // proc_stmt
        value.YY_MOVE_OR_COPY< functionCall * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_procedure_decl: // procedure_decl
        value.YY_MOVE_OR_COPY< functionNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_goto_stmt: // goto_stmt
        value.YY_MOVE_OR_COPY< gotoStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.YY_MOVE_OR_COPY< ifStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SYS_CON: // SYS_CON
      case symbol_kind::S_SYS_FUNCT: // SYS_FUNCT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_SYS_PROC: // SYS_PROC
      case symbol_kind::S_SYS_TYPE: // SYS_TYPE
      case symbol_kind::S_INTEGER: // INTEGER
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_const_value: // const_value
        value.YY_MOVE_OR_COPY< literal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_para_type_list: // para_type_list
        value.YY_MOVE_OR_COPY< parameter * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_record_type_decl: // record_type_decl
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.YY_MOVE_OR_COPY< recordDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_repeat_stmt: // repeat_stmt
        value.YY_MOVE_OR_COPY< repeatStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine: // routine
      case symbol_kind::S_sub_routine: // sub_routine
        value.YY_MOVE_OR_COPY< rootProgram* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine_head: // routine_head
        value.YY_MOVE_OR_COPY< std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program_head: // program_head
        value.YY_MOVE_OR_COPY< std::string* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_head: // function_head
        value.YY_MOVE_OR_COPY< std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_procedure_head: // procedure_head
        value.YY_MOVE_OR_COPY< std::tuple<std::string, std::vector<parameter *> *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_args_list: // args_list
        value.YY_MOVE_OR_COPY< std::vector<abstractExpr *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine_part: // routine_part
        value.YY_MOVE_OR_COPY< std::vector<functionNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_para_decl_list: // para_decl_list
        value.YY_MOVE_OR_COPY< std::vector<parameter *>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name_list: // name_list
      case symbol_kind::S_var_para_list: // var_para_list
      case symbol_kind::S_val_para_list: // val_para_list
        value.YY_MOVE_OR_COPY< std::vector<std::string>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine_body: // routine_body
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< stmtList * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_part: // type_part
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.YY_MOVE_OR_COPY< typeDefDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_part: // var_part
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.YY_MOVE_OR_COPY< varDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_definition: // type_definition
      case symbol_kind::S_var_decl: // var_decl
        value.YY_MOVE_OR_COPY< varNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.YY_MOVE_OR_COPY< whileStmt* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< abstractExpr * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_simple_type_decl: // simple_type_decl
        value.move< abstractSimpleDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_non_label_stmt: // non_label_stmt
      case symbol_kind::S_else_clause: // else_clause
        value.move< abstractStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< abstractTypeDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type_decl: // array_type_decl
        value.move< arrayDecl* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.move< assignStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_direction: // direction
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.move< caseNode* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_stmt: // case_stmt
      case symbol_kind::S_case_expr_list: // case_expr_list
        value.move< caseStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.move< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_const_part: // const_part
      case symbol_kind::S_const_expr_list: // const_expr_list
        value.move< constDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_REAL: // REAL
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< field* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_for_stmt: // for_stmt
        value.move< forStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_stmt: // proc_stmt
        value.move< functionCall * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_procedure_decl: // procedure_decl
        value.move< functionNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_goto_stmt: // goto_stmt
        value.move< gotoStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ifStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SYS_CON: // SYS_CON
      case symbol_kind::S_SYS_FUNCT: // SYS_FUNCT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_SYS_PROC: // SYS_PROC
      case symbol_kind::S_SYS_TYPE: // SYS_TYPE
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_const_value: // const_value
        value.move< literal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_para_type_list: // para_type_list
        value.move< parameter * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_record_type_decl: // record_type_decl
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< recordDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_repeat_stmt: // repeat_stmt
        value.move< repeatStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine: // routine
      case symbol_kind::S_sub_routine: // sub_routine
        value.move< rootProgram* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine_head: // routine_head
        value.move< std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program_head: // program_head
        value.move< std::string* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_head: // function_head
        value.move< std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_procedure_head: // procedure_head
        value.move< std::tuple<std::string, std::vector<parameter *> *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_args_list: // args_list
        value.move< std::vector<abstractExpr *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine_part: // routine_part
        value.move< std::vector<functionNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_para_decl_list: // para_decl_list
        value.move< std::vector<parameter *>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name_list: // name_list
      case symbol_kind::S_var_para_list: // var_para_list
      case symbol_kind::S_val_para_list: // val_para_list
        value.move< std::vector<std::string>* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_routine_body: // routine_body
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< stmtList * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_part: // type_part
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.move< typeDefDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_part: // var_part
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.move< varDecl * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_definition: // type_definition
      case symbol_kind::S_var_decl: // var_decl
        value.move< varNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< whileStmt* > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.copy< abstractExpr * > (that.value);
        break;

      case symbol_kind::S_simple_type_decl: // simple_type_decl
        value.copy< abstractSimpleDecl * > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_non_label_stmt: // non_label_stmt
      case symbol_kind::S_else_clause: // else_clause
        value.copy< abstractStmt* > (that.value);
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.copy< abstractTypeDeclNode * > (that.value);
        break;

      case symbol_kind::S_array_type_decl: // array_type_decl
        value.copy< arrayDecl* > (that.value);
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.copy< assignStmt* > (that.value);
        break;

      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_direction: // direction
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.copy< caseNode* > (that.value);
        break;

      case symbol_kind::S_case_stmt: // case_stmt
      case symbol_kind::S_case_expr_list: // case_expr_list
        value.copy< caseStmt* > (that.value);
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.copy< char > (that.value);
        break;

      case symbol_kind::S_const_part: // const_part
      case symbol_kind::S_const_expr_list: // const_expr_list
        value.copy< constDecl * > (that.value);
        break;

      case symbol_kind::S_REAL: // REAL
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.copy< field* > (that.value);
        break;

      case symbol_kind::S_for_stmt: // for_stmt
        value.copy< forStmt* > (that.value);
        break;

      case symbol_kind::S_proc_stmt: // proc_stmt
        value.copy< functionCall * > (that.value);
        break;

      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_procedure_decl: // procedure_decl
        value.copy< functionNode * > (that.value);
        break;

      case symbol_kind::S_goto_stmt: // goto_stmt
        value.copy< gotoStmt* > (that.value);
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.copy< ifStmt* > (that.value);
        break;

      case symbol_kind::S_SYS_CON: // SYS_CON
      case symbol_kind::S_SYS_FUNCT: // SYS_FUNCT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_SYS_PROC: // SYS_PROC
      case symbol_kind::S_SYS_TYPE: // SYS_TYPE
      case symbol_kind::S_INTEGER: // INTEGER
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_const_value: // const_value
        value.copy< literal* > (that.value);
        break;

      case symbol_kind::S_para_type_list: // para_type_list
        value.copy< parameter * > (that.value);
        break;

      case symbol_kind::S_record_type_decl: // record_type_decl
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.copy< recordDecl * > (that.value);
        break;

      case symbol_kind::S_repeat_stmt: // repeat_stmt
        value.copy< repeatStmt* > (that.value);
        break;

      case symbol_kind::S_routine: // routine
      case symbol_kind::S_sub_routine: // sub_routine
        value.copy< rootProgram* > (that.value);
        break;

      case symbol_kind::S_routine_head: // routine_head
        value.copy< std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_program_head: // program_head
        value.copy< std::string* > (that.value);
        break;

      case symbol_kind::S_function_head: // function_head
        value.copy< std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > (that.value);
        break;

      case symbol_kind::S_procedure_head: // procedure_head
        value.copy< std::tuple<std::string, std::vector<parameter *> *> > (that.value);
        break;

      case symbol_kind::S_args_list: // args_list
        value.copy< std::vector<abstractExpr *> * > (that.value);
        break;

      case symbol_kind::S_routine_part: // routine_part
        value.copy< std::vector<functionNode *> * > (that.value);
        break;

      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_para_decl_list: // para_decl_list
        value.copy< std::vector<parameter *>* > (that.value);
        break;

      case symbol_kind::S_name_list: // name_list
      case symbol_kind::S_var_para_list: // var_para_list
      case symbol_kind::S_val_para_list: // val_para_list
        value.copy< std::vector<std::string>* > (that.value);
        break;

      case symbol_kind::S_routine_body: // routine_body
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< stmtList * > (that.value);
        break;

      case symbol_kind::S_type_part: // type_part
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.copy< typeDefDecl * > (that.value);
        break;

      case symbol_kind::S_var_part: // var_part
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.copy< varDecl * > (that.value);
        break;

      case symbol_kind::S_type_definition: // type_definition
      case symbol_kind::S_var_decl: // var_decl
        value.copy< varNode * > (that.value);
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.copy< whileStmt* > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< abstractExpr * > (that.value);
        break;

      case symbol_kind::S_simple_type_decl: // simple_type_decl
        value.move< abstractSimpleDecl * > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_non_label_stmt: // non_label_stmt
      case symbol_kind::S_else_clause: // else_clause
        value.move< abstractStmt* > (that.value);
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< abstractTypeDeclNode * > (that.value);
        break;

      case symbol_kind::S_array_type_decl: // array_type_decl
        value.move< arrayDecl* > (that.value);
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.move< assignStmt* > (that.value);
        break;

      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_direction: // direction
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.move< caseNode* > (that.value);
        break;

      case symbol_kind::S_case_stmt: // case_stmt
      case symbol_kind::S_case_expr_list: // case_expr_list
        value.move< caseStmt* > (that.value);
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.move< char > (that.value);
        break;

      case symbol_kind::S_const_part: // const_part
      case symbol_kind::S_const_expr_list: // const_expr_list
        value.move< constDecl * > (that.value);
        break;

      case symbol_kind::S_REAL: // REAL
        value.move< double > (that.value);
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< field* > (that.value);
        break;

      case symbol_kind::S_for_stmt: // for_stmt
        value.move< forStmt* > (that.value);
        break;

      case symbol_kind::S_proc_stmt: // proc_stmt
        value.move< functionCall * > (that.value);
        break;

      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_procedure_decl: // procedure_decl
        value.move< functionNode * > (that.value);
        break;

      case symbol_kind::S_goto_stmt: // goto_stmt
        value.move< gotoStmt* > (that.value);
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ifStmt* > (that.value);
        break;

      case symbol_kind::S_SYS_CON: // SYS_CON
      case symbol_kind::S_SYS_FUNCT: // SYS_FUNCT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_SYS_PROC: // SYS_PROC
      case symbol_kind::S_SYS_TYPE: // SYS_TYPE
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< int > (that.value);
        break;

      case symbol_kind::S_const_value: // const_value
        value.move< literal* > (that.value);
        break;

      case symbol_kind::S_para_type_list: // para_type_list
        value.move< parameter * > (that.value);
        break;

      case symbol_kind::S_record_type_decl: // record_type_decl
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< recordDecl * > (that.value);
        break;

      case symbol_kind::S_repeat_stmt: // repeat_stmt
        value.move< repeatStmt* > (that.value);
        break;

      case symbol_kind::S_routine: // routine
      case symbol_kind::S_sub_routine: // sub_routine
        value.move< rootProgram* > (that.value);
        break;

      case symbol_kind::S_routine_head: // routine_head
        value.move< std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_program_head: // program_head
        value.move< std::string* > (that.value);
        break;

      case symbol_kind::S_function_head: // function_head
        value.move< std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > (that.value);
        break;

      case symbol_kind::S_procedure_head: // procedure_head
        value.move< std::tuple<std::string, std::vector<parameter *> *> > (that.value);
        break;

      case symbol_kind::S_args_list: // args_list
        value.move< std::vector<abstractExpr *> * > (that.value);
        break;

      case symbol_kind::S_routine_part: // routine_part
        value.move< std::vector<functionNode *> * > (that.value);
        break;

      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_para_decl_list: // para_decl_list
        value.move< std::vector<parameter *>* > (that.value);
        break;

      case symbol_kind::S_name_list: // name_list
      case symbol_kind::S_var_para_list: // var_para_list
      case symbol_kind::S_val_para_list: // val_para_list
        value.move< std::vector<std::string>* > (that.value);
        break;

      case symbol_kind::S_routine_body: // routine_body
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< stmtList * > (that.value);
        break;

      case symbol_kind::S_type_part: // type_part
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.move< typeDefDecl * > (that.value);
        break;

      case symbol_kind::S_var_part: // var_part
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.move< varDecl * > (that.value);
        break;

      case symbol_kind::S_type_definition: // type_definition
      case symbol_kind::S_var_decl: // var_decl
        value.move< varNode * > (that.value);
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< whileStmt* > (that.value);
        break;

      default:
        break;
    }

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
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
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
  Parser::yypop_ (int n)
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
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
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
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
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
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        yylhs.value.emplace< abstractExpr * > ();
        break;

      case symbol_kind::S_simple_type_decl: // simple_type_decl
        yylhs.value.emplace< abstractSimpleDecl * > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_non_label_stmt: // non_label_stmt
      case symbol_kind::S_else_clause: // else_clause
        yylhs.value.emplace< abstractStmt* > ();
        break;

      case symbol_kind::S_type_decl: // type_decl
        yylhs.value.emplace< abstractTypeDeclNode * > ();
        break;

      case symbol_kind::S_array_type_decl: // array_type_decl
        yylhs.value.emplace< arrayDecl* > ();
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        yylhs.value.emplace< assignStmt* > ();
        break;

      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_direction: // direction
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_case_expr: // case_expr
        yylhs.value.emplace< caseNode* > ();
        break;

      case symbol_kind::S_case_stmt: // case_stmt
      case symbol_kind::S_case_expr_list: // case_expr_list
        yylhs.value.emplace< caseStmt* > ();
        break;

      case symbol_kind::S_CHAR: // CHAR
        yylhs.value.emplace< char > ();
        break;

      case symbol_kind::S_const_part: // const_part
      case symbol_kind::S_const_expr_list: // const_expr_list
        yylhs.value.emplace< constDecl * > ();
        break;

      case symbol_kind::S_REAL: // REAL
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_field_decl: // field_decl
        yylhs.value.emplace< field* > ();
        break;

      case symbol_kind::S_for_stmt: // for_stmt
        yylhs.value.emplace< forStmt* > ();
        break;

      case symbol_kind::S_proc_stmt: // proc_stmt
        yylhs.value.emplace< functionCall * > ();
        break;

      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_procedure_decl: // procedure_decl
        yylhs.value.emplace< functionNode * > ();
        break;

      case symbol_kind::S_goto_stmt: // goto_stmt
        yylhs.value.emplace< gotoStmt* > ();
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        yylhs.value.emplace< ifStmt* > ();
        break;

      case symbol_kind::S_SYS_CON: // SYS_CON
      case symbol_kind::S_SYS_FUNCT: // SYS_FUNCT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_SYS_PROC: // SYS_PROC
      case symbol_kind::S_SYS_TYPE: // SYS_TYPE
      case symbol_kind::S_INTEGER: // INTEGER
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_const_value: // const_value
        yylhs.value.emplace< literal* > ();
        break;

      case symbol_kind::S_para_type_list: // para_type_list
        yylhs.value.emplace< parameter * > ();
        break;

      case symbol_kind::S_record_type_decl: // record_type_decl
      case symbol_kind::S_field_decl_list: // field_decl_list
        yylhs.value.emplace< recordDecl * > ();
        break;

      case symbol_kind::S_repeat_stmt: // repeat_stmt
        yylhs.value.emplace< repeatStmt* > ();
        break;

      case symbol_kind::S_routine: // routine
      case symbol_kind::S_sub_routine: // sub_routine
        yylhs.value.emplace< rootProgram* > ();
        break;

      case symbol_kind::S_routine_head: // routine_head
        yylhs.value.emplace< std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > ();
        break;

      case symbol_kind::S_ID: // ID
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_program_head: // program_head
        yylhs.value.emplace< std::string* > ();
        break;

      case symbol_kind::S_function_head: // function_head
        yylhs.value.emplace< std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > ();
        break;

      case symbol_kind::S_procedure_head: // procedure_head
        yylhs.value.emplace< std::tuple<std::string, std::vector<parameter *> *> > ();
        break;

      case symbol_kind::S_args_list: // args_list
        yylhs.value.emplace< std::vector<abstractExpr *> * > ();
        break;

      case symbol_kind::S_routine_part: // routine_part
        yylhs.value.emplace< std::vector<functionNode *> * > ();
        break;

      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_para_decl_list: // para_decl_list
        yylhs.value.emplace< std::vector<parameter *>* > ();
        break;

      case symbol_kind::S_name_list: // name_list
      case symbol_kind::S_var_para_list: // var_para_list
      case symbol_kind::S_val_para_list: // val_para_list
        yylhs.value.emplace< std::vector<std::string>* > ();
        break;

      case symbol_kind::S_routine_body: // routine_body
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< stmtList * > ();
        break;

      case symbol_kind::S_type_part: // type_part
      case symbol_kind::S_type_decl_list: // type_decl_list
        yylhs.value.emplace< typeDefDecl * > ();
        break;

      case symbol_kind::S_var_part: // var_part
      case symbol_kind::S_var_decl_list: // var_decl_list
        yylhs.value.emplace< varDecl * > ();
        break;

      case symbol_kind::S_type_definition: // type_definition
      case symbol_kind::S_var_decl: // var_decl
        yylhs.value.emplace< varNode * > ();
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        yylhs.value.emplace< whileStmt* > ();
        break;

      default:
        break;
    }


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
  case 2: // program: program_head routine DOT
#line 167 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            //auto t = globalsymtab->newSymTable($1);
            // globalsymtab->SymTable.insert()
            root = yystack_[1].value.as < rootProgram* > ();
        }
#line 1877 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 3: // program_head: PROGRAM ID SEMI
#line 176 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::string* > () = new std::string(yystack_[1].value.as < std::string > ()); // program head can be just a string
        }
#line 1885 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 4: // routine: routine_head routine_body
#line 182 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < rootProgram* > () = new rootProgram();
            yylhs.value.as < rootProgram* > ()->getDecls() = std::move(*(yystack_[1].value.as < std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > ().first));
            yylhs.value.as < rootProgram* > ()->getFuncs() = std::move(*(yystack_[1].value.as < std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > ().second));
            yylhs.value.as < rootProgram* > ()->getStmts() = std::move(*(yystack_[0].value.as < stmtList * > ()));
            yylhs.value.as < rootProgram* > ()->setLineno(yylhs.location.begin.line);
        }
#line 1897 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 5: // sub_routine: routine_head routine_body
#line 193 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {

        }
#line 1905 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 6: // routine_head: label_part const_part type_part var_part routine_part
#line 200 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
        	auto decls = new std::vector<abstractTypeDeclNode *>();
            auto f = [=](abstractTypeDeclNode *d) {
                decls->push_back(d);
            };
            decls->push_back(yystack_[3].value.as < constDecl * > ());
            decls->push_back(yystack_[2].value.as < typeDefDecl * > ());
            decls->push_back(yystack_[1].value.as < varDecl * > ());
            yylhs.value.as < std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > () = std::make_pair(decls, yystack_[0].value.as < std::vector<functionNode *> * > ());
        }
#line 1920 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 7: // label_part: %empty
#line 213 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
        }
#line 1927 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 8: // const_part: CONST const_expr_list
#line 219 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < constDecl * > () = yystack_[0].value.as < constDecl * > ();
        }
#line 1935 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 9: // const_part: %empty
#line 223 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
        }
#line 1942 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 10: // const_expr_list: const_expr_list ID EQUAL const_value SEMI
#line 229 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < constDecl * > ()->addConstDecl(yystack_[3].value.as < std::string > (), yystack_[1].value.as < literal* > ());
        }
#line 1950 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 11: // const_expr_list: ID EQUAL const_value SEMI
#line 233 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < constDecl * > () = new constDecl();
            yylhs.value.as < constDecl * > ()->addConstDecl(yystack_[3].value.as < std::string > (), yystack_[1].value.as < literal* > ());
            yylhs.value.as < constDecl * > ()->setLineno(yylhs.location.begin.line);
        }
#line 1960 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 12: // const_value: INTEGER
#line 242 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::INTEGER;
            v->int_value = yystack_[0].value.as < int > ();
            yylhs.value.as < literal* > () = new literal(v, t);
            yylhs.value.as < literal* > ()->setLineno(yystack_[0].location.begin.line);
        }
#line 1973 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 13: // const_value: REAL
#line 251 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::REAL;
            v->real_value = yystack_[0].value.as < double > ();
            yylhs.value.as < literal* > () = new literal(v, t);
            yylhs.value.as < literal* > ()->setLineno(yystack_[0].location.begin.line);
        }
#line 1986 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 14: // const_value: CHAR
#line 260 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::CHAR;
            v->char_value = yystack_[0].value.as < char > ();
            yylhs.value.as < literal* > () = new literal(v, t);
            yylhs.value.as < literal* > ()->setLineno(yystack_[0].location.begin.line);
        }
#line 1999 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 15: // const_value: BOOL
#line 269 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::BOOLEAN;
            v->bool_value = yystack_[0].value.as < bool > ();
            yylhs.value.as < literal* > () = new literal(v, t);
            yylhs.value.as < literal* > ()->setLineno(yystack_[0].location.begin.line);
        }
#line 2012 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 16: // const_value: SYS_CON
#line 278 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto t = new const_valueType();
            auto v = new expValue();
            if(yystack_[0].value.as < int > () == false) {
                t->sys_type = TOY_COMPILER::FALSE;
            } else if(yystack_[0].value.as < int > () == true) {
                t->sys_type = TOY_COMPILER::TRUE;
            } else if(yystack_[0].value.as < int > () == 2147483647) {
                t->sys_type = TOY_COMPILER::MAXINT;
            }
            v->bool_value = yystack_[0].value.as < int > ();
            yylhs.value.as < literal* > () = new literal(v, t);
            yylhs.value.as < literal* > ()->setLineno(yystack_[0].location.begin.line);
        }
#line 2031 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 17: // type_part: TYPE type_decl_list
#line 296 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < typeDefDecl * > () = yystack_[0].value.as < typeDefDecl * > ();
        }
#line 2039 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 18: // type_part: %empty
#line 300 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {

        }
#line 2047 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 19: // type_decl_list: type_decl_list type_definition
#line 307 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < typeDefDecl * > ()->addTypeDef(yystack_[0].value.as < varNode * > ());
        }
#line 2055 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 20: // type_decl_list: type_definition
#line 311 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < typeDefDecl * > () = new typeDefDecl();
            yylhs.value.as < typeDefDecl * > ()->addTypeDef(yystack_[0].value.as < varNode * > ());
            yylhs.value.as < typeDefDecl * > ()->setLineno(yylhs.location.begin.line);
        }
#line 2065 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 21: // type_definition: ID EQUAL type_decl SEMI
#line 320 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto ns = new std::vector<std::string>();
            ns->push_back(yystack_[3].value.as < std::string > ());
            yylhs.value.as < varNode * > () = new varNode(ns, yystack_[1].value.as < abstractTypeDeclNode * > ());
            yylhs.value.as < varNode * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2076 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 22: // type_decl: simple_type_decl
#line 330 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractTypeDeclNode * > () = yystack_[0].value.as < abstractSimpleDecl * > ();
        }
#line 2084 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 23: // type_decl: array_type_decl
#line 334 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractTypeDeclNode * > () = yystack_[0].value.as < arrayDecl* > ();
        }
#line 2092 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 24: // type_decl: record_type_decl
#line 338 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractTypeDeclNode * > () = yystack_[0].value.as < recordDecl * > ();
        }
#line 2100 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 25: // simple_type_decl: SYS_TYPE
#line 345 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            TOY_COMPILER::valType t;
            if (yystack_[0].value.as < int > () == 1)
                t = BOOLEAN;
            else if (yystack_[0].value.as < int > () == 2)
                t = CHAR;
            else if (yystack_[0].value.as < int > () == 3)
                t = INTEGER;
            else
                t = REAL;
            yylhs.value.as < abstractSimpleDecl * > () = new simpleDecl(t);
            yylhs.value.as < abstractSimpleDecl * > ()->setLineno(yystack_[0].location.begin.line);

        }
#line 2119 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 26: // simple_type_decl: ID
#line 360 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto name = new std::vector<std::string>();
            name->push_back(yystack_[0].value.as < std::string > ());

            yylhs.value.as < abstractSimpleDecl * > () = new namesDecl(*name, false);
            yylhs.value.as < abstractSimpleDecl * > ()->setLineno(yystack_[0].location.begin.line);
        }
#line 2131 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 27: // simple_type_decl: LP name_list RP
#line 368 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto names = new std::vector<std::string>();
            auto f = [=](std::string &name) {
                names->push_back(name);
            };
            for_each(yystack_[1].value.as < std::vector<std::string>* > ()->begin(), yystack_[1].value.as < std::vector<std::string>* > ()->end(), f);
            yylhs.value.as < abstractSimpleDecl * > () = new namesDecl(*names, false);
            yylhs.value.as < abstractSimpleDecl * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2145 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 28: // simple_type_decl: const_value DOTDOT const_value
#line 378 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractSimpleDecl * > () = new rangeDecl(false, yystack_[2].value.as < literal* > (), false, yystack_[0].value.as < literal* > ());
            yylhs.value.as < abstractSimpleDecl * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2154 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 29: // simple_type_decl: MINUS const_value DOTDOT const_value
#line 383 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractSimpleDecl * > () = new rangeDecl(true, yystack_[2].value.as < literal* > (), false, yystack_[0].value.as < literal* > ());
            yylhs.value.as < abstractSimpleDecl * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2163 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 30: // simple_type_decl: MINUS const_value DOTDOT MINUS const_value
#line 388 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractSimpleDecl * > () = new rangeDecl(true, yystack_[3].value.as < literal* > (), true, yystack_[0].value.as < literal* > ());
            yylhs.value.as < abstractSimpleDecl * > ()->setLineno(yystack_[4].location.begin.line);
        }
#line 2172 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 31: // simple_type_decl: ID DOTDOT ID
#line 393 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractSimpleDecl * > () = new rangeDecl(yystack_[2].value.as < std::string > (), yystack_[0].value.as < std::string > ());
            yylhs.value.as < abstractSimpleDecl * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2181 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 32: // array_type_decl: ARRAY LB simple_type_decl RB OF type_decl
#line 401 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < arrayDecl* > () = new arrayDecl(yystack_[3].value.as < abstractSimpleDecl * > (), yystack_[0].value.as < abstractTypeDeclNode * > ());
            yylhs.value.as < arrayDecl* > ()->setLineno(yystack_[5].location.begin.line);
        }
#line 2190 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 33: // record_type_decl: RECORD field_decl_list _END
#line 409 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < recordDecl * > () = yystack_[1].value.as < recordDecl * > ();
        }
#line 2198 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 34: // field_decl_list: field_decl_list field_decl
#line 416 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < recordDecl * > () = yystack_[1].value.as < recordDecl * > ();
            yylhs.value.as < recordDecl * > ()->addRecord(*yystack_[0].value.as < field* > ());
        }
#line 2207 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 35: // field_decl_list: field_decl
#line 421 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < recordDecl * > () = new recordDecl();
            yylhs.value.as < recordDecl * > ()->addRecord(*yystack_[0].value.as < field* > ());
            yylhs.value.as < recordDecl * > ()->setLineno(yylhs.location.begin.line);
        }
#line 2217 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 36: // field_decl: name_list COLON type_decl SEMI
#line 430 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < field* > () = new field(yystack_[3].value.as < std::vector<std::string>* > (), yystack_[1].value.as < abstractTypeDeclNode * > ());
            yylhs.value.as < field* > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2226 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 37: // name_list: name_list COMMA ID
#line 438 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<std::string>* > () = yystack_[2].value.as < std::vector<std::string>* > ();
            yylhs.value.as < std::vector<std::string>* > ()->push_back(yystack_[0].value.as < std::string > ());
        }
#line 2235 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 38: // name_list: ID
#line 443 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<std::string>* > () = new std::vector<std::string>();
            yylhs.value.as < std::vector<std::string>* > ()->push_back(yystack_[0].value.as < std::string > ());
        }
#line 2244 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 39: // var_part: VAR var_decl_list
#line 451 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < varDecl * > () = yystack_[0].value.as < varDecl * > ();
        }
#line 2252 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 40: // var_part: %empty
#line 455 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
        }
#line 2259 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 41: // var_decl_list: var_decl_list var_decl
#line 461 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < varDecl * > () = yystack_[1].value.as < varDecl * > ();
            yylhs.value.as < varDecl * > ()->addDecl(yystack_[0].value.as < varNode * > ());
        }
#line 2268 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 42: // var_decl_list: var_decl
#line 466 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < varDecl * > () = new varDecl();
            yylhs.value.as < varDecl * > ()->setLineno(yystack_[0].location.begin.line);
            yylhs.value.as < varDecl * > ()->addDecl(yystack_[0].value.as < varNode * > ());
        }
#line 2278 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 43: // var_decl: name_list COLON type_decl SEMI
#line 475 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < varNode * > () = new varNode(yystack_[3].value.as < std::vector<std::string>* > (), yystack_[1].value.as < abstractTypeDeclNode * > ());
            yylhs.value.as < varNode * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2287 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 44: // routine_part: routine_part function_decl
#line 483 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<functionNode *> * > () = yystack_[1].value.as < std::vector<functionNode *> * > ();
            yylhs.value.as < std::vector<functionNode *> * > ()->push_back(yystack_[0].value.as < functionNode * > ());
        }
#line 2296 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 45: // routine_part: routine_part procedure_decl
#line 488 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<functionNode *> * > () = yystack_[1].value.as < std::vector<functionNode *> * > ();
            yylhs.value.as < std::vector<functionNode *> * > ()->push_back(yystack_[0].value.as < functionNode * > ());
        }
#line 2305 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 46: // routine_part: function_decl
#line 493 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<functionNode *> * > () = new std::vector<functionNode *>();
            yylhs.value.as < std::vector<functionNode *> * > ()->push_back(yystack_[0].value.as < functionNode * > ());
        }
#line 2314 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 47: // routine_part: procedure_decl
#line 498 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<functionNode *> * > () = new std::vector<functionNode *>();
            yylhs.value.as < std::vector<functionNode *> * > ()->push_back(yystack_[0].value.as < functionNode * > ());
        }
#line 2323 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 48: // routine_part: %empty
#line 503 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {

        }
#line 2331 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 49: // function_decl: function_head SEMI sub_routine SEMI
#line 509 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                                               {
        	yylhs.value.as < functionNode * > () = new functionNode(get<0>(yystack_[3].value.as < std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > ()), get<1>(yystack_[3].value.as < std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > ()), yystack_[1].value.as < rootProgram* > (), get<2>(yystack_[3].value.as < std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > ()));
            yylhs.value.as < functionNode * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2340 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 50: // function_head: FUNCTION ID parameters COLON simple_type_decl
#line 517 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > () = std::make_tuple(yystack_[3].value.as < std::string > (), yystack_[2].value.as < std::vector<parameter *>* > (), yystack_[0].value.as < abstractSimpleDecl * > ());
        }
#line 2348 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 51: // procedure_decl: procedure_head SEMI sub_routine SEMI
#line 524 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < functionNode * > () = new functionNode(get<0>(yystack_[3].value.as < std::tuple<std::string, std::vector<parameter *> *> > ()), get<1>(yystack_[3].value.as < std::tuple<std::string, std::vector<parameter *> *> > ()), yystack_[1].value.as < rootProgram* > ());
            yylhs.value.as < functionNode * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2357 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 52: // procedure_head: PROCEDURE ID parameters
#line 532 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::tuple<std::string, std::vector<parameter *> *> > () = std::make_tuple(yystack_[1].value.as < std::string > (), yystack_[0].value.as < std::vector<parameter *>* > ());
        }
#line 2365 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 53: // parameters: LP para_decl_list RP
#line 539 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<parameter *>* > () = yystack_[1].value.as < std::vector<parameter *>* > ();
        }
#line 2373 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 54: // parameters: %empty
#line 543 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
        }
#line 2380 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 55: // para_decl_list: para_decl_list SEMI para_type_list
#line 549 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<parameter *>* > () = yystack_[2].value.as < std::vector<parameter *>* > ();
            yylhs.value.as < std::vector<parameter *>* > ()->push_back(yystack_[0].value.as < parameter * > ());
        }
#line 2389 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 56: // para_decl_list: para_type_list
#line 554 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<parameter *>* > () = new std::vector<parameter *>();
            yylhs.value.as < std::vector<parameter *>* > ()->push_back(yystack_[0].value.as < parameter * > ());
        }
#line 2398 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 57: // para_type_list: var_para_list COLON simple_type_decl
#line 562 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < parameter * > () = new parameter(TOY_COMPILER::REFER, *(yystack_[2].value.as < std::vector<std::string>* > ()), yystack_[0].value.as < abstractSimpleDecl * > ());
            yylhs.value.as < parameter * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2407 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 58: // para_type_list: val_para_list COLON simple_type_decl
#line 567 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < parameter * > () = new parameter(TOY_COMPILER::VALUE, *(yystack_[2].value.as < std::vector<std::string>* > ()), yystack_[0].value.as < abstractSimpleDecl * > ());
            yylhs.value.as < parameter * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2416 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 59: // var_para_list: VAR name_list
#line 575 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<std::string>* > () = yystack_[0].value.as < std::vector<std::string>* > ();
        }
#line 2424 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 60: // val_para_list: name_list
#line 582 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<std::string>* > () = yystack_[0].value.as < std::vector<std::string>* > ();
        }
#line 2432 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 61: // routine_body: compound_stmt
#line 588 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                      { yylhs.value.as < stmtList * > () = yystack_[0].value.as < stmtList * > (); }
#line 2438 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 62: // compound_stmt: _BEGIN stmt_list _END
#line 592 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                                {yylhs.value.as < stmtList * > () = yystack_[1].value.as < stmtList * > ();}
#line 2444 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 63: // stmt_list: stmt_list stmt SEMI
#line 596 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                              {yystack_[2].value.as < stmtList * > ()->addStmt(yystack_[1].value.as < abstractStmt* > ()); yylhs.value.as < stmtList * > () = yystack_[2].value.as < stmtList * > ();}
#line 2450 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 64: // stmt_list: %empty
#line 598 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < stmtList * > () = new stmtList();
            yylhs.value.as < stmtList * > ()->setLineno(yylhs.location.begin.line);
        }
#line 2459 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 65: // stmt: INTEGER COLON non_label_stmt
#line 605 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < abstractStmt* > ();
            //globalsymtab->Label.insert($1, $3);
        }
#line 2468 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 66: // stmt: non_label_stmt
#line 609 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                          {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < abstractStmt* > ();}
#line 2474 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 67: // non_label_stmt: assign_stmt
#line 613 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                    {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < assignStmt* > ();}
#line 2480 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 68: // non_label_stmt: proc_stmt
#line 614 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                    {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < functionCall * > ();}
#line 2486 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 69: // non_label_stmt: compound_stmt
#line 615 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                        {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < stmtList * > ();}
#line 2492 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 70: // non_label_stmt: if_stmt
#line 616 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                  {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < ifStmt* > ();}
#line 2498 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 71: // non_label_stmt: repeat_stmt
#line 617 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                      {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < repeatStmt* > ();}
#line 2504 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 72: // non_label_stmt: while_stmt
#line 618 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                     {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < whileStmt* > ();}
#line 2510 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 73: // non_label_stmt: for_stmt
#line 619 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                   {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < forStmt* > ();}
#line 2516 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 74: // non_label_stmt: case_stmt
#line 620 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                    {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < caseStmt* > ();}
#line 2522 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 75: // non_label_stmt: goto_stmt
#line 621 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                    {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < gotoStmt* > ();}
#line 2528 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 76: // assign_stmt: ID ASSIGN expression
#line 626 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto l = new variableNode(yystack_[2].value.as < std::string > ());
            l->setLineno(yystack_[2].location.begin.line);
            yylhs.value.as < assignStmt* > () = new assignStmt(l, yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < assignStmt* > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2539 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 77: // assign_stmt: ID LB expression RB ASSIGN expression
#line 633 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto l = new mathExpr(TOY_COMPILER::LBRB, new variableNode(yystack_[5].value.as < std::string > ()), yystack_[3].value.as < abstractExpr * > ());
            l->setLineno(yystack_[5].location.begin.line);
            yylhs.value.as < assignStmt* > () = new assignStmt(l, yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < assignStmt* > ()->setLineno(yystack_[5].location.begin.line);
        }
#line 2550 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 78: // assign_stmt: ID DOT ID ASSIGN expression
#line 640 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto l = new mathExpr(TOY_COMPILER::DOT, new variableNode(yystack_[4].value.as < std::string > ()), new variableNode(yystack_[2].value.as < std::string > ()));
            l->setLineno(yystack_[4].location.begin.line);
            yylhs.value.as < assignStmt* > () = new assignStmt(l, yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < assignStmt* > ()->setLineno(yystack_[4].location.begin.line);
        }
#line 2561 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 79: // proc_stmt: ID LP RP
#line 650 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < functionCall * > () = new functionCall(yystack_[2].value.as < std::string > (), nullptr);
            yylhs.value.as < functionCall * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2570 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 80: // proc_stmt: ID LP args_list RP
#line 655 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < functionCall * > () = new functionCall(yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::vector<abstractExpr *> * > ());
            yylhs.value.as < functionCall * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2579 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 81: // proc_stmt: SYS_PROC LP RP
#line 660 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            if (yystack_[2].value.as < int > () == 8) {
                yylhs.value.as < functionCall * > () = new functionCall("write", nullptr);
            } else if (yystack_[2].value.as < int > () == 9) {
                yylhs.value.as < functionCall * > () = new functionCall("writeln", nullptr);
            }
            yylhs.value.as < functionCall * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2592 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 82: // proc_stmt: SYS_PROC LP args_list RP
#line 669 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            if (yystack_[3].value.as < int > () == 8) {
                yylhs.value.as < functionCall * > () = new functionCall("write", yystack_[1].value.as < std::vector<abstractExpr *> * > ());
            } else if (yystack_[3].value.as < int > () == 9) {
                yylhs.value.as < functionCall * > () = new functionCall("writeln", yystack_[1].value.as < std::vector<abstractExpr *> * > ());
            }
            yylhs.value.as < functionCall * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2605 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 83: // proc_stmt: READ LP factor RP
#line 679 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            auto args = new std::vector<abstractExpr *>();
            args->push_back(yystack_[1].value.as < abstractExpr * > ());
            yylhs.value.as < functionCall * > () = new functionCall("read", args);
            yylhs.value.as < functionCall * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2616 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 84: // if_stmt: IF expression THEN stmt else_clause
#line 689 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < ifStmt* > () = new ifStmt(yystack_[3].value.as < abstractExpr * > (), yystack_[1].value.as < abstractStmt* > (), yystack_[0].value.as < abstractStmt* > ());
            yylhs.value.as < ifStmt* > ()->setLineno(yystack_[4].location.begin.line);
        }
#line 2625 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 85: // else_clause: ELSE stmt
#line 696 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                  {yylhs.value.as < abstractStmt* > () = yystack_[0].value.as < abstractStmt* > ();}
#line 2631 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 86: // else_clause: %empty
#line 697 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
           {yylhs.value.as < abstractStmt* > () = nullptr;}
#line 2637 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 87: // repeat_stmt: REPEAT stmt_list UNTIL expression
#line 702 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < repeatStmt* > () = new repeatStmt(yystack_[0].value.as < abstractExpr * > (), yystack_[2].value.as < stmtList * > ());
            yylhs.value.as < repeatStmt* > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2646 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 88: // while_stmt: WHILE expression DO stmt
#line 710 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < whileStmt* > () = new whileStmt(yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractStmt* > ());
            yylhs.value.as < whileStmt* > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2655 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 89: // for_stmt: FOR ID ASSIGN expression direction expression DO stmt
#line 718 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < forStmt* > () = new forStmt(yystack_[6].value.as < std::string > (), yystack_[4].value.as < abstractExpr * > (), yystack_[2].value.as < abstractExpr * > (), yystack_[3].value.as < bool > (), yystack_[0].value.as < abstractStmt* > ());
            yylhs.value.as < forStmt* > ()->setLineno(yystack_[7].location.begin.line);
        }
#line 2664 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 90: // direction: TO
#line 725 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
           {yylhs.value.as < bool > () = true;}
#line 2670 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 91: // direction: DOWNTO
#line 726 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                 {yylhs.value.as < bool > () = false;}
#line 2676 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 92: // case_stmt: CASE expression OF case_expr_list _END
#line 731 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < caseStmt* > () = yystack_[1].value.as < caseStmt* > ();
            yylhs.value.as < caseStmt* > ()->addCond(yystack_[3].value.as < abstractExpr * > ());
        }
#line 2685 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 93: // case_expr_list: case_expr_list case_expr
#line 739 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < caseStmt* > () = yystack_[1].value.as < caseStmt* > ();
            yylhs.value.as < caseStmt* > ()->addCase(yystack_[0].value.as < caseNode* > ());
        }
#line 2694 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 94: // case_expr_list: case_expr
#line 744 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < caseStmt* > () = new caseStmt();
            yylhs.value.as < caseStmt* > ()->addCase(yystack_[0].value.as < caseNode* > ());
            yylhs.value.as < caseStmt* > ()->setLineno(yystack_[0].location.begin.line);
        }
#line 2704 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 95: // case_expr: const_value COLON stmt SEMI
#line 753 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < caseNode* > () = new caseNode(yystack_[3].value.as < literal* > (), yystack_[1].value.as < abstractStmt* > ());
            yylhs.value.as < caseNode* > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2713 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 96: // case_expr: ID COLON stmt SEMI
#line 758 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < caseNode* > () = new caseNode(new variableNode(yystack_[3].value.as < std::string > ()), yystack_[1].value.as < abstractStmt* > ());
            yylhs.value.as < caseNode* > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2722 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 97: // goto_stmt: GOTO INTEGER
#line 766 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < gotoStmt* > () = new gotoStmt(yystack_[0].value.as < int > ());
            yylhs.value.as < gotoStmt* > ()->setLineno(yystack_[1].location.begin.line);
        }
#line 2731 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 98: // expression: expression GE expr
#line 774 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::GE, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2740 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 99: // expression: expression GT expr
#line 779 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::GT, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2749 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 100: // expression: expression LE expr
#line 784 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::LE, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2758 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 101: // expression: expression LT expr
#line 789 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::LT, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2767 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 102: // expression: expression EQUAL expr
#line 794 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::EQUAL, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2776 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 103: // expression: expression UNEQUAL expr
#line 799 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::UNEQUAL, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2785 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 104: // expression: expr
#line 804 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = yystack_[0].value.as < abstractExpr * > ();
        }
#line 2793 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 105: // expr: expr PLUS term
#line 811 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::PLUS, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2802 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 106: // expr: expr MINUS term
#line 816 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::MINUS, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2811 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 107: // expr: expr OR term
#line 821 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::OR, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2820 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 108: // expr: term
#line 825 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
                {yylhs.value.as < abstractExpr * > () = yystack_[0].value.as < abstractExpr * > ();}
#line 2826 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 109: // term: term MUL factor
#line 830 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::MUL, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2835 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 110: // term: term DIV factor
#line 835 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::DIV, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
	    }
#line 2844 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 111: // term: term MOD factor
#line 840 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::MOD, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2853 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 112: // term: term AND factor
#line 845 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::AND, yystack_[2].value.as < abstractExpr * > (), yystack_[0].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2862 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 113: // term: factor
#line 850 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = yystack_[0].value.as < abstractExpr * > ();
        }
#line 2870 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 114: // factor: ID
#line 857 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new variableNode(yystack_[0].value.as < std::string > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[0].location.begin.line);
        }
#line 2879 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 115: // factor: ID LP RP
#line 862 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new functionCall(yystack_[2].value.as < std::string > (), nullptr);
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2888 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 116: // factor: ID LP args_list RP
#line 867 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new functionCall(yystack_[3].value.as < std::string > (), yystack_[1].value.as < std::vector<abstractExpr *> * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2897 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 117: // factor: SYS_FUNCT LP RP
#line 872 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            std::string func_name;
            switch(yystack_[2].value.as < int > ()) {
                case 0:
                    func_name = "abs";
                    break;
                case 1:
                    func_name = "chr";
                    break;
                case 2:
                    func_name = "odd";
                    break;
                case 3:
                    func_name = "ord";
                    break;
                case 4:
                    func_name = "pred";
                    break;
                case 5:
                    func_name = "sqr";
                    break;
                case 6:
                    func_name = "sqrt";
                    break;
                case 7:
                    func_name = "succ";
                    break;
            }

            yylhs.value.as < abstractExpr * > () = new functionCall(func_name, nullptr);
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
        }
#line 2934 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 118: // factor: SYS_FUNCT LP args_list RP
#line 905 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
        	std::string func_name;
            switch(yystack_[3].value.as < int > ()) {
                case 0:
                    func_name = "abs";
                    break;
                case 1:
                    func_name = "chr";
                    break;
                case 2:
                    func_name = "odd";
                    break;
                case 3:
                    func_name = "ord";
                    break;
                case 4:
                    func_name = "pred";
                    break;
                case 5:
                    func_name = "sqr";
                    break;
                case 6:
                    func_name = "sqrt";
                    break;
                case 7:
                    func_name = "succ";
                    break;
            }

            yylhs.value.as < abstractExpr * > () = new functionCall(func_name, yystack_[1].value.as < std::vector<abstractExpr *> * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 2971 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 119: // factor: const_value
#line 938 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = yystack_[0].value.as < literal* > ();
        }
#line 2979 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 120: // factor: LP expression RP
#line 942 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = yystack_[1].value.as < abstractExpr * > ();
        }
#line 2987 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 121: // factor: NOT factor
#line 946 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::NOT, yystack_[0].value.as < abstractExpr * > (), nullptr);
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[1].location.begin.line);
        }
#line 2996 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 122: // factor: MINUS factor
#line 951 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::NOT, yystack_[0].value.as < abstractExpr * > (), nullptr);
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[1].location.begin.line);
        }
#line 3005 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 123: // factor: ID LB expression RB
#line 956 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::LBRB, new variableNode(yystack_[3].value.as < std::string > ()), yystack_[1].value.as < abstractExpr * > ());
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[3].location.begin.line);
        }
#line 3014 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 124: // factor: ID DOT ID
#line 961 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < abstractExpr * > () = new mathExpr(TOY_COMPILER::DOT, new variableNode(yystack_[2].value.as < std::string > ()), new variableNode(yystack_[0].value.as < std::string > ()));
            yylhs.value.as < abstractExpr * > ()->setLineno(yystack_[2].location.begin.line);
	    }
#line 3023 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 125: // args_list: args_list COMMA expression
#line 969 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<abstractExpr *> * > () = yystack_[2].value.as < std::vector<abstractExpr *> * > ();
            yylhs.value.as < std::vector<abstractExpr *> * > ()->push_back(yystack_[0].value.as < abstractExpr * > ());
        }
#line 3032 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;

  case 126: // args_list: expression
#line 974 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
        {
            yylhs.value.as < std::vector<abstractExpr *> * > () = new std::vector<abstractExpr *>();
            yylhs.value.as < std::vector<abstractExpr *> * > ()->push_back(yystack_[0].value.as < abstractExpr * > ());
        }
#line 3041 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"
    break;


#line 3045 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"

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

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
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


  const short Parser::yypact_ninf_ = -182;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
      -7,    16,    56,  -182,     3,  -182,    18,    69,    71,  -182,
    -182,  -182,  -182,  -182,    51,    93,   119,    45,    55,    88,
     111,   272,  -182,   102,   131,   272,  -182,   272,   115,   116,
     121,    80,  -182,   125,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,   331,   141,   143,    88,  -182,   140,    21,
    -182,   150,  -182,  -182,  -182,  -182,    34,   272,   272,   272,
    -182,    61,   158,   221,  -182,   139,  -182,   134,   133,    11,
     272,   202,   203,   272,   215,   272,   172,  -182,   160,   331,
      12,  -182,  -182,   -38,   140,  -182,   174,   187,    21,  -182,
     164,  -182,   167,   237,   250,   272,   192,  -182,  -182,   307,
     315,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   189,   272,   189,   178,  -182,
     322,   -15,  -182,   322,  -182,    23,   280,   190,  -182,   184,
     191,   140,  -182,   194,   331,   140,   198,   197,  -182,  -182,
    -182,   222,    12,  -182,   214,   214,  -182,  -182,  -182,  -182,
    -182,    47,  -182,    48,   291,  -182,  -182,   217,   219,   138,
    -182,   158,   158,   158,   158,   158,   158,   221,   221,   221,
    -182,  -182,  -182,  -182,    70,   273,   322,  -182,  -182,  -182,
     272,  -182,   229,   272,  -182,   -10,    -3,  -182,   103,   251,
     233,    72,   331,  -182,  -182,   232,   -16,   236,  -182,   235,
      69,   238,  -182,  -182,  -182,   189,   189,  -182,  -182,  -182,
    -182,   272,   189,  -182,   322,   272,   322,   241,  -182,  -182,
      12,  -182,   285,  -182,  -182,  -182,   140,   245,    97,  -182,
     240,   252,   -10,  -182,  -182,  -182,   253,   254,    35,  -182,
     322,   298,   255,   331,  -182,   245,  -182,   -16,   -10,   -10,
    -182,  -182,  -182,   189,    12,  -182,  -182,  -182,  -182,  -182,
    -182,  -182
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     7,     0,     1,     0,     0,     9,     3,
       2,    64,     4,    61,     0,    18,     0,     0,     8,     0,
      40,     0,    62,     0,     0,     0,    64,     0,     0,     0,
       0,     0,    69,     0,    66,    67,    68,    70,    71,    72,
      73,    74,    75,     0,     0,     0,    17,    20,     0,    48,
      16,     0,    15,    12,    13,    14,   114,     0,     0,     0,
     119,     0,   104,   108,   113,     0,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    63,     0,     0,
       0,    19,    38,     0,    39,    42,     0,     0,     6,    46,
       0,    47,     0,     0,     0,     0,     0,   122,   121,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
     126,     0,    65,    76,    79,     0,     0,     0,    11,     0,
       0,     0,    25,    26,     0,     0,     0,     0,    22,    23,
      24,     0,     0,    41,    54,    54,    44,    45,     7,     7,
     117,     0,   115,     0,     0,   124,   120,     0,     0,     0,
      94,   102,   103,    98,    99,   100,   101,   105,   106,   107,
     109,   110,   111,   112,     0,    86,    87,    88,    83,    82,
       0,    80,     0,     0,    10,     0,     0,    35,     0,     0,
       0,     0,     0,    21,    37,     0,     0,     0,    52,     0,
       0,     0,   118,   116,   123,     0,     0,    92,    93,    90,
      91,     0,     0,    84,   125,     0,    78,     0,    33,    34,
       0,    31,     0,    27,    28,    43,     0,    60,     0,    56,
       0,     0,     0,    49,     5,    51,     0,     0,     0,    85,
      77,     0,     0,     0,    29,    59,    53,     0,     0,     0,
      50,    96,    95,     0,     0,    36,    30,    55,    57,    58,
      89,    32
  };

  const short
  Parser::yypgoto_[] =
  {
    -182,  -182,  -182,  -182,   175,   320,  -182,  -182,  -182,   -43,
    -182,  -182,   287,  -140,  -181,  -182,  -182,  -182,   148,  -122,
    -182,  -182,   261,  -182,   247,  -182,   248,  -182,   201,  -182,
     100,  -182,  -182,   161,    -4,   337,  -105,   292,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,   223,  -182,
     -20,   274,   110,   -41,   -60
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,     6,   199,   200,     8,    15,    18,    60,
      20,    46,    47,   137,   138,   139,   140,   186,   187,    83,
      49,    84,    85,    88,    89,    90,    91,    92,   197,   228,
     229,   230,   231,    12,    32,    16,    33,    34,    35,    36,
      37,   213,    38,    39,    40,   211,    41,   159,   160,    42,
     120,    62,    63,    64,   121
  };

  const short
  Parser::yytable_[] =
  {
      78,    61,   195,    13,   217,    67,   218,    69,   226,   188,
     175,     1,   177,   191,   125,   130,    97,    98,   117,    50,
     141,   142,    82,   132,    52,    53,    54,    55,   133,   118,
     134,   131,    86,   151,   153,    82,   129,   136,    87,    99,
     179,    50,   253,   180,   135,   132,    52,    53,    54,    55,
     133,   250,   134,   123,     4,   126,     5,   158,   101,   102,
     103,   104,   105,   106,   188,     9,   135,   258,   259,   170,
     171,   172,   173,    11,   227,   154,   100,    14,   181,    10,
     242,   180,   101,   102,   103,   104,   105,   106,    94,    17,
      95,   190,    43,    44,   174,    96,   176,   209,   210,   136,
     236,   237,   202,   203,   245,   180,   180,   239,   101,   102,
     103,   104,   105,   106,   261,    19,   158,   101,   102,   103,
     104,   105,   106,    11,    21,   227,    45,   223,    22,    23,
     141,    24,    25,    73,    74,    48,    75,    11,    21,    26,
      65,    76,   136,    23,    27,    24,    25,   207,   260,   224,
      28,    29,   246,    26,    30,   115,   116,    31,    27,   247,
     214,   141,   220,   216,    28,    29,    66,    50,    30,    70,
      71,    31,    52,    53,    54,    55,   157,   136,    82,   244,
      72,   101,   102,   103,   104,   105,   106,    77,    79,   136,
      80,   238,   114,    11,    21,   240,    13,   107,   108,    23,
     256,    24,    25,   109,    93,   136,   136,    11,    21,    26,
     127,   136,   144,    23,    27,    24,    25,   167,   168,   169,
      28,    29,   128,    26,    30,   145,   148,    31,    27,   149,
     155,    50,    51,   178,    28,    29,    52,    53,    54,    55,
      56,    31,    57,   183,    50,    51,   184,   185,    58,    52,
      53,    54,    55,    56,   189,    57,    59,   119,   192,   193,
     194,    58,   110,   111,   112,   113,    50,    51,   196,    59,
     124,    52,    53,    54,    55,    56,   205,    57,   206,    50,
      51,   212,   215,    58,    52,    53,    54,    55,    56,   221,
      57,    59,   150,   222,   225,   232,    58,   233,   241,   248,
     235,    50,    51,   141,    59,   152,    52,    53,    54,    55,
      56,   249,    57,   254,    50,   251,   252,   255,    58,    52,
      53,    54,    55,     7,   201,   243,    59,   101,   102,   103,
     104,   105,   106,    81,   219,   146,   147,   182,   101,   102,
     103,   104,   105,   106,    50,   143,   198,   257,   204,    52,
      53,    54,    55,   157,   101,   102,   103,   104,   105,   106,
      50,   234,   156,    68,   122,    52,    53,    54,    55,   101,
     102,   103,   104,   105,   106,   161,   162,   163,   164,   165,
     166,     0,   208
  };

  const short
  Parser::yycheck_[] =
  {
      43,    21,   142,     7,   185,    25,     9,    27,    24,   131,
     115,    18,   117,   135,    74,     3,    57,    58,     7,    29,
      58,    59,    38,    33,    34,    35,    36,    37,    38,    70,
      40,    19,    11,    93,    94,    38,    79,    80,    17,    59,
      55,    29,     7,    58,    54,    33,    34,    35,    36,    37,
      38,   232,    40,    73,    38,    75,     0,   100,    47,    48,
      49,    50,    51,    52,   186,    62,    54,   248,   249,   110,
     111,   112,   113,     4,   196,    95,    15,     6,    55,    61,
     220,    58,    47,    48,    49,    50,    51,    52,    54,    38,
      56,   134,    47,    38,   114,    61,   116,    27,    28,   142,
     205,   206,    55,    55,   226,    58,    58,   212,    47,    48,
      49,    50,    51,    52,   254,    22,   159,    47,    48,    49,
      50,    51,    52,     4,     5,   247,    38,    55,     9,    10,
      58,    12,    13,    53,    54,    24,    56,     4,     5,    20,
      38,    61,   185,    10,    25,    12,    13,     9,   253,   192,
      31,    32,    55,    20,    35,    21,    23,    38,    25,    62,
     180,    58,    59,   183,    31,    32,    35,    29,    35,    54,
      54,    38,    34,    35,    36,    37,    38,   220,    38,   222,
      59,    47,    48,    49,    50,    51,    52,    62,    47,   232,
      47,   211,    53,     4,     5,   215,   200,    39,    40,    10,
     243,    12,    13,    45,    54,   248,   249,     4,     5,    20,
      38,   254,    38,    10,    25,    12,    13,   107,   108,   109,
      31,    32,    62,    20,    35,    38,    62,    38,    25,    62,
      38,    29,    30,    55,    31,    32,    34,    35,    36,    37,
      38,    38,    40,    53,    29,    30,    62,    56,    46,    34,
      35,    36,    37,    38,    60,    40,    54,    55,    60,    62,
      38,    46,    41,    42,    43,    44,    29,    30,    54,    54,
      55,    34,    35,    36,    37,    38,    59,    40,    59,    29,
      30,     8,    53,    46,    34,    35,    36,    37,    38,    38,
      40,    54,    55,    60,    62,    59,    46,    62,    57,    59,
      62,    29,    30,    58,    54,    55,    34,    35,    36,    37,
      38,    59,    40,    15,    29,    62,    62,    62,    46,    34,
      35,    36,    37,     3,   149,    40,    54,    47,    48,    49,
      50,    51,    52,    46,   186,    88,    88,    57,    47,    48,
      49,    50,    51,    52,    29,    84,   145,   247,    57,    34,
      35,    36,    37,    38,    47,    48,    49,    50,    51,    52,
      29,   200,    55,    26,    72,    34,    35,    36,    37,    47,
      48,    49,    50,    51,    52,   101,   102,   103,   104,   105,
     106,    -1,   159
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    18,    64,    65,    38,     0,    66,    68,    69,    62,
      61,     4,    96,    97,     6,    70,    98,    38,    71,    22,
      73,     5,     9,    10,    12,    13,    20,    25,    31,    32,
      35,    38,    97,    99,   100,   101,   102,   103,   105,   106,
     107,   109,   112,    47,    38,    38,    74,    75,    24,    83,
      29,    30,    34,    35,    36,    37,    38,    40,    46,    54,
      72,   113,   114,   115,   116,    38,    35,   113,    98,   113,
      54,    54,    59,    53,    54,    56,    61,    62,    72,    47,
      47,    75,    38,    82,    84,    85,    11,    17,    86,    87,
      88,    89,    90,    54,    54,    56,    61,   116,   116,   113,
      15,    47,    48,    49,    50,    51,    52,    39,    40,    45,
      41,    42,    43,    44,    53,    21,    23,     7,   116,    55,
     113,   117,   100,   113,    55,   117,   113,    38,    62,    72,
       3,    19,    33,    38,    40,    54,    72,    76,    77,    78,
      79,    58,    59,    85,    38,    38,    87,    89,    62,    62,
      55,   117,    55,   117,   113,    38,    55,    38,    72,   110,
     111,   114,   114,   114,   114,   114,   114,   115,   115,   115,
     116,   116,   116,   116,   113,    99,   113,    99,    55,    55,
      58,    55,    57,    53,    62,    56,    80,    81,    82,    60,
      72,    82,    60,    62,    38,    76,    54,    91,    91,    67,
      68,    67,    55,    55,    57,    59,    59,     9,   111,    27,
      28,   108,     8,   104,   113,    53,   113,    77,     9,    81,
      59,    38,    60,    55,    72,    62,    24,    82,    92,    93,
      94,    95,    59,    62,    96,    62,    99,    99,   113,    99,
     113,    57,    76,    40,    72,    82,    55,    62,    59,    59,
      77,    62,    62,     7,    15,    62,    72,    93,    77,    77,
      99,    76
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    63,    64,    65,    66,    67,    68,    69,    70,    70,
      71,    71,    72,    72,    72,    72,    72,    73,    73,    74,
      74,    75,    76,    76,    76,    77,    77,    77,    77,    77,
      77,    77,    78,    79,    80,    80,    81,    82,    82,    83,
      83,    84,    84,    85,    86,    86,    86,    86,    86,    87,
      88,    89,    90,    91,    91,    92,    92,    93,    93,    94,
      95,    96,    97,    98,    98,    99,    99,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   101,   101,   101,   102,
     102,   102,   102,   102,   103,   104,   104,   105,   106,   107,
     108,   108,   109,   110,   110,   111,   111,   112,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   114,   114,   115,
     115,   115,   115,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   117,   117
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     3,     3,     2,     2,     5,     0,     2,     0,
       5,     4,     1,     1,     1,     1,     1,     2,     0,     2,
       1,     4,     1,     1,     1,     1,     1,     3,     3,     4,
       5,     3,     6,     3,     2,     1,     4,     3,     1,     2,
       0,     2,     1,     4,     2,     2,     1,     1,     0,     4,
       5,     4,     3,     3,     0,     3,     1,     3,     3,     2,
       1,     1,     3,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     6,     5,     3,
       4,     3,     4,     4,     5,     2,     0,     4,     4,     8,
       1,     1,     5,     2,     1,     4,     4,     2,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     1,     3,
       3,     3,     3,     1,     1,     3,     4,     3,     4,     1,
       3,     2,     2,     4,     3,     3,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "ARRAY", "_BEGIN",
  "CASE", "CONST", "DO", "ELSE", "_END", "FOR", "FUNCTION", "GOTO", "IF",
  "IN", "OF", "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "THEN",
  "TYPE", "UNTIL", "VAR", "WHILE", "WITH", "TO", "DOWNTO", "SYS_CON",
  "SYS_FUNCT", "READ", "SYS_PROC", "SYS_TYPE", "BOOL", "INTEGER", "REAL",
  "CHAR", "ID", "PLUS", "MINUS", "MUL", "DIV", "MOD", "AND", "OR", "NOT",
  "EQUAL", "UNEQUAL", "GE", "GT", "LE", "LT", "ASSIGN", "LP", "RP", "LB",
  "RB", "COMMA", "COLON", "DOTDOT", "DOT", "SEMI", "$accept", "program",
  "program_head", "routine", "sub_routine", "routine_head", "label_part",
  "const_part", "const_expr_list", "const_value", "type_part",
  "type_decl_list", "type_definition", "type_decl", "simple_type_decl",
  "array_type_decl", "record_type_decl", "field_decl_list", "field_decl",
  "name_list", "var_part", "var_decl_list", "var_decl", "routine_part",
  "function_decl", "function_head", "procedure_decl", "procedure_head",
  "parameters", "para_decl_list", "para_type_list", "var_para_list",
  "val_para_list", "routine_body", "compound_stmt", "stmt_list", "stmt",
  "non_label_stmt", "assign_stmt", "proc_stmt", "if_stmt", "else_clause",
  "repeat_stmt", "while_stmt", "for_stmt", "direction", "case_stmt",
  "case_expr_list", "case_expr", "goto_stmt", "expression", "expr", "term",
  "factor", "args_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   166,   166,   175,   181,   192,   199,   213,   218,   223,
     228,   232,   241,   250,   259,   268,   277,   295,   300,   306,
     310,   319,   329,   333,   337,   344,   359,   367,   377,   382,
     387,   392,   400,   408,   415,   420,   429,   437,   442,   450,
     455,   460,   465,   474,   482,   487,   492,   497,   503,   509,
     516,   523,   531,   538,   543,   548,   553,   561,   566,   574,
     581,   588,   592,   596,   598,   604,   609,   613,   614,   615,
     616,   617,   618,   619,   620,   621,   625,   632,   639,   649,
     654,   659,   668,   678,   688,   696,   697,   701,   709,   717,
     725,   726,   730,   738,   743,   752,   757,   765,   773,   778,
     783,   788,   793,   798,   803,   810,   815,   820,   825,   829,
     834,   839,   844,   849,   856,   861,   866,   871,   904,   937,
     941,   945,   950,   955,   960,   968,   973
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
  Parser::yytranslate_ (int t)
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
    };
    // Last valid token kind.
    const int code_max = 317;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 20 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
} // TOY_COMPILER
#line 3772 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.cc"

#line 980 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"


void TOY_COMPILER::Parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

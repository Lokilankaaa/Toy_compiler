// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file /Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.hh
 ** Define the TOY_COMPILER::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_USERS_XUEWEI_ONEDRIVE_ZJU_EDU_CN_CODE_CPP_TOY_COMPILER_SRC_PARSER_TAB_HH_INCLUDED
# define YY_YY_USERS_XUEWEI_ONEDRIVE_ZJU_EDU_CN_CODE_CPP_TOY_COMPILER_SRC_PARSER_TAB_HH_INCLUDED
// "%code requires" blocks.
#line 23 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"

    namespace TOY_COMPILER  {
        class Scanner;
    }
    #include "ast.h"
    #include "symtab.h"

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#line 66 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.hh"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 20 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
namespace TOY_COMPILER {
#line 201 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.hh"




  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // expression
      // expr
      // term
      // factor
      char dummy1[sizeof (abstractExpr *)];

      // simple_type_decl
      char dummy2[sizeof (abstractSimpleDecl *)];

      // stmt
      // non_label_stmt
      // else_clause
      char dummy3[sizeof (abstractStmt*)];

      // type_decl
      char dummy4[sizeof (abstractTypeDeclNode *)];

      // array_type_decl
      char dummy5[sizeof (arrayDecl*)];

      // assign_stmt
      char dummy6[sizeof (assignStmt*)];

      // BOOL
      // direction
      char dummy7[sizeof (bool)];

      // case_expr
      char dummy8[sizeof (caseNode*)];

      // case_stmt
      // case_expr_list
      char dummy9[sizeof (caseStmt*)];

      // CHAR
      char dummy10[sizeof (char)];

      // const_part
      // const_expr_list
      char dummy11[sizeof (constDecl *)];

      // REAL
      char dummy12[sizeof (double)];

      // field_decl
      char dummy13[sizeof (field*)];

      // for_stmt
      char dummy14[sizeof (forStmt*)];

      // proc_stmt
      char dummy15[sizeof (functionCall *)];

      // function_decl
      // procedure_decl
      char dummy16[sizeof (functionNode *)];

      // goto_stmt
      char dummy17[sizeof (gotoStmt*)];

      // if_stmt
      char dummy18[sizeof (ifStmt*)];

      // SYS_CON
      // SYS_FUNCT
      // READ
      // SYS_PROC
      // SYS_TYPE
      // INTEGER
      char dummy19[sizeof (int)];

      // const_value
      char dummy20[sizeof (literal*)];

      // para_type_list
      char dummy21[sizeof (parameter *)];

      // record_type_decl
      // field_decl_list
      char dummy22[sizeof (recordDecl *)];

      // repeat_stmt
      char dummy23[sizeof (repeatStmt*)];

      // routine
      // sub_routine
      char dummy24[sizeof (rootProgram*)];

      // routine_head
      char dummy25[sizeof (std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *> )];

      // ID
      char dummy26[sizeof (std::string)];

      // program_head
      char dummy27[sizeof (std::string*)];

      // function_head
      char dummy28[sizeof (std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *>)];

      // procedure_head
      char dummy29[sizeof (std::tuple<std::string, std::vector<parameter *> *>)];

      // args_list
      char dummy30[sizeof (std::vector<abstractExpr *> *)];

      // routine_part
      char dummy31[sizeof (std::vector<functionNode *> *)];

      // parameters
      // para_decl_list
      char dummy32[sizeof (std::vector<parameter *>*)];

      // name_list
      // var_para_list
      // val_para_list
      char dummy33[sizeof (std::vector<std::string>*)];

      // routine_body
      // compound_stmt
      // stmt_list
      char dummy34[sizeof (stmtList *)];

      // type_part
      // type_decl_list
      char dummy35[sizeof (typeDefDecl *)];

      // var_part
      // var_decl_list
      char dummy36[sizeof (varDecl *)];

      // type_definition
      // var_decl
      char dummy37[sizeof (varNode *)];

      // while_stmt
      char dummy38[sizeof (whileStmt*)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    END = 0,                       // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    ARRAY = 258,                   // ARRAY
    _BEGIN = 259,                  // _BEGIN
    CASE = 260,                    // CASE
    CONST = 261,                   // CONST
    DO = 262,                      // DO
    ELSE = 263,                    // ELSE
    _END = 264,                    // _END
    FOR = 265,                     // FOR
    FUNCTION = 266,                // FUNCTION
    GOTO = 267,                    // GOTO
    IF = 268,                      // IF
    IN = 269,                      // IN
    OF = 270,                      // OF
    PACKED = 271,                  // PACKED
    PROCEDURE = 272,               // PROCEDURE
    PROGRAM = 273,                 // PROGRAM
    RECORD = 274,                  // RECORD
    REPEAT = 275,                  // REPEAT
    THEN = 276,                    // THEN
    TYPE = 277,                    // TYPE
    UNTIL = 278,                   // UNTIL
    VAR = 279,                     // VAR
    WHILE = 280,                   // WHILE
    WITH = 281,                    // WITH
    TO = 282,                      // TO
    DOWNTO = 283,                  // DOWNTO
    SYS_CON = 284,                 // SYS_CON
    SYS_FUNCT = 285,               // SYS_FUNCT
    READ = 286,                    // READ
    SYS_PROC = 287,                // SYS_PROC
    SYS_TYPE = 288,                // SYS_TYPE
    BOOL = 289,                    // BOOL
    INTEGER = 290,                 // INTEGER
    REAL = 291,                    // REAL
    CHAR = 292,                    // CHAR
    ID = 293,                      // ID
    PLUS = 294,                    // PLUS
    MINUS = 295,                   // MINUS
    MUL = 296,                     // MUL
    DIV = 297,                     // DIV
    MOD = 298,                     // MOD
    AND = 299,                     // AND
    OR = 300,                      // OR
    NOT = 301,                     // NOT
    EQUAL = 302,                   // EQUAL
    UNEQUAL = 303,                 // UNEQUAL
    GE = 304,                      // GE
    GT = 305,                      // GT
    LE = 306,                      // LE
    LT = 307,                      // LT
    ASSIGN = 308,                  // ASSIGN
    LP = 309,                      // LP
    RP = 310,                      // RP
    LB = 311,                      // LB
    RB = 312,                      // RB
    COMMA = 313,                   // COMMA
    COLON = 314,                   // COLON
    DOTDOT = 315,                  // DOTDOT
    DOT = 316,                     // DOT
    SEMI = 317                     // SEMI
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 63, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_ARRAY = 3,                             // ARRAY
        S__BEGIN = 4,                            // _BEGIN
        S_CASE = 5,                              // CASE
        S_CONST = 6,                             // CONST
        S_DO = 7,                                // DO
        S_ELSE = 8,                              // ELSE
        S__END = 9,                              // _END
        S_FOR = 10,                              // FOR
        S_FUNCTION = 11,                         // FUNCTION
        S_GOTO = 12,                             // GOTO
        S_IF = 13,                               // IF
        S_IN = 14,                               // IN
        S_OF = 15,                               // OF
        S_PACKED = 16,                           // PACKED
        S_PROCEDURE = 17,                        // PROCEDURE
        S_PROGRAM = 18,                          // PROGRAM
        S_RECORD = 19,                           // RECORD
        S_REPEAT = 20,                           // REPEAT
        S_THEN = 21,                             // THEN
        S_TYPE = 22,                             // TYPE
        S_UNTIL = 23,                            // UNTIL
        S_VAR = 24,                              // VAR
        S_WHILE = 25,                            // WHILE
        S_WITH = 26,                             // WITH
        S_TO = 27,                               // TO
        S_DOWNTO = 28,                           // DOWNTO
        S_SYS_CON = 29,                          // SYS_CON
        S_SYS_FUNCT = 30,                        // SYS_FUNCT
        S_READ = 31,                             // READ
        S_SYS_PROC = 32,                         // SYS_PROC
        S_SYS_TYPE = 33,                         // SYS_TYPE
        S_BOOL = 34,                             // BOOL
        S_INTEGER = 35,                          // INTEGER
        S_REAL = 36,                             // REAL
        S_CHAR = 37,                             // CHAR
        S_ID = 38,                               // ID
        S_PLUS = 39,                             // PLUS
        S_MINUS = 40,                            // MINUS
        S_MUL = 41,                              // MUL
        S_DIV = 42,                              // DIV
        S_MOD = 43,                              // MOD
        S_AND = 44,                              // AND
        S_OR = 45,                               // OR
        S_NOT = 46,                              // NOT
        S_EQUAL = 47,                            // EQUAL
        S_UNEQUAL = 48,                          // UNEQUAL
        S_GE = 49,                               // GE
        S_GT = 50,                               // GT
        S_LE = 51,                               // LE
        S_LT = 52,                               // LT
        S_ASSIGN = 53,                           // ASSIGN
        S_LP = 54,                               // LP
        S_RP = 55,                               // RP
        S_LB = 56,                               // LB
        S_RB = 57,                               // RB
        S_COMMA = 58,                            // COMMA
        S_COLON = 59,                            // COLON
        S_DOTDOT = 60,                           // DOTDOT
        S_DOT = 61,                              // DOT
        S_SEMI = 62,                             // SEMI
        S_YYACCEPT = 63,                         // $accept
        S_program = 64,                          // program
        S_program_head = 65,                     // program_head
        S_routine = 66,                          // routine
        S_sub_routine = 67,                      // sub_routine
        S_routine_head = 68,                     // routine_head
        S_label_part = 69,                       // label_part
        S_const_part = 70,                       // const_part
        S_const_expr_list = 71,                  // const_expr_list
        S_const_value = 72,                      // const_value
        S_type_part = 73,                        // type_part
        S_type_decl_list = 74,                   // type_decl_list
        S_type_definition = 75,                  // type_definition
        S_type_decl = 76,                        // type_decl
        S_simple_type_decl = 77,                 // simple_type_decl
        S_array_type_decl = 78,                  // array_type_decl
        S_record_type_decl = 79,                 // record_type_decl
        S_field_decl_list = 80,                  // field_decl_list
        S_field_decl = 81,                       // field_decl
        S_name_list = 82,                        // name_list
        S_var_part = 83,                         // var_part
        S_var_decl_list = 84,                    // var_decl_list
        S_var_decl = 85,                         // var_decl
        S_routine_part = 86,                     // routine_part
        S_function_decl = 87,                    // function_decl
        S_function_head = 88,                    // function_head
        S_procedure_decl = 89,                   // procedure_decl
        S_procedure_head = 90,                   // procedure_head
        S_parameters = 91,                       // parameters
        S_para_decl_list = 92,                   // para_decl_list
        S_para_type_list = 93,                   // para_type_list
        S_var_para_list = 94,                    // var_para_list
        S_val_para_list = 95,                    // val_para_list
        S_routine_body = 96,                     // routine_body
        S_compound_stmt = 97,                    // compound_stmt
        S_stmt_list = 98,                        // stmt_list
        S_stmt = 99,                             // stmt
        S_non_label_stmt = 100,                  // non_label_stmt
        S_assign_stmt = 101,                     // assign_stmt
        S_proc_stmt = 102,                       // proc_stmt
        S_if_stmt = 103,                         // if_stmt
        S_else_clause = 104,                     // else_clause
        S_repeat_stmt = 105,                     // repeat_stmt
        S_while_stmt = 106,                      // while_stmt
        S_for_stmt = 107,                        // for_stmt
        S_direction = 108,                       // direction
        S_case_stmt = 109,                       // case_stmt
        S_case_expr_list = 110,                  // case_expr_list
        S_case_expr = 111,                       // case_expr
        S_goto_stmt = 112,                       // goto_stmt
        S_expression = 113,                      // expression
        S_expr = 114,                            // expr
        S_term = 115,                            // term
        S_factor = 116,                          // factor
        S_args_list = 117                        // args_list
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< abstractExpr * > (std::move (that.value));
        break;

      case symbol_kind::S_simple_type_decl: // simple_type_decl
        value.move< abstractSimpleDecl * > (std::move (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_non_label_stmt: // non_label_stmt
      case symbol_kind::S_else_clause: // else_clause
        value.move< abstractStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< abstractTypeDeclNode * > (std::move (that.value));
        break;

      case symbol_kind::S_array_type_decl: // array_type_decl
        value.move< arrayDecl* > (std::move (that.value));
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.move< assignStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_direction: // direction
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.move< caseNode* > (std::move (that.value));
        break;

      case symbol_kind::S_case_stmt: // case_stmt
      case symbol_kind::S_case_expr_list: // case_expr_list
        value.move< caseStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.move< char > (std::move (that.value));
        break;

      case symbol_kind::S_const_part: // const_part
      case symbol_kind::S_const_expr_list: // const_expr_list
        value.move< constDecl * > (std::move (that.value));
        break;

      case symbol_kind::S_REAL: // REAL
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.move< field* > (std::move (that.value));
        break;

      case symbol_kind::S_for_stmt: // for_stmt
        value.move< forStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_proc_stmt: // proc_stmt
        value.move< functionCall * > (std::move (that.value));
        break;

      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_procedure_decl: // procedure_decl
        value.move< functionNode * > (std::move (that.value));
        break;

      case symbol_kind::S_goto_stmt: // goto_stmt
        value.move< gotoStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.move< ifStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_SYS_CON: // SYS_CON
      case symbol_kind::S_SYS_FUNCT: // SYS_FUNCT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_SYS_PROC: // SYS_PROC
      case symbol_kind::S_SYS_TYPE: // SYS_TYPE
      case symbol_kind::S_INTEGER: // INTEGER
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_const_value: // const_value
        value.move< literal* > (std::move (that.value));
        break;

      case symbol_kind::S_para_type_list: // para_type_list
        value.move< parameter * > (std::move (that.value));
        break;

      case symbol_kind::S_record_type_decl: // record_type_decl
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.move< recordDecl * > (std::move (that.value));
        break;

      case symbol_kind::S_repeat_stmt: // repeat_stmt
        value.move< repeatStmt* > (std::move (that.value));
        break;

      case symbol_kind::S_routine: // routine
      case symbol_kind::S_sub_routine: // sub_routine
        value.move< rootProgram* > (std::move (that.value));
        break;

      case symbol_kind::S_routine_head: // routine_head
        value.move< std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > (std::move (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_program_head: // program_head
        value.move< std::string* > (std::move (that.value));
        break;

      case symbol_kind::S_function_head: // function_head
        value.move< std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > (std::move (that.value));
        break;

      case symbol_kind::S_procedure_head: // procedure_head
        value.move< std::tuple<std::string, std::vector<parameter *> *> > (std::move (that.value));
        break;

      case symbol_kind::S_args_list: // args_list
        value.move< std::vector<abstractExpr *> * > (std::move (that.value));
        break;

      case symbol_kind::S_routine_part: // routine_part
        value.move< std::vector<functionNode *> * > (std::move (that.value));
        break;

      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_para_decl_list: // para_decl_list
        value.move< std::vector<parameter *>* > (std::move (that.value));
        break;

      case symbol_kind::S_name_list: // name_list
      case symbol_kind::S_var_para_list: // var_para_list
      case symbol_kind::S_val_para_list: // val_para_list
        value.move< std::vector<std::string>* > (std::move (that.value));
        break;

      case symbol_kind::S_routine_body: // routine_body
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_stmt_list: // stmt_list
        value.move< stmtList * > (std::move (that.value));
        break;

      case symbol_kind::S_type_part: // type_part
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.move< typeDefDecl * > (std::move (that.value));
        break;

      case symbol_kind::S_var_part: // var_part
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.move< varDecl * > (std::move (that.value));
        break;

      case symbol_kind::S_type_definition: // type_definition
      case symbol_kind::S_var_decl: // var_decl
        value.move< varNode * > (std::move (that.value));
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.move< whileStmt* > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, abstractExpr *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const abstractExpr *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, abstractSimpleDecl *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const abstractSimpleDecl *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, abstractStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const abstractStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, abstractTypeDeclNode *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const abstractTypeDeclNode *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, arrayDecl*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const arrayDecl*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, assignStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const assignStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, caseNode*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const caseNode*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, caseStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const caseStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, char&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const char& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, constDecl *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const constDecl *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, field*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const field*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, forStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const forStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, functionCall *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const functionCall *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, functionNode *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const functionNode *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gotoStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gotoStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ifStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ifStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, literal*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const literal*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, parameter *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const parameter *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, recordDecl *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const recordDecl *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, repeatStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const repeatStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, rootProgram*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const rootProgram*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *> && v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *> & v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::tuple<std::string, std::vector<parameter *> *>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::tuple<std::string, std::vector<parameter *> *>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<abstractExpr *> *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<abstractExpr *> *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<functionNode *> *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<functionNode *> *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<parameter *>*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<parameter *>*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<std::string>*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<std::string>*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, stmtList *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const stmtList *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, typeDefDecl *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const typeDefDecl *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, varDecl *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const varDecl *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, varNode *&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const varNode *& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, whileStmt*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const whileStmt*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr: // expr
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.template destroy< abstractExpr * > ();
        break;

      case symbol_kind::S_simple_type_decl: // simple_type_decl
        value.template destroy< abstractSimpleDecl * > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_non_label_stmt: // non_label_stmt
      case symbol_kind::S_else_clause: // else_clause
        value.template destroy< abstractStmt* > ();
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.template destroy< abstractTypeDeclNode * > ();
        break;

      case symbol_kind::S_array_type_decl: // array_type_decl
        value.template destroy< arrayDecl* > ();
        break;

      case symbol_kind::S_assign_stmt: // assign_stmt
        value.template destroy< assignStmt* > ();
        break;

      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_direction: // direction
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_case_expr: // case_expr
        value.template destroy< caseNode* > ();
        break;

      case symbol_kind::S_case_stmt: // case_stmt
      case symbol_kind::S_case_expr_list: // case_expr_list
        value.template destroy< caseStmt* > ();
        break;

      case symbol_kind::S_CHAR: // CHAR
        value.template destroy< char > ();
        break;

      case symbol_kind::S_const_part: // const_part
      case symbol_kind::S_const_expr_list: // const_expr_list
        value.template destroy< constDecl * > ();
        break;

      case symbol_kind::S_REAL: // REAL
        value.template destroy< double > ();
        break;

      case symbol_kind::S_field_decl: // field_decl
        value.template destroy< field* > ();
        break;

      case symbol_kind::S_for_stmt: // for_stmt
        value.template destroy< forStmt* > ();
        break;

      case symbol_kind::S_proc_stmt: // proc_stmt
        value.template destroy< functionCall * > ();
        break;

      case symbol_kind::S_function_decl: // function_decl
      case symbol_kind::S_procedure_decl: // procedure_decl
        value.template destroy< functionNode * > ();
        break;

      case symbol_kind::S_goto_stmt: // goto_stmt
        value.template destroy< gotoStmt* > ();
        break;

      case symbol_kind::S_if_stmt: // if_stmt
        value.template destroy< ifStmt* > ();
        break;

      case symbol_kind::S_SYS_CON: // SYS_CON
      case symbol_kind::S_SYS_FUNCT: // SYS_FUNCT
      case symbol_kind::S_READ: // READ
      case symbol_kind::S_SYS_PROC: // SYS_PROC
      case symbol_kind::S_SYS_TYPE: // SYS_TYPE
      case symbol_kind::S_INTEGER: // INTEGER
        value.template destroy< int > ();
        break;

      case symbol_kind::S_const_value: // const_value
        value.template destroy< literal* > ();
        break;

      case symbol_kind::S_para_type_list: // para_type_list
        value.template destroy< parameter * > ();
        break;

      case symbol_kind::S_record_type_decl: // record_type_decl
      case symbol_kind::S_field_decl_list: // field_decl_list
        value.template destroy< recordDecl * > ();
        break;

      case symbol_kind::S_repeat_stmt: // repeat_stmt
        value.template destroy< repeatStmt* > ();
        break;

      case symbol_kind::S_routine: // routine
      case symbol_kind::S_sub_routine: // sub_routine
        value.template destroy< rootProgram* > ();
        break;

      case symbol_kind::S_routine_head: // routine_head
        value.template destroy< std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *>  > ();
        break;

      case symbol_kind::S_ID: // ID
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_program_head: // program_head
        value.template destroy< std::string* > ();
        break;

      case symbol_kind::S_function_head: // function_head
        value.template destroy< std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *> > ();
        break;

      case symbol_kind::S_procedure_head: // procedure_head
        value.template destroy< std::tuple<std::string, std::vector<parameter *> *> > ();
        break;

      case symbol_kind::S_args_list: // args_list
        value.template destroy< std::vector<abstractExpr *> * > ();
        break;

      case symbol_kind::S_routine_part: // routine_part
        value.template destroy< std::vector<functionNode *> * > ();
        break;

      case symbol_kind::S_parameters: // parameters
      case symbol_kind::S_para_decl_list: // para_decl_list
        value.template destroy< std::vector<parameter *>* > ();
        break;

      case symbol_kind::S_name_list: // name_list
      case symbol_kind::S_var_para_list: // var_para_list
      case symbol_kind::S_val_para_list: // val_para_list
        value.template destroy< std::vector<std::string>* > ();
        break;

      case symbol_kind::S_routine_body: // routine_body
      case symbol_kind::S_compound_stmt: // compound_stmt
      case symbol_kind::S_stmt_list: // stmt_list
        value.template destroy< stmtList * > ();
        break;

      case symbol_kind::S_type_part: // type_part
      case symbol_kind::S_type_decl_list: // type_decl_list
        value.template destroy< typeDefDecl * > ();
        break;

      case symbol_kind::S_var_part: // var_part
      case symbol_kind::S_var_decl_list: // var_decl_list
        value.template destroy< varDecl * > ();
        break;

      case symbol_kind::S_type_definition: // type_definition
      case symbol_kind::S_var_decl: // var_decl
        value.template destroy< varNode * > ();
        break;

      case symbol_kind::S_while_stmt: // while_stmt
        value.template destroy< whileStmt* > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
#endif
      {
        YY_ASSERT (tok == token::END
                   || (token::YYerror <= tok && tok <= token::DOWNTO)
                   || (token::PLUS <= tok && tok <= token::SEMI));
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT (tok == token::BOOL);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, char v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const char& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT (tok == token::CHAR);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT (tok == token::REAL);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT ((token::SYS_CON <= tok && tok <= token::SYS_TYPE)
                   || tok == token::INTEGER);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT (tok == token::ID);
      }
    };

    /// Build a parser object.
    Parser (Scanner &scanner_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARRAY (location_type l)
      {
        return symbol_type (token::ARRAY, std::move (l));
      }
#else
      static
      symbol_type
      make_ARRAY (const location_type& l)
      {
        return symbol_type (token::ARRAY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make__BEGIN (location_type l)
      {
        return symbol_type (token::_BEGIN, std::move (l));
      }
#else
      static
      symbol_type
      make__BEGIN (const location_type& l)
      {
        return symbol_type (token::_BEGIN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE (location_type l)
      {
        return symbol_type (token::CASE, std::move (l));
      }
#else
      static
      symbol_type
      make_CASE (const location_type& l)
      {
        return symbol_type (token::CASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONST (location_type l)
      {
        return symbol_type (token::CONST, std::move (l));
      }
#else
      static
      symbol_type
      make_CONST (const location_type& l)
      {
        return symbol_type (token::CONST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO (location_type l)
      {
        return symbol_type (token::DO, std::move (l));
      }
#else
      static
      symbol_type
      make_DO (const location_type& l)
      {
        return symbol_type (token::DO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (location_type l)
      {
        return symbol_type (token::ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const location_type& l)
      {
        return symbol_type (token::ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make__END (location_type l)
      {
        return symbol_type (token::_END, std::move (l));
      }
#else
      static
      symbol_type
      make__END (const location_type& l)
      {
        return symbol_type (token::_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR (location_type l)
      {
        return symbol_type (token::FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_FOR (const location_type& l)
      {
        return symbol_type (token::FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FUNCTION (location_type l)
      {
        return symbol_type (token::FUNCTION, std::move (l));
      }
#else
      static
      symbol_type
      make_FUNCTION (const location_type& l)
      {
        return symbol_type (token::FUNCTION, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GOTO (location_type l)
      {
        return symbol_type (token::GOTO, std::move (l));
      }
#else
      static
      symbol_type
      make_GOTO (const location_type& l)
      {
        return symbol_type (token::GOTO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (location_type l)
      {
        return symbol_type (token::IF, std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const location_type& l)
      {
        return symbol_type (token::IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IN (location_type l)
      {
        return symbol_type (token::IN, std::move (l));
      }
#else
      static
      symbol_type
      make_IN (const location_type& l)
      {
        return symbol_type (token::IN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OF (location_type l)
      {
        return symbol_type (token::OF, std::move (l));
      }
#else
      static
      symbol_type
      make_OF (const location_type& l)
      {
        return symbol_type (token::OF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PACKED (location_type l)
      {
        return symbol_type (token::PACKED, std::move (l));
      }
#else
      static
      symbol_type
      make_PACKED (const location_type& l)
      {
        return symbol_type (token::PACKED, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PROCEDURE (location_type l)
      {
        return symbol_type (token::PROCEDURE, std::move (l));
      }
#else
      static
      symbol_type
      make_PROCEDURE (const location_type& l)
      {
        return symbol_type (token::PROCEDURE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PROGRAM (location_type l)
      {
        return symbol_type (token::PROGRAM, std::move (l));
      }
#else
      static
      symbol_type
      make_PROGRAM (const location_type& l)
      {
        return symbol_type (token::PROGRAM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RECORD (location_type l)
      {
        return symbol_type (token::RECORD, std::move (l));
      }
#else
      static
      symbol_type
      make_RECORD (const location_type& l)
      {
        return symbol_type (token::RECORD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REPEAT (location_type l)
      {
        return symbol_type (token::REPEAT, std::move (l));
      }
#else
      static
      symbol_type
      make_REPEAT (const location_type& l)
      {
        return symbol_type (token::REPEAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THEN (location_type l)
      {
        return symbol_type (token::THEN, std::move (l));
      }
#else
      static
      symbol_type
      make_THEN (const location_type& l)
      {
        return symbol_type (token::THEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE (location_type l)
      {
        return symbol_type (token::TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_TYPE (const location_type& l)
      {
        return symbol_type (token::TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNTIL (location_type l)
      {
        return symbol_type (token::UNTIL, std::move (l));
      }
#else
      static
      symbol_type
      make_UNTIL (const location_type& l)
      {
        return symbol_type (token::UNTIL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VAR (location_type l)
      {
        return symbol_type (token::VAR, std::move (l));
      }
#else
      static
      symbol_type
      make_VAR (const location_type& l)
      {
        return symbol_type (token::VAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (location_type l)
      {
        return symbol_type (token::WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const location_type& l)
      {
        return symbol_type (token::WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WITH (location_type l)
      {
        return symbol_type (token::WITH, std::move (l));
      }
#else
      static
      symbol_type
      make_WITH (const location_type& l)
      {
        return symbol_type (token::WITH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TO (location_type l)
      {
        return symbol_type (token::TO, std::move (l));
      }
#else
      static
      symbol_type
      make_TO (const location_type& l)
      {
        return symbol_type (token::TO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOWNTO (location_type l)
      {
        return symbol_type (token::DOWNTO, std::move (l));
      }
#else
      static
      symbol_type
      make_DOWNTO (const location_type& l)
      {
        return symbol_type (token::DOWNTO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYS_CON (int v, location_type l)
      {
        return symbol_type (token::SYS_CON, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SYS_CON (const int& v, const location_type& l)
      {
        return symbol_type (token::SYS_CON, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYS_FUNCT (int v, location_type l)
      {
        return symbol_type (token::SYS_FUNCT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SYS_FUNCT (const int& v, const location_type& l)
      {
        return symbol_type (token::SYS_FUNCT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_READ (int v, location_type l)
      {
        return symbol_type (token::READ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_READ (const int& v, const location_type& l)
      {
        return symbol_type (token::READ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYS_PROC (int v, location_type l)
      {
        return symbol_type (token::SYS_PROC, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SYS_PROC (const int& v, const location_type& l)
      {
        return symbol_type (token::SYS_PROC, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYS_TYPE (int v, location_type l)
      {
        return symbol_type (token::SYS_TYPE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SYS_TYPE (const int& v, const location_type& l)
      {
        return symbol_type (token::SYS_TYPE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOL (bool v, location_type l)
      {
        return symbol_type (token::BOOL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BOOL (const bool& v, const location_type& l)
      {
        return symbol_type (token::BOOL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER (int v, location_type l)
      {
        return symbol_type (token::INTEGER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INTEGER (const int& v, const location_type& l)
      {
        return symbol_type (token::INTEGER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REAL (double v, location_type l)
      {
        return symbol_type (token::REAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_REAL (const double& v, const location_type& l)
      {
        return symbol_type (token::REAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHAR (char v, location_type l)
      {
        return symbol_type (token::CHAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CHAR (const char& v, const location_type& l)
      {
        return symbol_type (token::CHAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID (std::string v, location_type l)
      {
        return symbol_type (token::ID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ID (const std::string& v, const location_type& l)
      {
        return symbol_type (token::ID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (location_type l)
      {
        return symbol_type (token::PLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const location_type& l)
      {
        return symbol_type (token::PLUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (location_type l)
      {
        return symbol_type (token::MINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const location_type& l)
      {
        return symbol_type (token::MINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUL (location_type l)
      {
        return symbol_type (token::MUL, std::move (l));
      }
#else
      static
      symbol_type
      make_MUL (const location_type& l)
      {
        return symbol_type (token::MUL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV (location_type l)
      {
        return symbol_type (token::DIV, std::move (l));
      }
#else
      static
      symbol_type
      make_DIV (const location_type& l)
      {
        return symbol_type (token::DIV, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD (location_type l)
      {
        return symbol_type (token::MOD, std::move (l));
      }
#else
      static
      symbol_type
      make_MOD (const location_type& l)
      {
        return symbol_type (token::MOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (location_type l)
      {
        return symbol_type (token::AND, std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const location_type& l)
      {
        return symbol_type (token::AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (location_type l)
      {
        return symbol_type (token::OR, std::move (l));
      }
#else
      static
      symbol_type
      make_OR (const location_type& l)
      {
        return symbol_type (token::OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (location_type l)
      {
        return symbol_type (token::NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_NOT (const location_type& l)
      {
        return symbol_type (token::NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (location_type l)
      {
        return symbol_type (token::EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const location_type& l)
      {
        return symbol_type (token::EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNEQUAL (location_type l)
      {
        return symbol_type (token::UNEQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_UNEQUAL (const location_type& l)
      {
        return symbol_type (token::UNEQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GE (location_type l)
      {
        return symbol_type (token::GE, std::move (l));
      }
#else
      static
      symbol_type
      make_GE (const location_type& l)
      {
        return symbol_type (token::GE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GT (location_type l)
      {
        return symbol_type (token::GT, std::move (l));
      }
#else
      static
      symbol_type
      make_GT (const location_type& l)
      {
        return symbol_type (token::GT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LE (location_type l)
      {
        return symbol_type (token::LE, std::move (l));
      }
#else
      static
      symbol_type
      make_LE (const location_type& l)
      {
        return symbol_type (token::LE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LT (location_type l)
      {
        return symbol_type (token::LT, std::move (l));
      }
#else
      static
      symbol_type
      make_LT (const location_type& l)
      {
        return symbol_type (token::LT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (location_type l)
      {
        return symbol_type (token::ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN (const location_type& l)
      {
        return symbol_type (token::ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LP (location_type l)
      {
        return symbol_type (token::LP, std::move (l));
      }
#else
      static
      symbol_type
      make_LP (const location_type& l)
      {
        return symbol_type (token::LP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RP (location_type l)
      {
        return symbol_type (token::RP, std::move (l));
      }
#else
      static
      symbol_type
      make_RP (const location_type& l)
      {
        return symbol_type (token::RP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LB (location_type l)
      {
        return symbol_type (token::LB, std::move (l));
      }
#else
      static
      symbol_type
      make_LB (const location_type& l)
      {
        return symbol_type (token::LB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RB (location_type l)
      {
        return symbol_type (token::RB, std::move (l));
      }
#else
      static
      symbol_type
      make_RB (const location_type& l)
      {
        return symbol_type (token::RB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOTDOT (location_type l)
      {
        return symbol_type (token::DOTDOT, std::move (l));
      }
#else
      static
      symbol_type
      make_DOTDOT (const location_type& l)
      {
        return symbol_type (token::DOTDOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (location_type l)
      {
        return symbol_type (token::DOT, std::move (l));
      }
#else
      static
      symbol_type
      make_DOT (const location_type& l)
      {
        return symbol_type (token::DOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMI (location_type l)
      {
        return symbol_type (token::SEMI, std::move (l));
      }
#else
      static
      symbol_type
      make_SEMI (const location_type& l)
      {
        return symbol_type (token::SEMI, l);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const { return yyla_; }
      symbol_kind_type token () const { return yyla_.kind (); }
      const location_type& location () const { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 382,     ///< Last index in yytable_.
      yynnts_ = 55,  ///< Number of nonterminal symbols.
      yyfinal_ = 5 ///< Termination state number.
    };


    // User arguments.
    Scanner &scanner;

  };


#line 20 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.y"
} // TOY_COMPILER
#line 3250 "/Users/xuewei/OneDrive - zju.edu.cn/code/cpp/toy_compiler/src/parser.tab.hh"




#endif // !YY_YY_USERS_XUEWEI_ONEDRIVE_ZJU_EDU_CN_CODE_CPP_TOY_COMPILER_SRC_PARSER_TAB_HH_INCLUDED

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* require bison 3.0 or later */
%require  "3.0"

/* use C++ interface */
%language "c++"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug 

/* verbose error messages */
%define parse.error verbose

/* write out a header file containing the token defines */

%locations
%define api.namespace {TOY_COMPILER}
%define api.parser.class {Parser}

%code requires{
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
}

%parse-param { Scanner &scanner }
%code{
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
}

%define api.value.type variant
%define parse.assert

// define the priority of operators
%right  ASSIGN
%left   OR
%left   AND
%left   NOT
%left   EQUAL UNEQUAL GE GT LE LT 
%left   PLUS MINUS
%left   MUL DIV MOD

%token  END     0       "end of file"

%token  ARRAY
%token  _BEGIN
%token  CASE
%token  CONST
%token  DO
%token  ELSE
%token  _END
%token  FOR
%token  FUNCTION
%token  GOTO
%token  IF
%token  IN
%token  OF
%token  PACKED
%token  PROCEDURE
%token  PROGRAM
%token  RECORD
%token  REPEAT
%token  THEN
%token  TYPE
%token  UNTIL
%token  VAR
%token  WHILE
%token  WITH
%token  TO
%token  DOWNTO

%token  <int>           SYS_CON
%token  <int>           SYS_FUNCT
%token  <int>           READ
%token  <int>           SYS_PROC
%token  <int>           SYS_TYPE

%token  <bool>          BOOL
%token  <int>           INTEGER
%token  <double>        REAL
%token  <char>          CHAR
%token  <std::string>   ID

%token  PLUS MINUS MUL DIV MOD AND OR NOT EQUAL UNEQUAL GE GT LE LT ASSIGN

%token  LP
%token  RP
%token  LB
%token  RB
%token  COMMA
%token  COLON
%token  DOTDOT
%token  DOT
%token  SEMI

%type   <bool> direction
%type	<std::string*> program_head
%type   <std::pair<std::vector<abstractTypeDeclNode *> *, std::vector<functionNode *> *> > routine_head
%type   <rootProgram*> routine sub_routine
%type   <stmtList *> routine_body
%type   <std::vector<functionNode *> *> routine_part
%type   <functionNode *> function_decl procedure_decl
%type   <functionCall *> proc_stmt
%type   <std::tuple<std::string, std::vector<parameter *> *, abstractSimpleDecl *>> function_head
%type   <std::tuple<std::string, std::vector<parameter *> *>> procedure_head
%type   <abstractExpr *> factor term expr expression
%type   <literal*> const_value
%type   <constDecl *> const_part const_expr_list
%type   <assignStmt*> assign_stmt
%type 	<abstractStmt*> else_clause stmt non_label_stmt
%type 	<ifStmt*> if_stmt
%type   <caseStmt*> case_stmt
%type   <whileStmt*> while_stmt
%type   <repeatStmt*> repeat_stmt
%type   <forStmt*> for_stmt
%type   <gotoStmt*> goto_stmt
%type   <stmtList *> compound_stmt stmt_list
%type   <caseNode*> case_expr
%type   <caseStmt*> case_expr_list
%type   <std::vector<abstractExpr *> *> args_list
%type   <varNode *> type_definition var_decl
%type   <varDecl *> var_part var_decl_list
%type   <abstractTypeDeclNode *> type_decl
%type   <typeDefDecl *> type_part type_decl_list  
%type   <abstractSimpleDecl *> simple_type_decl
%type   <arrayDecl*> array_type_decl
%type   <recordDecl *> record_type_decl field_decl_list
%type   <field*> field_decl
%type   <parameter *> para_type_list
%type   <std::vector<parameter *>*> para_decl_list parameters
%type   <std::vector<std::string>*> name_list var_para_list val_para_list


%%
program:
// TODO: add ast root to symtab
        program_head  routine  DOT
        {
            //auto t = globalsymtab->newSymTable($1);
            // globalsymtab->SymTable.insert()
            root = $2;
        }
        ;

program_head:
        PROGRAM  ID  SEMI
        {
            $$ = new std::string($2); // program head can be just a string
        }
        ;
routine:
        routine_head  routine_body
        {
            $$ = new rootProgram();
            $$->getDecls() = std::move(*($1.first));
            $$->getFuncs() = std::move(*($1.second));
            $$->getStmts() = std::move(*($2));
            $$->setLineno(@1.begin.line);
        }
        ;

sub_routine:
        routine_head  routine_body
        {

        }
        ;

routine_head:
        label_part  const_part  type_part  var_part  routine_part
        {
        	auto decls = new std::vector<abstractTypeDeclNode *>();
            auto f = [=](abstractTypeDeclNode *d) {
                decls->push_back(d);
            };
            decls->push_back($2);
            decls->push_back($3);
            decls->push_back($4);
            $$ = std::make_pair(decls, $5);
        }
        ;

label_part:
        {
        }
        ;

const_part:
        CONST  const_expr_list
        {
            $$ = $2;
        }
        |
        {
        }
        ;

const_expr_list:
        const_expr_list  ID  EQUAL  const_value  SEMI
        {
            $$->addConstDecl($2, $4);
        }
        |  ID  EQUAL  const_value  SEMI
        {
            $$ = new constDecl();
            $$->addConstDecl($1, $3);
            $$->setLineno(@$.begin.line);
        }
        ;

const_value:
        INTEGER
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::INTEGER;
            v->int_value = $1;
            $$ = new literal(v, t);
            $$->setLineno(@1.begin.line);
        }
        |  REAL
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::REAL;
            v->real_value = $1;
            $$ = new literal(v, t);
            $$->setLineno(@1.begin.line);
        }
        |  CHAR
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::CHAR;
            v->char_value = $1;
            $$ = new literal(v, t);
            $$->setLineno(@1.begin.line);
        }
        |  BOOL
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::BOOLEAN;
            v->bool_value = $1;
            $$ = new literal(v, t);
            $$->setLineno(@1.begin.line);
        }
        |  SYS_CON
        {
            auto t = new const_valueType();
            auto v = new expValue();
            if($1 == false) {
                t->sys_type = TOY_COMPILER::FALSE;
            } else if($1 == true) {
                t->sys_type = TOY_COMPILER::TRUE;
            } else if($1 == 2147483647) {
                t->sys_type = TOY_COMPILER::MAXINT;
            }
            v->bool_value = $1;
            $$ = new literal(v, t);
            $$->setLineno(@1.begin.line);
        }
        ;

type_part:
        TYPE type_decl_list
        {
            $$ = $2;
        }
        |
        {

        }
        ;

type_decl_list:
        type_decl_list  type_definition
        {
            $$->addTypeDef($2);
        }
        |  type_definition
        {
            $$ = new typeDefDecl();
            $$->addTypeDef($1);
            $$->setLineno(@$.begin.line);
        }
        ;

type_definition:
        ID  EQUAL  type_decl  SEMI
        {
            auto ns = new std::vector<std::string>();
            ns->push_back($1);
            $$ = new varNode(ns, $3);
            $$->setLineno(@1.begin.line);
        }
        ;

type_decl:
        simple_type_decl
        {
            $$ = $1;
        }
        |  array_type_decl
        {
            $$ = $1;
        }
        |  record_type_decl
        {
            $$ = $1;
        }
        ;

simple_type_decl:
        SYS_TYPE
        {
            TOY_COMPILER::valType t;
            if ($1 == 1)
                t = BOOLEAN;
            else if ($1 == 2)
                t = CHAR;
            else if ($1 == 3)
                t = INTEGER;
            else
                t = REAL;
            $$ = new simpleDecl(t);
            $$->setLineno(@1.begin.line);

        }
        |  ID
        {
            auto name = new std::vector<std::string>();
            name->push_back($1);

            $$ = new namesDecl(*name, false);
            $$->setLineno(@1.begin.line);
        }
        |  LP  name_list  RP
        {
            auto names = new std::vector<std::string>();
            auto f = [=](std::string &name) {
                names->push_back(name);
            };
            for_each($2->begin(), $2->end(), f);
            $$ = new namesDecl(*names, false);
            $$->setLineno(@1.begin.line);
        }
        |  const_value  DOTDOT  const_value
        {
            $$ = new rangeDecl(false, $1, false, $3);
            $$->setLineno(@1.begin.line);
        }
        |  MINUS  const_value  DOTDOT  const_value
        {
            $$ = new rangeDecl(true, $2, false, $4);
            $$->setLineno(@1.begin.line);
        }
        |  MINUS  const_value  DOTDOT  MINUS  const_value
        {
            $$ = new rangeDecl(true, $2, true, $5);
            $$->setLineno(@1.begin.line);
        }
        |  ID  DOTDOT  ID
        {
            $$ = new rangeDecl($1, $3);
            $$->setLineno(@1.begin.line);
        }
        ;

array_type_decl:
        ARRAY  LB  simple_type_decl  RB  OF  type_decl
        {
            $$ = new arrayDecl($3, $6);
            $$->setLineno(@1.begin.line);
        }
        ;

record_type_decl:
        RECORD  field_decl_list  _END
        {
            $$ = $2;
        }
        ;

field_decl_list:
        field_decl_list  field_decl
        {
            $$ = $1;
            $$->addRecord(*$2);
        }
        |  field_decl
        {
            $$ = new recordDecl();
            $$->addRecord(*$1);
            $$->setLineno(@$.begin.line);
        }
        ;

field_decl:
        name_list  COLON  type_decl  SEMI
        {
            $$ = new field($1, $3);
            $$->setLineno(@1.begin.line);
        }
        ;

name_list:
        name_list  COMMA  ID
        {
            $$ = $1;
            $$->push_back($3);
        }
        |  ID
        {
            $$ = new std::vector<std::string>();
            $$->push_back($1);
        }
        ;

var_part:
        VAR  var_decl_list
        {
            $$ = $2;
        }
        |
        {
        }
        ;

var_decl_list:
        var_decl_list  var_decl
        {
            $$ = $1;
            $$->addDecl($2);
        }
        |  var_decl
        {
            $$ = new varDecl();
            $$->setLineno(@1.begin.line);
            $$->addDecl($1);
        }
        ;

var_decl:
        name_list  COLON  type_decl  SEMI
        {
            $$ = new varNode($1, $3);
            $$->setLineno(@1.begin.line);
        }
        ;

routine_part:
        routine_part  function_decl
        {
            $$ = $1;
            $$->push_back($2);
        }
        |  routine_part  procedure_decl
        {
            $$ = $1;
            $$->push_back($2);
        }
        |  function_decl
        {
            $$ = new std::vector<functionNode *>();
            $$->push_back($1);
        }
        |  procedure_decl
        {
            $$ = new std::vector<functionNode *>();
            $$->push_back($1);
        }
        |
        {

        }
        ;

function_decl:
        function_head  SEMI  sub_routine  SEMI {
        	$$ = new functionNode(std::get<0>($1), std::get<1>($1), $3, std::get<2>($1));
            $$->setLineno(@1.begin.line);
        }
        ;

function_head:
        FUNCTION  ID  parameters  COLON  simple_type_decl
        {
            $$ = std::make_tuple($2, $3, $5);
        }
        ;

procedure_decl:
        procedure_head  SEMI  sub_routine  SEMI 
        {
            $$ = new functionNode(std::get<0>($1), std::get<1>($1), $3);
            $$->setLineno(@1.begin.line);
        }
        ;

procedure_head:
        PROCEDURE ID parameters
        {
            $$ = std::make_tuple($2, $3);
        }
        ;

parameters:
        LP  para_decl_list  RP
        {
            $$ = $2;
        }
        |
        {
        }
        ;

para_decl_list:
        para_decl_list  SEMI  para_type_list
        {
            $$ = $1;
            $$->push_back($3);
        }
        | para_type_list
        {
            $$ = new std::vector<parameter *>();
            $$->push_back($1);
        }
        ;

para_type_list:
        var_para_list COLON  simple_type_decl
        {
            $$ = new parameter(TOY_COMPILER::REFER, *($1), $3);
            $$->setLineno(@1.begin.line);
        }
        |  val_para_list  COLON  simple_type_decl
        {
            $$ = new parameter(TOY_COMPILER::VALUE, *($1), $3);
            $$->setLineno(@1.begin.line);
        }
        ;

var_para_list:
        VAR  name_list
        {
            $$ = $2;
        }
        ;

val_para_list:
        name_list
        {
            $$ = $1;
        }
        ;

routine_body:
        compound_stmt { $$ = $1; }
        ;

compound_stmt:
        _BEGIN  stmt_list  _END {$$ = $2;}
        ;

stmt_list:
        stmt_list  stmt  SEMI {$1->addStmt($2); $$ = $1;}
        |  
        {
            $$ = new stmtList();
            $$->setLineno(@$.begin.line);
        }
        ;
stmt:
        INTEGER  COLON  non_label_stmt 
        {
            $$ = $3;
            //globalsymtab->Label.insert($1, $3);
        }
        |  non_label_stmt {$$ = $1;}
        ;

non_label_stmt:
        assign_stmt {$$ = $1;}
        | proc_stmt {$$ = $1;}
        | compound_stmt {$$ = $1;}
        | if_stmt {$$ = $1;}
        | repeat_stmt {$$ = $1;}
        | while_stmt {$$ = $1;}
        | for_stmt {$$ = $1;}
        | case_stmt {$$ = $1;}
        | goto_stmt {$$ = $1;}
        ;

assign_stmt:
        ID  ASSIGN  expression 
        {
            auto l = new variableNode($1);
            l->setLineno(@1.begin.line);
            $$ = new assignStmt(l, $3);
            $$->setLineno(@1.begin.line);
        }
        | ID LB expression RB ASSIGN expression 
        {
            auto l = new mathExpr(TOY_COMPILER::LBRB, new variableNode($1), $3);
            l->setLineno(@1.begin.line);
            $$ = new assignStmt(l, $6);
            $$->setLineno(@1.begin.line);
        }
        | ID  DOT  ID  ASSIGN  expression 
        {
            auto l = new mathExpr(TOY_COMPILER::DOT, new variableNode($1), new variableNode($3));
            l->setLineno(@1.begin.line);
            $$ = new assignStmt(l, $5);
            $$->setLineno(@1.begin.line);
        }
        ;

proc_stmt:
        ID  LP  RP
        {
            $$ = new functionCall($1, nullptr);
            $$->setLineno(@1.begin.line);
        }
        |  ID  LP  args_list  RP 
        {
            $$ = new functionCall($1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  SYS_PROC  LP  RP
        {
            if ($1 == 8) {
                $$ = new functionCall("write", nullptr);
            } else if ($1 == 9) {
                $$ = new functionCall("writeln", nullptr);
            }
            $$->setLineno(@1.begin.line);
        }
        |  SYS_PROC  LP  args_list  RP 
        {
            if ($1 == 8) {
                $$ = new functionCall("write", $3);
            } else if ($1 == 9) {
                $$ = new functionCall("writeln", $3);
            }
            $$->setLineno(@1.begin.line);
        }
// TODO: add factor class
        |  READ  LP  factor  RP
        {
            auto args = new std::vector<abstractExpr *>();
            args->push_back($3);
            $$ = new functionCall("read", args);
            $$->setLineno(@1.begin.line);
        }
        ;

if_stmt:
        IF  expression  THEN  stmt  else_clause 
        {
            $$ = new ifStmt($2, $4, $5);
            $$->setLineno(@1.begin.line);
        }
        ;

else_clause:
        ELSE stmt {$$ = $2;}
        |  {$$ = nullptr;}
        ;

repeat_stmt:
        REPEAT  stmt_list  UNTIL  expression 
        {
            $$ = new repeatStmt($4, $2);
            $$->setLineno(@1.begin.line);
        }
        ;

while_stmt:
        WHILE  expression  DO stmt 
        {
            $$ = new whileStmt($2, $4);
            $$->setLineno(@1.begin.line);
        }
        ;

for_stmt:
        FOR  ID  ASSIGN  expression  direction  expression  DO stmt 
        {
            $$ = new forStmt($2, $4, $6, $5, $8);
            $$->setLineno(@1.begin.line);
        }
        ;

direction:
        TO {$$ = true;}
        | DOWNTO {$$ = false;}
        ;

case_stmt:
        CASE expression OF case_expr_list  _END 
        {
            $$ = $4;
            $$->addCond($2);
        }
        ;

case_expr_list:
        case_expr_list  case_expr 
        {
            $$ = $1;
            $$->addCase($2);
        }
        |  case_expr 
        {
            $$ = new caseStmt();
            $$->addCase($1);
            $$->setLineno(@1.begin.line);
        }
        ;

case_expr:
        const_value  COLON  stmt  SEMI 
        {
            $$ = new caseNode($1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  ID  COLON  stmt  SEMI 
        {
            $$ = new caseNode(new variableNode($1), $3);
            $$->setLineno(@1.begin.line);
        }
        ;

goto_stmt:
        GOTO  INTEGER 
        {
            $$ = new gotoStmt($2);
            $$->setLineno(@1.begin.line);
        }
        ;

expression:
        expression  GE  expr 
        {
            $$ = new mathExpr(TOY_COMPILER::GE, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  expression  GT  expr 
        {
            $$ = new mathExpr(TOY_COMPILER::GT, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  expression  LE  expr 
        {
            $$ = new mathExpr(TOY_COMPILER::LE, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  expression  LT  expr 
        {
            $$ = new mathExpr(TOY_COMPILER::LT, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  expression  EQUAL  expr 
        {
            $$ = new mathExpr(TOY_COMPILER::EQUAL, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  expression  UNEQUAL  expr 
        {
            $$ = new mathExpr(TOY_COMPILER::UNEQUAL, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  expr 
        {
            $$ = $1;
        }
        ;

expr:
        expr  PLUS  term 
        {
            $$ = new mathExpr(TOY_COMPILER::PLUS, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  expr  MINUS  term 
        {
            $$ = new mathExpr(TOY_COMPILER::MINUS, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  expr  OR  term 
        {
            $$ = new mathExpr(TOY_COMPILER::OR, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  term {$$ = $1;}
        ;

term:
        term  MUL  factor 
        {
            $$ = new mathExpr(TOY_COMPILER::MUL, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  term  DIV  factor 
        {
            $$ = new mathExpr(TOY_COMPILER::DIV, $1, $3);
            $$->setLineno(@1.begin.line);
	    }
        |  term  MOD  factor 
        {
            $$ = new mathExpr(TOY_COMPILER::MOD, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  term  AND  factor 
        {
            $$ = new mathExpr(TOY_COMPILER::AND, $1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  factor
        {
            $$ = $1;
        }
        ;

factor:
        ID 
        {
            $$ = new variableNode($1);
            $$->setLineno(@1.begin.line);
        }
        |  ID  LP  RP
        {
            $$ = new functionCall($1, nullptr);
            $$->setLineno(@1.begin.line);
        }
        |  ID  LP  args_list  RP 
        {
            $$ = new functionCall($1, $3);
            $$->setLineno(@1.begin.line);
        }
        |  SYS_FUNCT  LP  RP
        {
            std::string func_name;
            switch($1) {
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

            $$ = new functionCall(func_name, nullptr);
            $$->setLineno(@1.begin.line);
        }
        |  SYS_FUNCT  LP  args_list  RP 
        {
        	std::string func_name;
            switch($1) {
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

            $$ = new functionCall(func_name, $3);
            $$->setLineno(@1.begin.line);
        }
        |  const_value 
        {
            $$ = $1;
        }
        |  LP  expression  RP 
        {
            $$ = $2;
        }
        |  NOT  factor 
        {
            $$ = new mathExpr(TOY_COMPILER::NOT, $2, nullptr);
            $$->setLineno(@1.begin.line);
        }
        |  MINUS  factor 
        {
            $$ = new mathExpr(TOY_COMPILER::NOT, $2, nullptr);
            $$->setLineno(@1.begin.line);
        }
        |  ID  LB  expression  RB 
        {
            $$ = new mathExpr(TOY_COMPILER::LBRB, new variableNode($1), $3);
            $$->setLineno(@1.begin.line);
        }
        |  ID  DOT  ID 
        {
            $$ = new mathExpr(TOY_COMPILER::DOT, new variableNode($1), new variableNode($3));
            $$->setLineno(@1.begin.line);
	    }
        ;

args_list: 
        args_list  COMMA  expression 
        {
            $$ = $1;
            $$->push_back($3);
        }
        | expression 
        {
            $$ = new std::vector<abstractExpr *>();
            $$->push_back($1);
        }
        ;

%%

void TOY_COMPILER::Parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
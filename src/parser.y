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
    /* include for all driver functions */

    extern GlobalSymbol *globalsymtab;

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
%type   <rootProgram*> routine_body
%type   <mathExpr*> factor term expr expression
%type   <literal*> const_value
%type   <assignStmt*> assign_stmt
%type 	<abstractStmt*> else_clause stmt non_label_stmt
%type 	<ifStmt*> if_stmt case_stmt
%type   <whileStmt*> while_stmt
%type   <repeatStmt*> repeat_stmt
%type   <forStmt*> for_stmt
%type   <gotoStmt*> goto_stmt
%type   <functionNode*> proc_stmt
%type   <stmtList *> compound_stmt
%type   <caseNode*> case_expr
%type   <caseStmt*> case_expr_list
%type   <stmtList*> stmt_list
%type   <std::vector<abstractStmt*>*> args_list

%type   <typeDefDecl*> type_decl 
%type   <simpleDecl*> simple_type_decl
%type   <arrayDecl*> array_type_decl
%type   <recordDecl *> record_type_decl field_decl_list
%type   <field*> field_decl
%type   <parameter *> parameters 
%type   <std::vector<parameters *>*> para_decl_list para_type_list  var_para_list val_para_list
%type   <std::vector<std::string>*> name_list
%type   <std::tuple<std::string, <std::vector<parameters *>*>, abstractSimpleDecl *>> function_head


%%
program:
        program_head  routine  DOT
        {
            auto s = new Symbol($1, $2);
            globalSymtable->addSymbol(s);
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
            $$->getDecls = std::move(*($1.first));
            $$->getFunc = std::move(*($1.second));
            $$->getStmt = std::move(*($2));
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
        	auto decls = new std::vector<abstractDeclNode *>();
            auto f = [=](abstractDeclNode *d) {
                decls->push_back(d);
            }
            for_each($2->begin(), $2->end(), f);
            for_each($3->begin(), $3->end(), f);
            for_each($4->begin(), $4->end(), f);
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
        }
        |  REAL
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::REAL;
            v->real_value = $1;
            $$ = new literal(v, t);
        }
        |  CHAR
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::CHAR;
            v->char_value = $1;
            $$ = new literal(v, t);
        }
        |  BOOL
        {
            auto t = new const_valueType();
            auto v = new expValue();
            t->d_type = TOY_COMPILER::BOOLEAN;
            v->bool_value = $1;
            $$ = new literal(v, t);
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
        }
        ;

type_definition:
        ID  EQUAL  type_decl  SEMI
        {
            auto ns = new std::vector<std::string>();
            ns->push_back($1);
            $$ = new varNode(ns, $3);
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
            $$ = new simpleDecl($1);

        }
        |  ID
        {
            auto name = new std::vector<std::string>();
            name.push_back($1);

            $$ = new namesDecl(*name, false);
        }
        |  LP  name_list  RP
        {
            auto names = new std::vector<std::string>();
            auto f = [=](std::string &name) {
                names.push_back(name);
            }
            for_each($2->begin(), $2->end(), f);
            $$ = new namesDecl(*names, false);
        }
        |  const_value  DOTDOT  const_value
        {
            $$ = new rangeDecl(false, $1, false, $3);
        }
        |  MINUS  const_value  DOTDOT  const_value
        {
            $$ = new rangeDecl(true, $1, false, $3);
        }
        |  MINUS  const_value  DOTDOT  MINUS  const_value
        {
            $$ = new rangeDecl(true, $1, true, $3);
        }
        |  ID  DOTDOT  ID
        {
            $$ = new rangeDecl($1, $3);
        }
        ;

array_type_decl:
        ARRAY  LB  simple_type_decl  RB  OF  type_decl
        {
            $$ = new arrayDecl($3, $6);
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
            $$->addRecord($2);
        }
        |  field_decl
        {
            $$ = new recordDecl();
            $$->addRecord($1);
        }
        ;

field_decl:
        name_list  COLON  type_decl  SEMI
        {
            $$ = new field($1, $3);
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
            $$->addDecl($1);
        }
        ;

var_decl:
        name_list  COLON  type_decl  SEMI
        {
            $$ = new varNode($1, $3);
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
            //TODO: 
        }
        |
        {

        }
        ;

function_decl:
        function_head  SEMI  sub_routine  SEMI {
        	$$ = new functionNode(get<0>($1), get<1>($1), $3, get<2>($1));
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
            $$ = new functionNode(get<0>($1), get<1>($1), $3);
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
        }
        |  val_para_list  COLON  simple_type_decl
        {
            $$ = new parameter(TOY_COMPILER::VALUE, *($1), $3);
        }
        ;

var_para_list:
        VAR  name_list
        {
            $$ = $2
        }
        ;

val_para_list:
        name_list
        {
            $$ = $1
        }
        ;

routine_body:
        compound_stmt { $$ = $1; }
        ;

compound_stmt:
        _BEGIN  stmt_list  _END {$$ = $2;}
        ;

stmt_list:
        stmt_list  stmt  SEMI {$1->push_back($2); $$ = $1;}
        |  {$$ = new stmtList();}
        ;
// TODO: add label to symtab
stmt:
        INTEGER  COLON  non_label_stmt {$$ = $3; /*add the label into the symtable*/ }
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
            $$ = new assignStmt(l, $3);
        }
        | ID LB expression RB ASSIGN expression 
        {
            auto l = new mathExpr(TOY_COMPILER::LBRB, new variableNode($1), $3);
            $$ = new assignStmt(l, $6);
        }
        | ID  DOT  ID  ASSIGN  expression 
        {
            auto l = new mathExpr(TOY_COMPILER::DOT, new variableNode($1), new variableNode($3));
            $$ = new assignStmt(l, $5);
        }
        ;

proc_stmt:
        ID  LP  RP
        {
            $$ = new functionCall($1, nullptr);
        }
        |  ID  LP  args_list  RP 
        {
            $$ = new functionCall($1, $3);
        }
        |  SYS_PROC  LP  RP
        {
            if ($1 == 8) {
                $$ = new functionCall("write", nullptr);
            } else if ($1 == 9) {
                $$ = new functionCall("writeln", nullptr);
            }
        }
        |  SYS_PROC  LP  args_list  RP 
        {
            if ($1 == 8) {
                $$ = new functionCall("write", $3);
            } else if ($1 == 9) {
                $$ = new functionCall("writeln", $3);
            }
        }
// TODO: add factor class
        |  READ  LP  factor  RP
        {
            $$ = new functionCall("read", $3);
        }
        ;

if_stmt:
        IF  expression  THEN  stmt  else_clause 
        {$$ = new ifStmt($2, $4, $5);}
        ;

else_clause:
        ELSE stmt {$$ = $2;}
        |  {$$ = nullptr;}
        ;

repeat_stmt:
        REPEAT  stmt_list  UNTIL  expression 
        {$$ = new repeatStmt($4, $2);}
        ;

while_stmt:
        WHILE  expression  DO stmt {
        $$ = new whileStmt($2, $4);
        }
        ;

for_stmt:
        FOR  ID  ASSIGN  expression  direction  expression  DO stmt 
        {
        	

        }
        ;

direction:
        TO {$$ = true;}
        | DOWNTO {$$ = false;}
        ;

case_stmt:
        CASE expression OF case_expr_list  _END {
            Assert(!$4->empty(), "");
            $$ = new AST_If(new AST_Math(EQUAL_, $2, $4->at(0)->val),
                                       $4->at(0)->stmt,
                                       nullptr);
            if($4->size() > 1){
                AST_If* track = $$;
                for(unsigned int i=1; i<$4->size(); i++, track=(AST_If*)track->getDoElse()){
                    track->addRight(new AST_If(new AST_Math(EQUAL_, $2, $4->at(i)->val),
                                               $4->at(i)->stmt,
                                               nullptr));
                }
                //the last null pointer refers to 'default'
            }
        }
        ;

case_expr_list:
        case_expr_list  case_expr {$1->push_back($2); $$ = $1;}
        |  case_expr {$$ = new std::vector<caseUnit*>(); $$->push_back($1);}
        ;

case_expr:
        const_value  COLON  stmt  SEMI {$$ = new caseUnit($1, $3);}
        |  ID  COLON  stmt  SEMI {
        auto sym = driver.symtab.lookupVariable($1.c_str());
	if(!sym) {
		throw splException{@1.begin.line, @1.begin.column , "variable '" + $1 + "' is not declared in this scope.\n"};
	}
        $$ = new caseUnit(new AST_Sym($1, 0, sym),$3);
        }
        ;

goto_stmt:
        GOTO  INTEGER {$$ = new AST_Goto($2);}
        ;

expression:
        expression  GE  expr {
        $$ = new AST_Math(GE_, $1, $3);
        if(checkTypeUnequal($1->valType,SPL_TYPE::INT) && checkTypeUnequal($1->valType,SPL_TYPE::REAL)){
		// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column ,
			"operator '>=' expect type 'INT' or 'REAL', got '" + typeToString($1->valType) + "'.\n"};
	}
	if(checkTypeUnequal($3->valType ,SPL_TYPE::INT) && checkTypeUnequal($3->valType,SPL_TYPE::REAL)){
		// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column ,
			"operator '>=' expect type 'INT' or 'REAL', got '" + typeToString($3->valType) + "'.\n"};
	}

	$$->valType = SPL_TYPE::BOOL;
        }
        |  expression  GT  expr {
        $$ = new AST_Math(GT_, $1, $3);
        if(checkTypeUnequal($1->valType, SPL_TYPE::INT) && checkTypeUnequal($1->valType ,SPL_TYPE::REAL)){
		// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column ,
			"operator '>' expect type 'INT' or 'REAL', got '" + typeToString($1->valType) + "'.\n"};
	}
	if(checkTypeUnequal($3->valType,SPL_TYPE::INT) && checkTypeUnequal($3->valType ,SPL_TYPE::REAL)){
		// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column ,
			"operator '>' expect type 'INT' or 'REAL', got '" + typeToString($3->valType) + "'.\n"};
	}

	$$->valType = SPL_TYPE::BOOL;
        }
        |  expression  LE  expr {
        $$ = new AST_Math(LE_, $1, $3);
        if(checkTypeUnequal($1->valType ,SPL_TYPE::INT) && checkTypeUnequal($1->valType, SPL_TYPE::REAL)){
		// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column ,
			"operator '<=' expect type 'INT' or 'REAL', got '" + typeToString($1->valType) + "'.\n"};
	}
	if(checkTypeUnequal($3->valType, SPL_TYPE::INT) && checkTypeUnequal($3->valType, SPL_TYPE::REAL)){
		// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column ,
			"operator '<=' expect type 'INT' or 'REAL', got '" + typeToString($3->valType) + "'.\n"};
	}

	$$->valType = SPL_TYPE::BOOL;
        }
        |  expression  LT  expr {
        $$ = new AST_Math(LT_, $1, $3);
        if(checkTypeUnequal($1->valType,SPL_TYPE::INT) && checkTypeUnequal($1->valType, SPL_TYPE::REAL)){
		// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column ,
                	"operator '<' expect type 'INT' or 'REAL', got '" + typeToString($1->valType) + "'.\n"};
	}
	if(checkTypeUnequal($3->valType,SPL_TYPE::INT) && checkTypeUnequal($3->valType, SPL_TYPE::REAL)){
		// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column ,
			"operator '<' expect type 'INT' or 'REAL', got '" + typeToString($3->valType) + "'.\n"};
	}

	$$->valType = SPL_TYPE::BOOL;

        }
        |  expression  EQUAL  expr {
        $$ = new AST_Math(EQUAL_, $1, $3);
        if(checkTypeUnequal($1->valType, $3->valType)){
		// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column ,
		"operator '==' expect two operands with same type .\n"};
	}
	$$->valType = SPL_TYPE::BOOL;
        }
        |  expression  UNEQUAL  expr {
        $$ = new AST_Math(UNEQUAL_, $1, $3);
        if(checkTypeUnequal($1->valType, $3->valType)){

		throw splException{@3.begin.line, @3.begin.column ,
                "operator '!=' expect two operands with same type .\n"};
	}

        $$->valType = SPL_TYPE::BOOL;

        }
        |  expr {$$ = $1;}
        ;

expr:
        expr  PLUS  term {
        $$ = new AST_Math(PLUS_, $1, $3);
        if(checkTypeUnequal($1->valType, SPL_TYPE::INT) && checkTypeUnequal($1->valType ,SPL_TYPE::REAL)){

	// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column ,
		"operator '+' expect type 'INT' or 'REAL', got '" + typeToString($1->valType) + "'.\n"};
	}

	if(checkTypeUnequal($3->valType,SPL_TYPE::INT) && checkTypeUnequal($3->valType,SPL_TYPE::REAL)){

	// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column,
		"operator '+' expect type 'INT' or 'REAL', got '" + typeToString($3->valType) + "'.\n"};
	}

	if(checkTypeEqual($1->valType, SPL_TYPE::REAL) || checkTypeEqual($3->valType, SPL_TYPE::REAL)) {
		$$->valType = SPL_TYPE::REAL;
	}else{
		$$->valType = SPL_TYPE::INT;
	}
        }
        |  expr  MINUS  term {
        $$ = new AST_Math(MINUS_, $1, $3);
        if(checkTypeUnequal($1->valType ,SPL_TYPE::INT) && checkTypeUnequal($1->valType, SPL_TYPE::REAL)){

	// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column,
		"operator '-' expect type 'INT' or 'REAL', got '" + typeToString($1->valType) + "'.\n"};
	}

	if(checkTypeUnequal($3->valType ,SPL_TYPE::INT) && checkTypeUnequal($3->valType, SPL_TYPE::REAL)){

	// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column,
		"operator '-' expect type 'INT' or 'REAL', got '" + typeToString($3->valType) + "'.\n"};
	}
	if(checkTypeEqual($1->valType, SPL_TYPE::REAL) || checkTypeEqual($3->valType, SPL_TYPE::REAL)) {
		$$->valType = SPL_TYPE::REAL;
	}else{
		$$->valType = SPL_TYPE::INT;
	}
        }
        |  expr  OR  term {
        $$ = new AST_Math(OR_, $1, $3);
        if(checkTypeUnequal($1->valType, SPL_TYPE::BOOL)){

	// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column ,
		"operator 'OR' expect type 'BOOL', got '" + typeToString($1->valType) + "'.\n"};
	}

	if(checkTypeUnequal($3->valType, SPL_TYPE::BOOL)){

	// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column ,
		"operator 'OR' expect type 'BOOL', got '" + typeToString($3->valType) + "'.\n"};
	}
	$$->valType = SPL_TYPE::BOOL;
        }
        |  term {$$ = $1;}
        ;

term:
        term  MUL  factor {
        $$ = new AST_Math(MUL_, $1, $3);
        if(checkTypeUnequal($1->valType, SPL_TYPE::INT) && checkTypeUnequal($1->valType,SPL_TYPE::REAL)){
	// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column ,
		"operator '*' expect type 'INT' or 'REAL', got '" + typeToString($1->valType) + "'.\n"};
	}

	if(checkTypeUnequal($3->valType, SPL_TYPE::INT) && checkTypeUnequal($3->valType, SPL_TYPE::REAL)){

	// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column ,
		"operator '*' expect type 'INT' or 'REAL', got '" + typeToString($3->valType) + "'.\n"};
	}
	if(checkTypeEqual($1->valType, SPL_TYPE::REAL) || checkTypeEqual($3->valType, SPL_TYPE::REAL)) {
		$$->valType = SPL_TYPE::REAL;
	}else{
		$$->valType = SPL_TYPE::INT;
	}
        }
        |  term  DIV  factor {
        $$ = new AST_Math(DIV_, $1, $3);
        if(checkTypeUnequal($1->valType ,SPL_TYPE::INT) && checkTypeUnequal($1->valType, SPL_TYPE::REAL)){
	// 类型不匹配
		throw splException{@1.begin.line, @1.begin.column ,
		"operator '/' expect type 'INT' or 'REAL', got '" + typeToString($1->valType) + "'.\n"};
	}

	if(checkTypeUnequal($3->valType, SPL_TYPE::INT) && checkTypeUnequal($3->valType, SPL_TYPE::REAL)){
	// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column ,
		"operator '/' expect type 'INT' or 'REAL', got '" + typeToString($3->valType) + "'.\n"};
	}
	if(checkTypeEqual($1->valType, SPL_TYPE::REAL) || checkTypeEqual($3->valType,SPL_TYPE::REAL)) {
		$$->valType = SPL_TYPE::REAL;
	}else{
		$$->valType = SPL_TYPE::INT;
	}
	}
        |  term  MOD  factor {
        $$ = new AST_Math(MOD_, $1, $3);
        if(checkTypeUnequal($1->valType,SPL_TYPE::INT )){

         	// 类型不匹配
         	throw splException{@1.begin.line, @1.begin.column ,
			"operator 'MOD' expect type 'INT', got '" + typeToString($1->valType) + "'.\n"};
		}
        if(checkTypeUnequal($3->valType, SPL_TYPE::INT )){

		// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column ,
			"operator 'MOD' expect type 'INT', got '" + typeToString($3->valType) + "'.\n"};
	}
	$$->valType = SPL_TYPE::INT;
        }
        |  term  AND  factor {
        $$ = new AST_Math(AND_, $1, $3);
        if(checkTypeUnequal($1->valType, SPL_TYPE::BOOL)){
         	// 类型不匹配
         	throw splException{@1.begin.line, @1.begin.column ,
                		"operator 'AND' expect type 'BOOL', got '" + typeToString($1->valType) + "'.\n"};
         	}
        if(checkTypeUnequal($3->valType ,SPL_TYPE::BOOL)){

		// 类型不匹配
		throw splException{@3.begin.line, @3.begin.column ,
		"operator 'AND' expect type 'BOOL', got '" + typeToString($3->valType) + "'.\n"};
	}
	$$->valType = SPL_TYPE::BOOL;
        }

        |  factor {$$ = $1;}
        ;

factor:
        ID {
        // 检查sym table查看table的类型
        auto sym = driver.symtab.lookupVariable($1.c_str());
        if(!sym) {
        	throw splException{@1.begin.line, @1.begin.column , "variable '" + $1 + "' is not declared in this scope.\n"};
        }
        $$ = new AST_Sym($1, sym->scopeIndex, sym);
        $$->valType = sym->symbolType;
        }
        |  ID  LP  RP
        {
        // 检查sym table 查看func的返回值类型
        auto sym = driver.symtab.lookupFunction($1.c_str());
        if(!sym) {
                // 函数未定义
		throw splException{@1.begin.line, @1.begin.column , "function or procedure '" + $1 + "' is not declared in this scope.\n"};
        }
	std::vector<AST_Exp*>* emptyVec = new std::vector<AST_Exp*>();
	$$ = new AST_Func(false, $1, emptyVec, sym->scopeIndex, sym);
        $$->valType = sym->symbolType;
        }
        |  ID  LP  args_list  RP {
        // 检查sym table 查看func的返回值类型
        auto sym = driver.symtab.lookupFunction($1.c_str());
	if(!sym) {
		// 函数未定义
		throw splException{@1.begin.line, @1.begin.column , "function or procedure '" + $1 + "' is not declared in this scope.\n"};
	}
	if(sym->symbolType == UNKNOWN) {
		// procedure 不可以做为函数右值
		throw splException{@1.begin.line, @1.begin.column , "procedure '" + $1 + "' can not be used as rvalue.\n"};

	}
	// 查看参数列表的类型是否一致
	auto args_list = sym->subSymbolList;
	if(args_list->size()!=$3->size()){
		// 传入参数数目与定义不一致
		throw splException{@1.begin.line, @1.begin.column ,
		"function or procedure '" + $1 + "' expect " + std::to_string(args_list->size()) + " arguments, got " + std::to_string($3->size()) +".\n"};
	}
	int size = $3->size();
	for(auto i = 0 ; i < size ; i ++ ){
		// 检查数据类型是否一致
		if(checkTypeUnequal($3->at(i)->valType, args_list->at(i)->symbolType)){
			throw splException{@3.begin.line, @3.begin.column ,
                        "function or procedure '" + $1 + "' expect type '" + typeToString(args_list->at(i)->symbolType) + "', got type '"+ typeToString($3->at(i)->valType) +"'.\n"};
		}

		// 检查是否传递常量或者临时变量给引用类型
		if(args_list->at(i)->paraType == REFER && $3->at(i)->nodeType != AST_SYM) {
			throw splException{@3.begin.line, @3.begin.column ,
                        "can not pass temp result or literal as reference in function or procedure '" + $1 + "'n" };
		}
	}
        $$ = new AST_Func(false, $1, $3, sym->scopeIndex, sym);
        // 推导为返回值的数据类型
        $$->valType = sym->symbolType;
        }
        |  SYS_FUNCT  LP  RP
	{
            std::vector<AST_Exp*>* emptyVec = new std::vector<AST_Exp*>();
            $$ = new AST_Func($1, emptyVec);
	}
        |  SYS_FUNCT  LP  args_list  RP {
        	$$ = new AST_Func($1, $3);
        }
        |  const_value {
        $$ = $1;
        }
        |  LP  expression  RP {$$ = $2;}
        |  NOT  factor {
        $$ = new AST_Math(NOT_, $2, nullptr);
        $$->valType = SPL_TYPE::BOOL;
        }
        |  MINUS  factor {
        $$ = new AST_Math(MINUS__, $2, nullptr);
        $$->valType = $2->valType;
        }
        |  ID  LB  expression  RB {
        auto sym = driver.symtab.lookupVariable($1.c_str());
	if(!sym) {
		// 函数未定义
		throw splException{@1.begin.line, @1.begin.column , "variable '" + $1 + "' is not declared in this scope.\n"};
	}
	if($3->valType != INT) {
		throw splException{@1.begin.line, @1.begin.column , "index of array '" + $1 + "' must be type INT, get " + typeToString($3->valType) +".\n"};
	}
        $$ = new AST_Array(new AST_Sym($1, sym->scopeIndex, sym),$3);
        $$->valType = INT;
        }
        |  ID  DOT  ID {
        auto sym = driver.symtab.lookupVariable($1.c_str());
	if(!sym) {
		throw splException{@1.begin.line, @1.begin.column , "variable '" + $1 + "' is not declared in this scope.\n"};
	}
	$$ = new AST_Sym($1, sym->scopeIndex, sym);
	if(sym->symbolType != RECORD) {
		throw splException{@1.begin.line, @1.begin.column , "variable '" + $1 + "' is not record type.\n"};
	}
	auto members = sym->subSymbolMap;
	if(members == nullptr) {
		throw splException{@1.begin.line, @1.begin.column , "variable '" + $1 + "' has not members.\n"};
	}
	auto member = members->find($3);
	if(member == members->end()) {
		throw splException{@1.begin.line, @1.begin.column , "variable '" + $1 + "' has not member " + $3 +"\n"};
	}
        $$ = new AST_Dot(
	new AST_Sym($1, sym->scopeIndex, sym),
	new AST_Sym($3, member->second->scopeIndex, member->second));
	$$->valType = member->second->symbolType;
	}
        ;

args_list: 
        args_list  COMMA  expression {
        }
        | expression {
        }
        ;

%%
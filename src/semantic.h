#pragma once
#include"symtab.h"
#include "ast.h"
#include<map>
namespace TOY_COMPILER {
	class SPL_Semantic {
	public:
		class TOY_COMPILER::rootProgram *ast;
		FunctionSymbol Main;	//the Program 
		SymbolTable *NowTable;	//The Symbol table used now
		FunctionSymbol &NowFunction; //used for function initial, not the function we are in

		std::vector<std::string> error;	//error messages


		SPL_Semantic(class TOY_COMPILER::rootProgram *ast);	//for initiate

		int Semantic(class TOY_COMPILER::abstractAST *node);	//useless?

		Symbol Semantic_Const(class TOY_COMPILER::constNode *constNode);	//for const delcaration node
		int Semantic_ConstDecl(class TOY_COMPILER::constDecl *constDecl);	//for const delcaration list
		Symbol Semantic_SimpleDecl(class TOY_COMPILER::simpleDecl *simpleDecl);	//for simple declaration

		Symbol Semantic_NameDecl(TOY_COMPILER::namesDecl * nameDecl);	//for name list declaration and 
		//simple_type_decl £º NAME  |  LP  name_list  RP 
		Symbol Semantic_Var(class TOY_COMPILER::varNode *varNode, bool addTable);	//for variable declaration
		Symbol Semantic_VarDecl(class TOY_COMPILER::varDecl *varDecl);	//for variable declaration list
		Symbol Semantic_RangeDecl(class TOY_COMPILER::rangeDecl *rangeDecl);	//for range declaration	
		Symbol Semantic_RecordDecl(TOY_COMPILER::recordDecl * recordDecl);	//for range declaration list
		Symbol Semantic_TypeDecl(TOY_COMPILER::typeDefDecl *typeDefDecl);	//for type declaration list
		Symbol Semantic_Type(TOY_COMPILER::abstractTypeDeclNode *Decl);	//for type declaration
		Symbol Semantic_ArrayDecl(TOY_COMPILER::arrayDecl *arrayDecl);	//for array declaration

		int Semantic_StmtList(class TOY_COMPILER::stmtList *stmtList);	//for stmt list
		int Semantic_Stmt(class TOY_COMPILER::abstractStmt *Stmt);	//for a stmt, not known type
		int Semantic_Case(class TOY_COMPILER::caseStmt *caseStmt);	//for a case
		int Semantic_Repeat(class TOY_COMPILER::repeatStmt *repeatStmt);	//for a repeat stmt
		int Semantic_While(class TOY_COMPILER::whileStmt *whileStmt);	//for a while stmt
		int Semantic_For(class TOY_COMPILER::forStmt *forStmt);	//for a for stmt
		int Semantic_If(class TOY_COMPILER::ifStmt *ifStmt);	//for a ifstmt

		Symbol Semantic_Literal(literal *l);	//for literal
		Symbol Semantic_Assign(class TOY_COMPILER::assignStmt *assignStmt);	//for assign, check left value and type
		Symbol IsLeftValue(abstractExpr * Expr);	//for left value check
		Symbol Semantic_Expr(abstractExpr * Expr);	//for expr, unknown type
		Symbol Semantic_Call(class functionCall *functionCall);	//for function call
		int Semantic_Goto(class TOY_COMPILER::gotoStmt *Stmt);	//for goto, just check label exist
		int Semantic_Function(class TOY_COMPILER::functionNode *func);	//check for the Function declaration
		int Semantic_Arglist(std::vector<TOY_COMPILER::abstractTypeDeclNode *> *argList);	//for arglist, program and function
		int ArgCheck(std::vector<abstractExpr *> * args, FunctionSymbol function);	//check the argment when call
		Symbol Semantic_Record(class TOY_COMPILER::mathExpr *math);	//for record member calculate
		Symbol Semantic_Array(class TOY_COMPILER::mathExpr *math);	//for array calculate
		Symbol Semantic_Math(class TOY_COMPILER::mathExpr *math);	// for math
		int doSemantic();

		Symbol IsMember(std::string name, Symbol symbol) {
			int memberIndex = 0;
			for (memberIndex = 0; memberIndex < symbol.memberList.size(); memberIndex++) {
				if (name == symbol.memberList[memberIndex].name)return symbol.memberList[memberIndex];
			}
			return Symbol();
		}
		bool IsBaseType(Symbol s) {
			if (s.valType != INTEGER && s.valType != REAL && s.valType != BOOLEAN && s.valType != CHAR)return false;
			return true;
		}
		int CheckSameType(Symbol s1, Symbol s2) {
			if (s1.valType != s2.valType)return 0;
			if (IsBaseType(s1) && s1.TypeName != s2.TypeName)return 0;
			return 1;
		}
	};
}
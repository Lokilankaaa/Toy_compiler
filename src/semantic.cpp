#include "semantic.h"

namespace TOY_COMPILER {
	SPL_Semantic::SPL_Semantic(class TOY_COMPILER::rootProgram *ast) {
		Main = FunctionSymbol("program");
		this->NowFunction = Main;
		this->ast = ast;
	}


	int SPL_Semantic::doSemantic() {
		class TOY_COMPILER::rootProgram *Program = this->ast;
		std::vector<TOY_COMPILER::functionNode *> functions = ast->getFuncs;
		std::vector<TOY_COMPILER::functionNode *>::iterator funcIter = functions.begin();
		while (funcIter != ast->funcs.end()) {
			Semantic_Function(*funcIter);
		}
		stmtList stmts = ast->getStmts();
		std::vector<TOY_COMPILER::abstractTypeDeclNode *> decls = ast->getDecls();
		Semantic_Arglist(&decls);
		Semantic_StmtList(&stmts);
		
	}



	int SPL_Semantic::Semantic_Function(class TOY_COMPILER::functionNode *func) {
		FunctionSymbol FunctionSym = FunctionSymbol(func->getId());
		NowTable->insertFunction(FunctionSym);
		this->NowFunction = FunctionSym;
		SymbolTable* NewTable = globalsymtab.NewSymTable(func->getId, this->NowTable);
		this->NowTable = NewTable;
		Semantic_Arglist(func->getParams);
		Semantic_StmtList(func->getBody);
	}


	int SPL_Semantic::Semantic_Arglist(std::vector<TOY_COMPILER::abstractTypeDeclNode *> *argList) {
		std::vector<TOY_COMPILER::abstractTypeDeclNode *>::iterator argIter = argList->begin;
		while (argIter != argList->end()) {
			switch ((*argIter)->n_type)
			{
			case TOY_COMPILER::CONSTDECL:
				Semantic_ConstDecl((TOY_COMPILER::constDecl *)(*argIter));
				break;
			case TOY_COMPILER::RANGEDECL:
				Semantic_RangeDecl((TOY_COMPILER::rangeDecl *)(*argIter));
				break;
			case TOY_COMPILER::SIMPLEDCEL:
				Semantic_SimpleDecl((TOY_COMPILER::simpleDecl *)(*argIter));
				break;
			case TOY_COMPILER::NAMEDECL:
				Semantic_NameDecl((TOY_COMPILER::namesDecl *)(*argIter));
				break;
			case TOY_COMPILER::ARRAYDECL:
				Semantic_ArrayDecl((TOY_COMPILER::arrayDecl *)(*argIter));
				break;
			case TOY_COMPILER::VARDECL:
				Semantic_VarDecl((TOY_COMPILER::varDecl *)(*argIter));
				break;
			case TOY_COMPILER::TYPEDEF:
				Semantic_TypeDecl((TOY_COMPILER::typeDefDecl *)(*argIter));
				break;
			default:
				error.push_back("Wrong Declarations!");
				break;
			}
		}

	}

	Symbol SPL_Semantic::Semantic_ArrayDecl(TOY_COMPILER::arrayDecl *arrayDecl) {
		Symbol indexSymbol = Semantic_Type(arrayDecl->getSimpleType);
		Symbol elementSymbol = Semantic_Type(arrayDecl->getTypeDecl);
		Symbol arraySymbol = Symbol(TOY_COMPILER::ARRAY, TOY_COMPILER::ARRAY_S, (TOY_COMPILER::abstractAST *)arrayDecl, NowTable->scope);
		arraySymbol.setArray(indexSymbol, elementSymbol);
		NowFunction.AddArgs(arraySymbol);
		NowTable->insertSym(arraySymbol);
		return Symbol();
	}

	Symbol SPL_Semantic::Semantic_RecordDecl(TOY_COMPILER::recordDecl *recordDecl) {
		std::vector<TOY_COMPILER::field *> fields = recordDecl->getFields;
		Symbol recordSymbol = Symbol(TOY_COMPILER::COMP, TOY_COMPILER::RECORD_S, (TOY_COMPILER::abstractAST *)recordDecl, NowTable->scope);
		int fieldIndex = 0;
		for (fieldIndex = 0; fieldIndex < fields.size(); fieldIndex++) {
			int nameIndex = 0;
			TOY_COMPILER::field *field = fields[fieldIndex];
			std::vector<std::string> *nameList=field->getNamelist;
			Symbol fieldSybmol = Semantic_Type(field->getType);
			for (nameIndex = 0; nameIndex < nameList->size(); nameIndex++) {
				fieldSybmol.changeId((*nameList)[nameIndex]);
				recordSymbol.addMem(fieldSybmol);
			}
		}
		return recordSymbol;
	}

	Symbol SPL_Semantic::Semantic_TypeDecl(TOY_COMPILER::typeDefDecl *typeDefDecl) {
		std::vector<varNode *> *typeList = typeDefDecl->getNewType();
		int typeIndex = 0;
		for(typeIndex=0;typeIndex<typeList->size();typeIndex++){
			Symbol typeSymbol = Semantic_Var((*typeList)[typeIndex],false);
			typeSymbol.setIsType();
			typeSymbol.TypeName = typeSymbol.id;
			NowFunction.AddArgs(typeSymbol);
			NowTable->insertSym(typeSymbol);
			return typeSymbol;
		}
	}

	Symbol SPL_Semantic::Semantic_Type(TOY_COMPILER::abstractTypeDeclNode *Decl) {
		switch (Decl->n_type)
		{
		case RECORDDECL:
			return Semantic_RecordDecl((TOY_COMPILER::recordDecl *)Decl);
		case ARRAYDECL:
			return Semantic_ArrayDecl((TOY_COMPILER::arrayDecl *)Decl);
		case SIMPLEDCEL:
			return Semantic_SimpleDecl((TOY_COMPILER::simpleDecl *)Decl);
		case RANGEDECL:
			return Semantic_RangeDecl((TOY_COMPILER::rangeDecl *)Decl);
		case NAMEDECL:
			return Semantic_NameDecl((TOY_COMPILER::namesDecl *)Decl);
		case VARDECL:
			return Semantic_VarDecl((TOY_COMPILER::varDecl *)Decl);
		default:
			break;
		}
	}

	Symbol SPL_Semantic::Semantic_Const(class TOY_COMPILER::constNode *constNode) {
		Symbol SymbolExist = NowTable->findSym(constNode->getId());
		if (SymbolExist.null == 1) {
			Symbol s = Symbol(constNode->getId(), constNode->getType(), TOY_COMPILER::CONST_S, (TOY_COMPILER::abstractAST *)constNode, NowTable->scope);
			NowFunction.AddArgs(s);
			NowTable->insertSym(s);
			return s;
		}
		else error.push_back("Exist Symbol name!");
		return Symbol();
	}


	Symbol SPL_Semantic::Semantic_VarDecl(class TOY_COMPILER::varDecl *varDecl) {
		std::vector<TOY_COMPILER::varNode *> varList = varDecl->getDecls;
		std::vector<TOY_COMPILER::varNode *>::iterator var = varList.begin();
		while (var != varList.end()) {
			Semantic_Var(*var, true);
			var++;
		}
	}

	Symbol SPL_Semantic::Semantic_Var(class TOY_COMPILER::varNode *varNode, bool addTable) {
		Symbol SymbolExist = NowTable->findSym(varNode->getId());
		if (SymbolExist.null == 1) {
			Symbol varSymbol = Semantic_Type(varNode->getVarType);
			varSymbol.changeId(varNode->getId());
			if (varSymbol.symbolType == NAME_S)varSymbol.TypeName = varNode->getId();
			if (addTable) {
				NowFunction.AddArgs(varSymbol);
				NowTable->insertSym(varSymbol);
			}
			return varSymbol;
		}
		else error.push_back("Exist Symbol name!");
		return Symbol();
	}

	Symbol SPL_Semantic::Semantic_SimpleDecl(class TOY_COMPILER::simpleDecl *simpleDecl) {
		Symbol simpleSymbol = Symbol(simpleDecl->getval_type(), TOY_COMPILER::VAR_S, simpleDecl, NowTable->scope);
		return simpleSymbol;
	}

	Symbol SPL_Semantic::Semantic_NameDecl(TOY_COMPILER::namesDecl * nameDecl) {
		if (nameDecl->getIsNamelist) {
			Symbol typeSymbol = NowTable->findSym(nameDecl->getNames()[0]);
			if (typeSymbol.istype == 0) {
				error.push_back("Exist Symbol name!");
				return Symbol();
			}
			else {
				typeSymbol.istype = 0;
				return typeSymbol;
			}
		}
		else {
			std::vector<std::string> names = nameDecl->getNames();
			Symbol nameSymbol = Symbol(TOY_COMPILER::NAME, TOY_COMPILER::NAME_S, (TOY_COMPILER::abstractAST *)nameDecl, NowTable->scope);
			int nameIndex = 0;
			for (nameIndex = 0; nameIndex < names.size(); nameIndex++) {
				nameSymbol.addMem(Symbol(names[nameIndex]));
			}
			return nameSymbol;
		}

	}

	int SPL_Semantic::Semantic_ConstDecl(class TOY_COMPILER::constDecl *constDecl) {
		std::vector<TOY_COMPILER::constNode *> constList = constDecl->getDecls();
		int constIndex = 0;
		for(constIndex=0;constIndex<constList.size();constIndex++)Semantic_Const(constList[constIndex]);
	}

	Symbol SPL_Semantic::Semantic_RangeDecl(class TOY_COMPILER::rangeDecl *rangeDecl) {
		int beginIndex = rangeDecl->getLeftRange;
		int endIndex = rangeDecl->getRightRange;
		if (rangeDecl->getLeftSign)beginIndex = -beginIndex;
		if (rangeDecl->getRightSign)endIndex = -endIndex;
		return Symbol(TOY_COMPILER::RANGE,TOY_COMPILER::RANGE_S, rangeDecl, beginIndex, endIndex, NowTable->scope);
	}


	int SPL_Semantic::Semantic_If(class TOY_COMPILER::ifStmt *ifStmt) {
		Symbol cond=Semantic_Math(ifStmt->getCond());
		int errorReturn = 0;
		int execResult=Semantic_Stmt(ifStmt->getExecStmt());
		int elseResult=Semantic_Stmt(ifStmt->getElseStmt());
		if (cond.valType != BOOLEAN) {
			error.push_back("If condition type wrong!");
			errorReturn = -1;
		}
		if (execResult == -1 || elseResult == -1)errorReturn = -1;
		return errorReturn;
	}

	int SPL_Semantic::Semantic_Repeat(class TOY_COMPILER::repeatStmt *repeatStmt) {
		Symbol cond=Semantic_Math(repeatStmt->getCond);
		int list=Semantic_StmtList(repeatStmt->getStmtList);
		int errorReturn = list;
		if (cond.valType != BOOLEAN) {
			error.push_back("Repeat condition type wrong!");
			errorReturn = -1;
		}
		return errorReturn;
	}

	int SPL_Semantic::Semantic_While(class TOY_COMPILER::whileStmt *whileStmt) {
		Symbol cond=Semantic_Math(whileStmt->getCond);
		int list=Semantic_StmtList(whileStmt->getStmtlist);
		int errorReturn = list;
		if (cond.valType != BOOLEAN) {
			error.push_back("While condition type wrong!");
			errorReturn = -1;
		}
		return errorReturn;
	}

	int SPL_Semantic::Semantic_For(class TOY_COMPILER::forStmt *forStmt) {
		Symbol from=Semantic_Math(forStmt->getFrom);
		Symbol to=Semantic_Math(forStmt->getTo);
		int list=Semantic_StmtList(forStmt->getStmtlist);
		int errorReturn = list;
		if (from.null == 1 || to.null == 1)errorReturn=-1;
		return errorReturn;
	}

	int SPL_Semantic::Semantic_Case(class TOY_COMPILER::caseStmt *caseStmt) {
		Symbol cond=Semantic_Math(caseStmt->getCond);
		int errorReturn = 0;
		TOY_COMPILER::valType condType = cond.valType;
		if (condType != TOY_COMPILER::INTEGER&&condType != TOY_COMPILER::CHAR&&condType != BOOLEAN) {
			error.push_back("Case condition type wrong!");
			errorReturn = -1;
		}
		std::vector<TOY_COMPILER::caseNode *> caseExprList = caseStmt->getCases();
		std::vector<TOY_COMPILER::caseNode *>::iterator caseExpr = caseExprList.begin();
		while (caseExpr != caseExprList.end()) {
			if ((*caseExpr)->case_->getType.getType != condType){
				error.push_back("Wrong case type!");
				errorReturn = -1;
			}
			if (Semantic_Stmt((*caseExpr)->stmt) == -1)errorReturn = -1;
		}
		return errorReturn;
	}


	int SPL_Semantic::Semantic_Stmt(class TOY_COMPILER::abstractStmt *Stmt) {
		Symbol s = Symbol();
		switch (Stmt->n_type)
		{
		case TOY_COMPILER::CASESTMT:
			return Semantic_Case((class TOY_COMPILER::caseStmt *)Stmt);
		case TOY_COMPILER::REPEATSTMT:
			return Semantic_Repeat((class TOY_COMPILER::repeatStmt *)Stmt);
		case TOY_COMPILER::WHILESTMT:
			return Semantic_While((class TOY_COMPILER::whileStmt*)Stmt);
		case TOY_COMPILER::IFSTMT:
			return Semantic_If((class TOY_COMPILER::ifStmt*)Stmt);
		case TOY_COMPILER::FORSTMT:
			return Semantic_For((class TOY_COMPILER::forStmt *)Stmt);
		case TOY_COMPILER::GOTOSTMT:
			return Semantic_Goto((class TOY_COMPILER::gotoStmt *)Stmt);
		case TOY_COMPILER::ASSIGNSTMT:
			s=Semantic_Assign((class TOY_COMPILER::assignStmt *)Stmt);
			return -(s.null);
		case TOY_COMPILER::EXPRESSION:
			s=Semantic_Expr((class TOY_COMPILER::abstractExpr *)Stmt);
			return -(s.null);
		case TOY_COMPILER::STMTLIST:
			return Semantic_StmtList((class TOY_COMPILER::stmtList *)Stmt);
		case TOY_COMPILER::FUNCCALL:
			s=Semantic_Call((class TOY_COMPILER::functionCall *)Stmt);
			return -(s.null);
		default:
			error.push_back("Not a Stmt!");
			return -1;
		}
	}

	int SPL_Semantic::Semantic_Goto(class TOY_COMPILER::gotoStmt *Stmt) {
		int Label = Stmt->getLabel(); 
		std::map<int, abstractStmt*>::iterator LabelIter;
		LabelIter=GlobalSymbolTable.Label.find(Label);
		if (LabelIter == GlobalSymbolTable.Label.end()) {
			error.push_back("Not exist label for goto");
			return -1;
		}
	}

	int SPL_Semantic::Semantic_StmtList(class TOY_COMPILER::stmtList *stmtList) {
		std::vector<TOY_COMPILER::abstractStmt *>::iterator stmt = stmtList->getStmtList().begin();
		while (stmt != stmtList->getStmtList().end()) {
			Semantic(*stmt);
		}
	}


	Symbol SPL_Semantic::Semantic_Assign(class TOY_COMPILER::assignStmt *assignStmt) {
		Symbol left=IsLeftValue(assignStmt->getLhs);
		Symbol right=Semantic_Expr(assignStmt->getRhs);
		if (left.valType!=right.valType) {
			error.push_back("Assign on different types");
		}else if (left.valType == COMP && left.TypeName != right.TypeName) {
			error.push_back("Assign on different types");
		}
		return left;
	}

	Symbol SPL_Semantic::IsLeftValue(abstractExpr * Expr) {
		if (Expr->n_type == MATHEXPR) {
			Symbol s=Semantic_Math((TOY_COMPILER::mathExpr *)Expr);
			if (((mathExpr *)Expr)->getOp() != LPLB || ((mathExpr *)Expr)->getOp() != DOT) {
				error.push_back("Not a valid left value");
			}
			return s;
		}
		if (Expr->n_type == VARIABLE) {
			std::string symbolName = ((variableNode *)Expr)->getId();
			Symbol argsymbol = NowTable->findSym(symbolName);
			if (argsymbol.null == 1) {
				error.push_back("Variable not exist!");
				return argsymbol;
			}
			if(argsymbol.symbolType== CONST_S) {
				error.push_back("Cannot assign const!");
				return argsymbol;
			}
			if (argsymbol.symbolType != VAR_S || argsymbol.istype==1) {
				error.push_back("Not a valid left value");
				return argsymbol;
			}
			Expr->res_type = argsymbol.valType;
			return argsymbol;
		}
	}

	Symbol SPL_Semantic::Semantic_Expr(abstractExpr * Expr) {
		if (Expr->n_type == MATHEXPR) {
			Symbol s=Semantic_Math((TOY_COMPILER::mathExpr *)Expr);
			return s;
		}
		if (Expr->n_type == VARIABLE) {
			std::string symbolName = ((variableNode *)Expr)->getId();
			Symbol argsymbol = NowTable->findSym(symbolName);
			if (argsymbol.null == 1) {
				error.push_back("Variable not exist!");
				return argsymbol;
			}
			Expr->res_type = argsymbol.valType;
			return argsymbol;
		}
	}

	Symbol SPL_Semantic::Semantic_Call(class functionCall *functionCall) {
		FunctionSymbol function = NowTable->findFunc(functionCall->getFunc_name());
		if (function.null == 1) {
			error.push_back("Function not exist");
			return Symbol();
		}
		ArgCheck(functionCall->getArgs(), function);
		return function.returnType;
	}

	int SPL_Semantic::ArgCheck(std::vector<abstractExpr *> * args, FunctionSymbol function) {
		int argindex= 0;
		if ((*args).size() != function.args.size()) {
			error.push_back("Wrong number of argv");
			return -1;
		}
		for (argindex = 0; argindex < function.args.size(); argindex++) {
			if ((*args)[argindex]->n_type == MATHEXPR) {
				Semantic_Math((mathExpr *)(*args)[argindex]);
				if ((*args)[argindex]->res_type != function.args[argindex].valType) {
					error.push_back("Wrong type of parameter");
					return -1;
				}
			}
			else {
				std::string symbolName = ((variableNode *)(*args)[argindex])->getId();
				Symbol argsymbol = NowTable->findSym(symbolName);
				if (argsymbol.valType != function.args[argindex].valType) {
					error.push_back("Wrong type of parameter");
					return -1;
				}
				if (argsymbol.valType == COMP&&argsymbol.TypeName!=function.args[argindex].TypeName) {
					error.push_back("Wrong type of parameter");
					return -1;
				}
			}
		}
		return 0;
	}


	int SPL_Semantic::Semantic(class TOY_COMPILER::abstractAST *node) {
		Symbol s=Symbol();
		switch (node->n_type) {
		case TOY_COMPILER::PROGRAM:
			this->error .push_back( "Only one program is allowed");
			return -1;
		case TOY_COMPILER::ASTType::FUNCTION:
			class TOY_COMPILER::functionNode *func = (TOY_COMPILER::functionNode *)(TOY_COMPILER::abstractStmt*)node;
			return this->Semantic_Function(func);
			break;
		case TOY_COMPILER::ASTType::STMTLIST:
			class TOY_COMPILER::stmtList *stmtList = (TOY_COMPILER::stmtList *)(TOY_COMPILER::abstractStmt*)node;
			return this->Semantic_StmtList(stmtList);
		case TOY_COMPILER::ASTType::IFSTMT:
			class TOY_COMPILER::ifStmt *ifStmt = (TOY_COMPILER::ifStmt *)(TOY_COMPILER::abstractStmt *)node;
			return this->Semantic_If(ifStmt);

		case TOY_COMPILER::ASTType::FORSTMT:
			class TOY_COMPILER::forStmt *forStmt = (TOY_COMPILER::forStmt *)(TOY_COMPILER::abstractStmt *)node;
			return this->Semantic_For(forStmt);

		case TOY_COMPILER::ASTType::WHILESTMT:
			class TOY_COMPILER::whileStmt *whileStmt = (TOY_COMPILER::whileStmt *)(TOY_COMPILER::abstractStmt *)node;
			return this->Semantic_While(whileStmt);

		case TOY_COMPILER::CASESTMT:
			class TOY_COMPILER::caseStmt *caseStmt=(class TOY_COMPILER::caseStmt *)(TOY_COMPILER::abstractStmt *)node;
			return  this->Semantic_Case(caseStmt);
		case TOY_COMPILER::GOTOSTMT:
			class TOY_COMPILER::gotoStmt *gotoStmt = (class TOY_COMPILER::gotoStmt *)(TOY_COMPILER::abstractStmt *)node;
			return  this->Semantic_Goto(gotoStmt);
		case TOY_COMPILER::ASTType::REPEATSTMT:
			class TOY_COMPILER::repeatStmt *repeatStmt = (TOY_COMPILER::repeatStmt *)(TOY_COMPILER::abstractStmt *)node;
			return this->Semantic_Repeat(repeatStmt);
		case TOY_COMPILER::ASSIGNSTMT:
			class TOY_COMPILER::assignStmt *assignStmt = (TOY_COMPILER::assignStmt *)(TOY_COMPILER::abstractStmt *)node;
			s=Semantic_Assign(assignStmt);
			if (s.null == 1)return -1;
			return 0;
		case TOY_COMPILER::EXPRESSION:
			class TOY_COMPILER::abstractExpr *abstractExpr = (TOY_COMPILER::assignStmt *)(TOY_COMPILER::abstractStmt *)node;
			s= this->Semantic_Expr(abstractExpr);
			if (s.null == 1)return -1;
			return 0;
		}
	}

	Symbol SPL_Semantic::Semantic_Array(class TOY_COMPILER::mathExpr *math) {
		Symbol left = Semantic_Expr(math->getLeftChild());
		if (left.valType != ARRAY) {
			error.push_back("Not a Array!");
			return Symbol();
		}
		if (math->getRightChild()->n_type == LITERAL) {
			Symbol right = Semantic_Literal((literal *)math->getRightChild());
			if (!CheckSameType(left,right)) {
				error.push_back("Wrong Index type!");
			}
		}
		if (math->getRightChild()->n_type == MATHEXPR) {
			Symbol right=Semantic_Math((TOY_COMPILER::mathExpr *)math->getRightChild());
			if (!CheckSameType(left, right)) {
				error.push_back("Wrong Index type!");
			}
		}
		if (math->getRightChild()->n_type == VARIABLE) {
			Symbol right = NowTable->findSym(((variableNode *)math->getRightChild())->getId());
			if (!CheckSameType(left, right)) {
				error.push_back("Wrong Index type!");
			}
		}
		return *(left.Element);
	}

	Symbol SPL_Semantic::Semantic_Literal(literal *l) {
		return Symbol(l->getType().d_type);
	}

	Symbol SPL_Semantic::Semantic_Record(class TOY_COMPILER::mathExpr *math) {
		Symbol left = Semantic_Expr(math->getLeftChild());
		if (left.valType != RECORD) {
			error.push_back("Not a Record!");
			return Symbol();
		}
		if (math->getRightChild()->n_type != VARIABLE)return Symbol();
		std::string rightName = ((variableNode *)math->getRightChild())->getId;
		return IsMember(rightName, left);
	}

	Symbol SPL_Semantic::Semantic_Math(class TOY_COMPILER::mathExpr *math) {
		if (math->getLeftChild)Semantic_Expr(math->getLeftChild);
		if (math->getRightChild)Semantic_Expr(math->getRightChild);
		TOY_COMPILER::valType leftType = VOID;
		TOY_COMPILER::valType rightType = VOID;
		switch (math->getOp) {
		case TOY_COMPILER::PLUS:
		case TOY_COMPILER::MINUS:
		case TOY_COMPILER::MUL:
			leftType = math->getLeftChild->res_type;
			rightType = math->getRightChild->res_type;
			if (leftType == TOY_COMPILER::INTEGER&&rightType == TOY_COMPILER::INTEGER)math->res_type = TOY_COMPILER::INTEGER;
			else if (leftType == TOY_COMPILER::REAL || rightType == TOY_COMPILER::REAL)math->res_type = TOY_COMPILER::REAL;
			else this->error.push_back("wrong type for math");

		case TOY_COMPILER::DIV:
			if (leftType == TOY_COMPILER::INTEGER&&rightType == TOY_COMPILER::INTEGER)math->res_type = TOY_COMPILER::REAL;
			else if (leftType == TOY_COMPILER::REAL || rightType == TOY_COMPILER::REAL)math->res_type = TOY_COMPILER::REAL;
			else this->error.push_back( "wrong type for math");
			return Symbol(math->res_type);
		case TOY_COMPILER::UNEQUAL:
		case TOY_COMPILER::GE:
		case TOY_COMPILER::GT:
		case TOY_COMPILER::LE:
		case TOY_COMPILER::LT:
		case TOY_COMPILER::EQUAL:
			leftType = math->getLeftChild->res_type;
			rightType = math->getRightChild->res_type;
			if (leftType != rightType) {
				this->error .push_back("wrong type for math");
			}
			math->res_type = TOY_COMPILER::BOOLEAN;
			return Symbol(math->res_type);
		case TOY_COMPILER::ASSIGN:
			return  Semantic_Assign((assignStmt *)math);
		case TOY_COMPILER::NOT:
			leftType = math->getLeftChild->res_type;
			if (leftType != TOY_COMPILER::BOOLEAN) {
				this->error.push_back("wrong type for math");
			}
			return 	Symbol(BOOLEAN);
		case TOY_COMPILER::MOD:
			leftType = math->getLeftChild->res_type;
			rightType = math->getRightChild->res_type;
			if (leftType != TOY_COMPILER::INTEGER || rightType != TOY_COMPILER::INTEGER) {
				this->error .push_back( "wrong type for math");
			}
			math->res_type = TOY_COMPILER::INTEGER;
			return Symbol(math->res_type);
		case TOY_COMPILER::LPLB:
			return Semantic_Array(math);
		case TOY_COMPILER::DOT:
			return Semantic_Record(math);
		default:
			return Symbol();
		}
	}
}
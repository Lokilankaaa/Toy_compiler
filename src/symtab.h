#pragma once
#include<iostream>
#include<string>
#include"SPL_Define.h"
#include"ast.h"

typedef class Symbol {	//for symbol except functions
public :
	std::string name;
	TOY_COMPILER::symbolVal symbolType;	//what is the type of the val:INTEGER,REAL,BOOLEAN,CHAR,ARRAY
	TOY_COMPILER::symbolType symbolClass;	//what is the symbol:CONST,VAR,TYPE,RANGE

	int assigned; //if 1 means has been assigned, used for const
	int scopeIndex;
	TOY_COMPILER::abstractAST * node;	//related nodes

	TOY_COMPILER::symbolVal elementType;	//if is array, the element type
	int arrayLevel;		//don't know if it will be used(?)
	int arrayLength;	//how many elements
	int beginIndex;		//for range
	int endIndex;		//for range

	std::string error;

	int null;
	Symbol(std::string name, TOY_COMPILER::symbolVal valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, TOY_COMPILER::symbolVal elementType, int beginIndex, int endIndex, int scopeIndex);	//add a array with range
	Symbol(std::string name, TOY_COMPILER::symbolVal valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, TOY_COMPILER::symbolVal elementType, int arrayLength, int scopeIndex);	//add a array with length
	Symbol(std::string name, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int beginIndex, int endIndex, int scopeIndex); //add a range
	Symbol(std::string name, TOY_COMPILER::symbolVal valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int scopeIndex);	//add a integer/real/boolean/char
	Symbol();
	int SetAssigned() {
		this->assigned = 1;	//if assigned a const
	}
	bool IsAssigned() {
		return assigned;	//To know if a const has been assigned
	}
} Symbol;

typedef class FunctionSymbol {	//only for function symbol
public:
	int null;
	std::string functionName;
	std::vector<Symbol> args;
	TOY_COMPILER::symbolVal returnType;	//if it is function, the type of return val
	SymbolTable *functionTable;	//every function give a divided table

	TOY_COMPILER::abstractAST * *node;	//related AST nodes

	FunctionSymbol();
	FunctionSymbol(std::string functionName);	//insert a function only with name, add args and result value with functions below
	int AddArgs(Symbol s) {	//add a argment
		this->args.push_back(s);
	}
	int SetRet(TOY_COMPILER::symbolVal returnType) {	//set the return type.
		this->returnType = returnType;
	}
};

typedef class SymbolList {	//a list of symbol
public:
	std::list<class Symbol> list;	//list for symbol
	std::list<class FunctionSymbol> functionList;	//list for function symbols
	int insertSym(Symbol s);	//add a symbol
	int insertFunction(FunctionSymbol function);	//add a function
	int deleteSym(std::string delname);	//maybe useless
	Symbol findSym(std::string name);	//find a sym in the list
	FunctionSymbol findFunction(std::string name);	//find a function in the list

} SymbolList;

typedef class SymbolTable {
public:
	SymbolList *table[100];	//a hash table, each is a list
	SymbolTable *parentTable;	//if it is a function/scope table, it will point to the scope defines it
	int scope;
	std::string tablename; //which function the table belong
	int insertSym(Symbol s);	//insert a symbol
	int insertFunction(FunctionSymbol fun);	//insert a function symbol
	int deleteSym(std::string delname);	//maybe useless
	~SymbolTable();
	SymbolTable(std::string tablename);	//create a new table with name
	SymbolTable(std::string tablename, SymbolTable *parent);	//create a new table with name and a parent table
	Symbol findSym(std::string name);	//find a symbol in this table and its parents table.
	std::string error; //Useless. Maybe changed in future.
private:
	int string_hash(std::string str) {	//for string hash
		unsigned long hashresult= 0;
		for (size_t i = 0; i < str.size(); i++)
			hashresult = 5 * hashresult + str[i];
		return size_t(hashresult%100);
	}
} SymbolTable;

/*in the semantic class, I have a map for <string, SymbolTable*> to save the tables for the functions*/
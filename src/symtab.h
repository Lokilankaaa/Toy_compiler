#ifndef TOY_COMPILER_SYMTAB_H
#define TOY_COMPILER_SYMTAB_H

#include <iostream>
#include <string>
#include "types.cuh"
#include "ast.h"
#include <map>
#include <list>
#include <vector>
#define SPL_LIST std::list<class Symbol>
#define SPL_TABLE std::map<std::string, class SymbolTable*>

namespace TOY_COMPILER {

    class abstractStmt;
    class abstractAST;
    class literal;
    class Record_Struct;
    class Array_Struct;
    class Name_Struct;
    class Range_Struct;
    class Type_Struct;

    class GlobalSymbol {
	public:
		std::map<std::string, class SymbolTable*> SymTable;	//string is the id of the function, use id to find table
		std::map<int, abstractStmt*> Label;
		SymbolTable*  NewSymTable(std::string tablename);	//initiate a table, the first one, without parent
		SymbolTable*  NewSymTable(std::string tablename, SymbolTable *parent);	//initiate a table, one with a parent, when find a symbol will find from it and its parent
	};


	class Symbol {	//for symbol except functions
	public:
		std::string id;	//id of the symbol
		std::string name;	//name for element
		TOY_COMPILER::valType valType;	//what is the type of the val:INTEGER,REAL,BOOLEAN,CHAR
		TOY_COMPILER::symbolType symbolType;	//what is the symbol:CONST,VAR,TYPE,RANGE

		std::vector<Symbol> memberList;

		int Label;
		std::string TypeName;

		TOY_COMPILER::expValue const_value;
		TOY_COMPILER::const_valueType const_t;

		int scopeIndex;
		TOY_COMPILER::abstractAST * node;	//related nodes

		TOY_COMPILER::passBy by;

		int arrayLevel;		//don't know if it will be used(?)
		int arrayLength;	//how many elements
		int beginIndex;		//for range
		int endIndex;		//for range
		Symbol *Index;	//the symbol of index
		Symbol *Element;	//the symbol of element


		int istype;

		std::vector<std::string> error;

		int null;
		Symbol(TOY_COMPILER::valType valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int beginIndex, int endIndex, int scopeIndex); //add a range
		Symbol(std::string id, literal* constvalue, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int scopeIndex); //add a const
		Symbol(std::string id, TOY_COMPILER::valType valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int scopeIndex);	//add a integer/real/boolean/char/complex
		Symbol(TOY_COMPILER::valType valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int scope);
		Symbol(std::string id, TOY_COMPILER::abstractAST *node, int scopeIndex);
		Symbol(TOY_COMPILER::valType valType, std::string TypeName);
		Symbol(TOY_COMPILER::valType valType);

		Symbol(std::string name);	//create a symbo
		// l only with name, for the element of name declaration
		Symbol();

		int addMem(Symbol s) {	//used to add member
			memberList.push_back(s);
		}
		int changeType(TOY_COMPILER::valType type) {	//used to change the type of the symbol
			valType = type;
		}
		int changeSymbol(TOY_COMPILER::symbolType symbol) {
			this->symbolType = symbol;
		}
		int setIsType() {
			istype = 1;
		}
		int changeId(std::string id) {
			this->id = id;
		}
		int setArray(Symbol indexSymbol, Symbol elementSymbol);
		int setIndex(Symbol indexSymbol);
		int setElement(Symbol elementSymbol);
	};

	class SymbolList {	//a list of symbol
	public:
		std::list<class Symbol> list;	//list for symbol
		std::list<class FunctionSymbol> functionList;	//list for function symbols
		int insertSym(Symbol s);	//add a symbol
		int insertFunction(FunctionSymbol function);	//add a function
		int deleteSym(std::string delname);	//maybe useless
		Symbol findSym(std::string id);	//find a sym in the list
		FunctionSymbol findFunction(std::string id);	//find a function in the list

	};

	class SymbolTable {
	public:
		SymbolList *table[100];	//a hash table, each is a list
		SymbolTable *parentTable;	//if it is a function/scope table, it will point to the scope defines it
		int scope;
		std::string tablename; //which function the table belong
		int insertSym(Symbol s);	//insert a symbol
		int insertFunction(FunctionSymbol fun);	//insert a function symbol
		int deleteSym(std::string delname);	//maybe useless
		~SymbolTable();
		SymbolTable(std::string tablename);	//create a new table with id
		SymbolTable(std::string tablename, SymbolTable *parent);	//create a new table with id and a parent table
		Symbol findSym(std::string id);	//find a symbol in this table and its parents table.
		FunctionSymbol findFunc(std::string functionId);
		std::string error; //Useless. Maybe changed in future.
	private:
		int string_hash(std::string str) {	//for string hash
			unsigned long hashresult = 0;
			for (size_t i = 0; i < str.size(); i++)
				hashresult = 5 * hashresult + str[i];
			return size_t(hashresult % 100);
		}
	};

	class FunctionSymbol {	//only for function symbol
	public:
		int null;
		std::string functionName;
		std::vector<Symbol> args;
		Symbol returnType;	//if it is function, the type of return val
		SymbolTable *functionTable;	//every function give a divided table

		TOY_COMPILER::abstractAST  *node;	//related AST nodes

		FunctionSymbol();
		FunctionSymbol(std::string functionName);	//insert a function only with id, add args and result value with functions below
		int AddArgs(Symbol s) {	//add a argment
			this->args.push_back(s);
		}
		int SetRet(Symbol returnType) {	//set the return type.
			this->returnType = returnType;
		}
	};
}
/*in the semantic class, I have a map for <string, SymbolTable*> to save the tables for the functions*/
#endif

#include "symtab.h"

Symbol::Symbol(std::string name, TOY_COMPILER::symbolVal valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, TOY_COMPILER::symbolVal elementType, int arrayLength, int scopeIndex){
	this->name = name;
	this->symbolType = valType;
	this->symbolClass = symbolType;
	this->node = node;
	this->elementType = elementType;
	this->arrayLength = arrayLength;
	this->beginIndex = 0;
	this->endIndex = beginIndex + arrayLength;
	this->scopeIndex = scopeIndex;
	this->null = 0;
}

Symbol::Symbol(std::string name, TOY_COMPILER::symbolVal valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, TOY_COMPILER::symbolVal elementType, int beginIndex, int endIndex, int scopeIndex) {
	this->name = name;
	this->symbolType = valType;
	this->symbolClass = symbolType;
	this->node = node;
	this->elementType = elementType;
	this->arrayLength = endIndex-beginIndex+1;
	this->beginIndex = beginIndex;
	this->endIndex = endIndex;
	this->scopeIndex = scopeIndex;
	this->null = 0;
}


Symbol::Symbol(std::string name, TOY_COMPILER::symbolVal valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int scopeIndex) {
	this->name = name;
	this->symbolType = valType;
	this->symbolClass = symbolType;
	this->node = node;
	this->scopeIndex = scopeIndex;
	this->null = 0;
}

Symbol::Symbol(std::string name, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int beginIndex, int endIndex, int scopeIndex) {
	this->name = name;
	this->symbolClass = symbolType;
	this->node = node;
	this->beginIndex = beginIndex;
	this->endIndex = endIndex;
	this->scopeIndex = scopeIndex;
	this->null = 0;
}



Symbol::Symbol() {
	this->null = 1;
}


FunctionSymbol::FunctionSymbol(std::string functionName) {
	this->functionName = functionName;
}


FunctionSymbol::FunctionSymbol() {
	this->null = 1;
}

int SymbolList::insertSym(Symbol s) {
	this->list.push_front(s);
	return 0;
}

int SymbolList::deleteSym(std::string delname) {
	std::list<class Symbol>::iterator s = this->list.begin();
	while (s != this->list.end()) {
		if (s->name == delname) {
			this->list.erase(s);
			return 0;
		}
		s++;
	}
	return 1;
}
int SymbolList::insertFunction(FunctionSymbol function) {
	std::list<class FunctionSymbol>::iterator fun = this->functionList.begin;
	std::string name = function.functionName;
	while (fun != this->functionList.end) {
		if ((*fun).functionName == name)return -1;
		fun++;
	}
	this->functionList.push_front(function);
}

FunctionSymbol SymbolList::findFunction(std::string name) {
	std::list<class FunctionSymbol>::iterator fun = this->functionList.begin;
	while (fun != this->functionList.end) {
		if ((*fun).functionName == name)return *fun;
		fun++;
	}
	return FunctionSymbol();
}

Symbol SymbolList::findSym(std::string name) {
	std::list<class Symbol>::iterator sym = this->list.begin();
	while (sym != this->list.end()) {
		if (sym->name == name)return *sym;
	}
	return Symbol();
}
	
int SymbolTable::insertSym(Symbol s){	
	int hashresult = SymbolTable::string_hash(s.name);
	SymbolList *list = this->table[hashresult];
	if (list == NULL)list = new SymbolList();
	list->insertSym(s);
	return 0;
}

int SymbolTable::insertFunction(FunctionSymbol fun) {
	int hashresult = SymbolTable::string_hash(fun.functionName);
	SymbolList *list = this->table[hashresult];
	if (list == NULL)list = new SymbolList();
	list->insertFunction(fun);
	return 0;
}

int SymbolTable::deleteSym(std::string delname) {
	int hashresult = SymbolTable::string_hash(delname);
	SymbolList *list = this->table[hashresult];
	if (list == NULL)list = new SymbolList();
	list->deleteSym(delname);
	return 0;
}


SymbolTable::~SymbolTable() {
	SymbolTable *partab = this->parentTable;
	for (int i = 0; i < 100; i++)if (this->table[i] != NULL)delete this->table[i];
}

SymbolTable::SymbolTable(std::string tablename) {
	for (int i = 0; i < 100; i++) {
		this->table[i] = NULL;
	}
	this->scope = 0;
	this->parentTable = NULL;
	this->tablename = tablename;
}

SymbolTable::SymbolTable(std::string tablename, SymbolTable *parent) {
	for (int i = 0; i < 100; i++) {
		this->table[i] = NULL;
	}
	this->scope = parent->scope + 1;
	this->parentTable = parent;
	this->scope = parent->scope+1;
}

Symbol SymbolTable::findSym(std::string name) {
	SymbolTable *Symtable = this;
	Symbol SymbolResult=Symbol();
	int index = this->string_hash(name);
	while (Symtable != NULL) {
		SymbolResult=Symtable->table[index]->findSym(name);
		if (!SymbolResult.null)break;
		Symtable = Symtable->parentTable;
	}
	return SymbolResult;
}
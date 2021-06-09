#include "symtab.h"

namespace TOY_COMPILER {

	SymbolTable* GlobalSymbol::NewSymTable(std::string tablename) {
		SymbolTable *NewSymTable = new SymbolTable(tablename);
		this->SymTable.insert(std::map<std::string, class SymbolTable*>::value_type(tablename, NewSymTable));
	}

	SymbolTable* GlobalSymbol::NewSymTable(std::string tablename, SymbolTable *parent) {
		SymbolTable *NewSymTable = new SymbolTable(tablename);
		this->SymTable.insert(std::map<std::string, class SymbolTable*>::value_type(tablename, NewSymTable));
	}


	Symbol::Symbol(std::string id, TOY_COMPILER::valType valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int scopeIndex) {
		this->id = id;
		this->valType = valType;
		this->symbolType = symbolType;
		this->node = node;
		this->scopeIndex = scopeIndex;
		this->null = 0;
		this->istype = 0;
	}

	Symbol::Symbol(std::string id, literal* constvalue, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int scopeIndex) {
		this->id = id;
		this->const_value = constvalue->getValue;
		this->const_t = constvalue->getType;
		this->symbolType = symbolType;
		this->node = node;
		this->scopeIndex = scopeIndex;
		this->null = 0;
		this->istype = 0;
	}

	Symbol::Symbol(TOY_COMPILER::valType valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int beginIndex, int endIndex, int scopeIndex) {
		this->id = id;
		this->valType = valType;
		this->symbolType = symbolType;
		this->node = node;
		this->beginIndex = beginIndex;
		this->endIndex = endIndex;
		this->scopeIndex = scopeIndex;
		this->null = 0;
		this->istype = 0;
	}

	Symbol::Symbol(TOY_COMPILER::valType valType, TOY_COMPILER::symbolType symbolType, TOY_COMPILER::abstractAST *node, int scope) {
		this->valType = valType;
		this->symbolType = symbolType;
		this->node = node;
		this->scopeIndex = scopeIndex;
		this->null = 0;
		this->istype = 0;
	}

	Symbol::Symbol(std::string id, TOY_COMPILER::abstractAST *node, int scopeIndex) {
		this->id = id;
		this->node = node;
		this->scopeIndex = scopeIndex;
		this->null = 0;
		this->istype = 0;
	}

	Symbol::Symbol(std::string name) {
		this->name = name;
		this->symbolType = TOY_COMPILER::ELEMENT_S;
		this->null = 0;
		this->istype = 0;
	}

	Symbol::Symbol(TOY_COMPILER::valType valType, std::string TypeName) {
		this->valType = valType;
		this->TypeName = TypeName;
		this->istype = 0;
	}

	Symbol::Symbol(TOY_COMPILER::valType valType) {
		this->valType = valType;
		this->istype = 0;
	}

	Symbol::Symbol() {
		this->null = 1;
		this->istype = 0;
		this->valType = ERROR;
	}

	int Symbol::setArray(Symbol indexSymbol, Symbol elementSymbol) {
		if (indexSymbol.symbolType != RANGE_S || indexSymbol.symbolType != NAME_S) {
			setIndex(elementSymbol);
			setElement(indexSymbol);
		}
		else {
			setIndex(indexSymbol);
			setElement(elementSymbol);
		}
	}

	int Symbol::setIndex(Symbol indexSymbol) {
		if (indexSymbol.symbolType == RANGE_S) {
			this->Index = new Symbol(indexSymbol);
			this->beginIndex = indexSymbol.beginIndex;
			this->endIndex = indexSymbol.endIndex;
			this->arrayLength = indexSymbol.arrayLength;
			return 0;
		}
		if(indexSymbol.symbolType==NAME_S){
			this->Index = new Symbol(indexSymbol);
			this->arrayLength = this->Index->memberList.size();
			return 0;
		}
	}

	int Symbol::setElement(Symbol elementSymbol) {
			this->Element = new Symbol(elementSymbol);
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
			if (s->id == delname) {
				this->list.erase(s);
				return 0;
			}
			s++;
		}
		return 1;
	}
	int SymbolList::insertFunction(FunctionSymbol function) {
		std::list<class FunctionSymbol>::iterator fun = this->functionList.begin();
		std::string id = function.functionName;
		while (fun != this->functionList.end()) {
			if ((*fun).functionName == id)return -1;
			fun++;
		}
		this->functionList.push_front(function);
	}

	FunctionSymbol SymbolList::findFunction(std::string id) {
		std::list<class FunctionSymbol>::iterator fun = this->functionList.begin();
		while (fun != this->functionList.end()) {
			if ((*fun).functionName == id)return *fun;
			fun++;
		}
		return FunctionSymbol();
	}

	Symbol SymbolList::findSym(std::string id) {
		std::list<class Symbol>::iterator sym = this->list.begin();
		while (sym != this->list.end()) {
			if (sym->id == id)return *sym;
		}
		return Symbol();
	}

	int SymbolTable::insertSym(Symbol s) {
		int hashresult = SymbolTable::string_hash(s.id);
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
		this->scope = parent->scope + 1;
	}

	Symbol SymbolTable::findSym(std::string id) {
		SymbolTable *Symtable = this;
		Symbol SymbolResult = Symbol();
		int index = this->string_hash(id);
		while (Symtable != NULL) {
			SymbolResult = Symtable->table[index]->findSym(id);
			if (!SymbolResult.null)break;
			Symtable = Symtable->parentTable;
		}
		return SymbolResult;
	}

	FunctionSymbol SymbolTable::findFunc(std::string functionId) {
		SymbolTable *Symtable = this;
		FunctionSymbol SymbolResult = FunctionSymbol();
		int index = this->string_hash(functionId);
		while (Symtable != NULL) {
			SymbolResult = Symtable->table[index]->findFunction(functionId);
			if (!SymbolResult.null)break;
			Symtable = Symtable->parentTable;
		}
		return SymbolResult;
	}
}
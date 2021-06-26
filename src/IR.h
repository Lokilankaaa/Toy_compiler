#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "ast.h"

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> TheBuilder(TheContext);

namespace TOY_COMPILER {

    class Record_Struct;
    class Array_Struct;
    class Name_Struct;
    class Range_Struct;
    class Type_Struct;

	class Function {
	public:	//maps for every function,const every variable will record in typeMap, except function
		// functionMap used to record return value
		std::map<std::string, Record_Struct*> recordMap;
		std::map<std::string, Array_Struct *> arrayMap;
		std::map<std::string, Name_Struct*> nameMap;
		std::map<std::string, Range_Struct*> rangeMap;
		std::map<std::string, Type_Struct*> typeMap;
		std::map<std::string, Type_Struct*> functionMap;

		llvm::Function *Func;
		Function(llvm::Function *Func){
			this->Func = Func;
		}
	};

	class SPLStruct {
	};

    class Type_Struct:public SPLStruct {	//a general type used in iR
    public:
        std::string name;	//name of a variable
        valType type;	//type of it
        bool istype;	//if it is a variable of a type
        bool isconst;	//if it is a const, the value is its value, the const will not save in the llvm function
        SPLStruct *Struct;	//if it is complicated(array, record, name), the struct of them
        llvm::Type *llvm;	//the type information, generator when declaration, can be used
        expValue value;	//the value for const
        llvm::Value *llvmValue;	//the llvm value, used to pass some llvm value *
        //not record the variable value, you need to find from llvm function

        Type_Struct() {
            this->type = ERROR;
            this->isconst = 0;
            this->istype = 0;
        }

        Type_Struct(valType val) {
            this->type = val;
            this->isconst = 0;
            this->istype = 0;
        }

        Type_Struct(llvm::Value *value) {
            this->llvmValue = value;
            this->isconst = 0;
            this->istype = 0;
        }

        operator llvm::Value*() {
            return this->llvmValue;
        }
    };

    class Array_Struct: public SPLStruct {
    public:
        int begin;	//begin of the index
        int end;	//end of index
        int size;	//size of index
        iType arrayType;	//the index is name or range, range can generate by the up three attribute
        Type_Struct indexType;	//if index is name, find the name type in here
        Type_Struct elementType;	//the type of element
    };

	class Range_Struct: public SPLStruct {
	public:
		int begin;
		int end;
		int size;
	};

	class Record_Struct:public SPLStruct {	//record the element of the record
	public:
		std::vector<Type_Struct> elements;
	};

	class Name_Struct:public SPLStruct {	//rocord the names of the enum
	public:
		std::vector<std::string> elements;
	};

	class IR
	{
	public:
		std::unique_ptr<llvm::Module> TheModule;
		unsigned int TheAddrSpace;
		std::vector<Function> funcStack;
		llvm::BasicBlock* labelBlock[10000];

		llvm::Function *printf, *scanf;
		std::vector<std::string> error;
		llvm::Function *mainFunction;

		IR()
		{
			TheModule = std::unique_ptr<llvm::Module>(new llvm::Module("main", TheContext));
			TheAddrSpace = TheModule->getDataLayout().getAllocaAddrSpace();
		}

        void generate(TOY_COMPILER::rootProgram *root)
        {
            std::cout << "[INFO]" << "IR generation begin..." << std::endl;
            root->init(*this);
//            root->codeGen(*this);
            std::cout << "[INFO]" << "IR generation finished." << std::endl;

            //    llvm::legacy::PassManager pm;
            //    pm.add(createPrintModulePass(llvm::outs()));
            //    pm.run(*TheModule);
            // TheModule->dump();
            TheModule->print(llvm::errs(), nullptr);
        }

        llvm::GenericValue run()
        {
            std::cout << "[INFO]" << "IR running begin..." << std::endl;
            llvm::ExecutionEngine* ee = genExeEngine();
            std::vector<llvm::GenericValue> args;
            llvm::GenericValue res = ee->runFunction(mainFunction, args);
            std::cout << "[INFO]" << "IR running finished." << std::endl;
            return res;
        }

        llvm::ExecutionEngine* genExeEngine()
        {
            std::string errStr;
            auto RTDyldMM = std::unique_ptr<llvm::SectionMemoryManager>(new llvm::SectionMemoryManager());
            llvm::ExecutionEngine* ee = llvm::EngineBuilder(std::move(TheModule))
                    //        .setEngineKind(llvm::EngineKind::Interpreter)
                    .setEngineKind(llvm::EngineKind::JIT)
                    .setErrorStr(&errStr)
                    .setVerifyModules(true)
                    .setMCJITMemoryManager(move(RTDyldMM))
                    .setOptLevel(llvm::CodeGenOpt::Default)
                    .create();
            if (!ee)
            {
                throw std::logic_error("[ERROR]Create Engine Error: " + errStr);
            }
            ee->addModule(std::move(TheModule));
            ee->finalizeObject();
            return ee;
        }


		int InsertArray(std::string &name, Array_Struct* array) {	//to insert a array into the map
			funcStack.back().arrayMap.insert(std::map<std::string, Array_Struct*>::value_type(name, array));
			return 0;
		}

		int InsertRecord(std::string &name, Record_Struct* record) { //to insert a record into the map
			funcStack.back().recordMap.insert(std::map<std::string, Record_Struct*>::value_type(name, record));
			return 0;
		}

		int InsertName(std::string &name, Name_Struct* namelist) { //to insert a name into the map
			funcStack.back().nameMap.insert(std::map<std::string, Name_Struct*>::value_type(name, namelist));
			return 0;
		}

		int InsertType(std::string &name, Type_Struct* type) { //to insert a type into the map
			Type_Struct *check = checkType(name);
			if (check != NULL) {
				std::cout << "Deplicate Varaible:" << name;
				return -1;
			}
			funcStack.back().typeMap.insert(std::map<std::string, Type_Struct*>::value_type(name, type));
			return 0;
		}

		int InsertFunction(std::string &name, Type_Struct* type) { //to insert a function return into the map
			Type_Struct *check = checkType(name);
			if (check != NULL) {
				std::cout << "Deplicate Varaible:" << name;
				return -1;
			}
			funcStack.back().functionMap.insert(std::map<std::string, Type_Struct*>::value_type(name, type));
			return 0;
		}

		Array_Struct* findArray(const std::string &name) {	//find a array in all functions
			for (auto it = funcStack.rbegin(); it != funcStack.rend(); it++)
			{
				auto result = it->arrayMap.find(name);
				if (result != it->arrayMap.end())
				{
					std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
					return result->second;
				}
				else
				{
					std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				}
			}
			return NULL;
		}


		Range_Struct* findRange(std::string &name) { //find a range in all functions
			for (auto it = funcStack.rbegin(); it != funcStack.rend(); it++)
			{
				auto result = it->rangeMap.find(name);
				if (result != it->rangeMap.end())
				{
					std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
					return result->second;
				}
				else
				{
					std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				}
			}
			return NULL;
		}

		Record_Struct* findRecord(const std::string &name) { //find a record in all functions
			for (auto it = funcStack.rbegin(); it != funcStack.rend(); it++)
			{
				auto result = it->recordMap.find(name);
				if (result != it->recordMap.end())
				{
					std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
					return result->second;
				}
				else
				{
					std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				}
			}
			return NULL;
		}

		Name_Struct* findName(const std::string &name) { //find a name in all functions
			for (auto it = funcStack.rbegin(); it != funcStack.rend(); it++)
			{
				auto result = it->nameMap.find(name);
				if (result != it->nameMap.end())
				{
					std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
					return result->second;
				}
				else
				{
					std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				}
			}
			return NULL;
		}

		Type_Struct* findConst(const std::string &name) { //find a const in all functions
			auto it = funcStack.rbegin();
			auto result = it->typeMap.find(name);
			if (result != it->typeMap.end())
			{
				std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				return result->second;
			}
			else
			{
				std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
			}
			return NULL;
		}

		Type_Struct* checkType(const std::string &name) { //check if there is a variable with same name in this function
			auto it = funcStack.rbegin();
			auto result = it->typeMap.find(name);
			if (result != it->typeMap.end())
			{
				std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				return result->second;
			}
			else
			{
				std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
			}
			return NULL;
		}

		Type_Struct* findType(const std::string &name, std::vector<Function>::reverse_iterator it) {
			//get the Type in the given function
			auto result = it->typeMap.find(name);
			if (result != it->typeMap.end())
			{
				std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				return result->second;
			}
			else
			{
				std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
			}
			return NULL;
		}

		Type_Struct* findFunction(const std::string &name) {
			//get the function return from function map
			for (auto it = funcStack.rbegin(); it != funcStack.rend(); it++)
			{
				auto result = it->functionMap.find(name);
				if (result != it->functionMap.end())
				{
					std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
					return result->second;
				}
				else
				{
					std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				}
			}
			return NULL;
		}


		Type_Struct* findType(const std::string &name) {
			//get the type information from function map

			for (auto it = funcStack.rbegin(); it != funcStack.rend(); it++)
			{
				auto result = it->typeMap.find(name);
				if (result != it->typeMap.end())
				{
					std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
					return result->second;
				}
				else
				{
					std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				}
			}
			return NULL;
		}

		llvm::Value* findValue(const std::string & name)	//get the llvm value from llvm function
		{
			llvm::Value * result = nullptr;
			for (auto it = funcStack.rbegin(); it != funcStack.rend(); it++)
			{
				Type_Struct *type = findType(name,it);
				if (type!=NULL)
				{
					if (type->isconst) {
						switch (type->type)
						{
						case INTEGER: return TheBuilder.getInt32(type->value.int_value);
						case REAL: return llvm::ConstantFP::get(TheBuilder.getDoubleTy(), type->value.real_value);
						case CHAR: return TheBuilder.getInt8(type->value.char_value);
						case BOOLEAN: return TheBuilder.getInt1(type->value.bool_value);
						}
					}else result = it->Func->getValueSymbolTable()->lookup(name);
					std::cout << "Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
					return result;
				}
				else
				{
					std::cout << "Not Find " << name << " in " << std::string(it->Func->getName()) << std::endl;
				}
			}
			return result;
		}

		llvm::Function* getCurFunction()
		{
			return funcStack.back().Func;
		}

		void pushFunction(llvm::Function* func)
		{
			funcStack.push_back(Function(func));
		}

		void popFunction()
		{
			funcStack.pop_back();
		}

		llvm::Function* createPrintf()
		{
			std::vector<llvm::Type*> arg_types;
			arg_types.push_back(TheBuilder.getInt8PtrTy());
			auto printf_type = llvm::FunctionType::get(TheBuilder.getInt32Ty(), llvm::makeArrayRef(arg_types), true);
			auto func = llvm::Function::Create(printf_type, llvm::Function::ExternalLinkage, llvm::Twine("printf"), TheModule.get());
			func->setCallingConv(llvm::CallingConv::C);
			return func;
		}

		llvm::Function* createScanf()
		{
			auto scanf_type = llvm::FunctionType::get(TheBuilder.getInt32Ty(), true);
			auto func = llvm::Function::Create(scanf_type, llvm::Function::ExternalLinkage, llvm::Twine("scanf"), TheModule.get());
			func->setCallingConv(llvm::CallingConv::C);
			return func;
		}

	};


}
#endif
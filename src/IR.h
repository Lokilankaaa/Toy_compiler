#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "ast.h"
#include "symtab.h"

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Target/TargetMachine.h>
	//#include <llvm/Support/Debug.h>

namespace TOY_COMPILER {

    class rootProgram;

    static llvm::LLVMContext TheContext;
    static llvm::IRBuilder<> TheBuilder(TheContext);

	class Function {
	public:
		std::map<std::string, Record_Struct*> recordMap;
		std::map<std::string, Array_Struct *> arrayMap;
		std::map<std::string, Name_Struct*> nameMap;
		std::map<std::string, Range_Struct*> rangeMap;
		std::map<std::string, Type_Struct*> typeMap;
		std::map<std::string, Type_Struct *>functionMap;

		llvm::Function *Func;
		Function(llvm::Function *Func){
			this->Func = Func;
		}
	};

	class SPLStruct {
	};

	class Array_Struct: public SPLStruct {
	public:
		int begin;
		int end;
		int size;
		iType arrayType;
		Type_Struct indexType;
		Type_Struct elementType;
	};

	class Range_Struct: public SPLStruct {
	public:
		int begin;
		int end;
		int size;
	};

	class Type_Struct:public SPLStruct {
	public:
		std::string name;
		valType type;
		bool istype;
		bool isconst;
		SPLStruct *Struct;
		llvm::Type *llvm;
		expValue value;
		llvm::Value *llvmValue;

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
	};

	class Record_Struct:public SPLStruct {
	public:
		std::vector<Type_Struct> elements;
	};

	class Name_Struct:public SPLStruct {
	public:
		std::vector<std::string> elements;
	};

	class IR
	{
	public:
		std::unique_ptr<llvm::Module> TheModule;
		unsigned int TheAddrSpace;
		llvm::Function *mainFunction;

		llvm::BasicBlock* labelBlock[10000];

		llvm::Function *printf, *scanf;
		std::vector<std::string> error;
		std::vector<Function> funcStack;


		IR()
		{
			TheModule = std::unique_ptr<llvm::Module>(new llvm::Module("main", TheContext));
			TheAddrSpace = TheModule->getDataLayout().getAllocaAddrSpace();
		}

		void generate(rootProgram* astRoot);
		llvm::GenericValue run();
		llvm::ExecutionEngine* genExeEngine();

		int InsertArray(std::string &name, Array_Struct* array) {
			funcStack.back().arrayMap.insert(std::map<std::string, Array_Struct*>::value_type(name, array));
			return 0;
		}

		int InsertRecord(std::string &name, Record_Struct* record) {
			funcStack.back().recordMap.insert(std::map<std::string, Record_Struct*>::value_type(name, record));
			return 0;
		}

		int InsertName(std::string &name, Name_Struct* namelist) {
			funcStack.back().nameMap.insert(std::map<std::string, Name_Struct*>::value_type(name, namelist));
			return 0;
		}

		int InsertType(std::string &name, Type_Struct* type) {
			Type_Struct *check = checkType(name);
			if (check != NULL) {
				std::cout << "Deplicate Varaible:" << name;
				return -1;
			}
			funcStack.back().typeMap.insert(std::map<std::string, Type_Struct*>::value_type(name, type));
			return 0;
		}

		int InsertFunction(std::string &name, Type_Struct* type) {
			Type_Struct *check = checkType(name);
			if (check != NULL) {
				std::cout << "Deplicate Varaible:" << name;
				return -1;
			}
			funcStack.back().functionMap.insert(std::map<std::string, Type_Struct*>::value_type(name, type));
			return 0;
		}

		Array_Struct* findArray(const std::string &name) {
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


		Range_Struct* findRange(std::string &name) {
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

		Record_Struct* findRecord(const std::string &name) {
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

		Name_Struct* findName(const std::string &name) {
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

		Type_Struct* findConst(const std::string &name) {
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

		Type_Struct* checkType(const std::string &name) {
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

		llvm::Value* findValue(const std::string & name)
		{
			llvm::Value * result = nullptr;
			for (auto it = funcStack.rbegin(); it != funcStack.rend(); it++)
			{
				Type_Struct *type = findType(name,it);
				if (type!=NULL)
				{
					if (type->isconst) {
						switch (((Const_Struct*)type->Struct)->type)
						{
						case INTEGER: return TheBuilder.getInt32(((Const_Struct*)type->Struct)->value.int_value);
						case REAL: return llvm::ConstantFP::get(TheBuilder.getDoubleTy(), ((Const_Struct*)type->Struct)->value.real_value);
						case CHAR: return TheBuilder.getInt8(((Const_Struct*)type->Struct)->value.char_value);
						case BOOLEAN: return TheBuilder.getInt1(((Const_Struct*)type->Struct)->value.bool_value);
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

    void IR::generate(rootProgram *root)
    {
        std::cout << "[INFO]" << "IR generation begin..." << std::endl;
        root->codeGen(*this);
        std::cout << "[INFO]" << "IR generation finished." << std::endl;

        //    llvm::legacy::PassManager pm;
        //    pm.add(createPrintModulePass(llvm::outs()));
        //    pm.run(*TheModule);
        // TheModule->dump();
        TheModule->print(llvm::errs(), nullptr);
    }

    llvm::GenericValue IR::run()
    {
        std::cout << "[INFO]" << "IR running begin..." << std::endl;
        llvm::ExecutionEngine* ee = genExeEngine();
        std::vector<llvm::GenericValue> args;
        llvm::GenericValue res = ee->runFunction(mainFunction, args);
        std::cout << "[INFO]" << "IR running finished." << std::endl;
        return res;
    }

    llvm::ExecutionEngine* IR::genExeEngine()
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
}
#endif
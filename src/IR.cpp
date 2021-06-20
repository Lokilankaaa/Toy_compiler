#include "ast.h"
#include "IR.h"
#include<string>

extern std::map<int, TOY_COMPILER::abstractStmt*> Label;

namespace TOY_COMPILER {
	
	template <typename T>
	void printT(T* vt)
	{
		std::string str;
		llvm::raw_string_ostream stream(str);
		vt->print(stream);
		std::cout << str << std::endl;
	}

    std::string to_string(int num) {
        std::string res = "";
        while (num != 0) {
            res =(char)(num%10 + 0x30)+res;
            num = num / 10;
        }
        return res;
    }

	llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, llvm::StringRef VarName, llvm::Type* type)
	{
		llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
		return TmpB.CreateAlloca(type, nullptr, VarName);
	}

	llvm::Type* toLLVMPtrType(const valType & type)
	{
		switch (type)
		{
		case INTEGER: return llvm::Type::getInt32PtrTy(TheContext);
		case REAL: return llvm::Type::getDoublePtrTy(TheContext);
		case CHAR: return llvm::Type::getInt8PtrTy(TheContext);
		case BOOLEAN: return llvm::Type::getInt1PtrTy(TheContext);
		}
	}

	int GetValue(Type_Struct ts) {
		switch (ts.type)
		{
		case INTEGER: return (int)ts.value.int_value;
		case REAL: return (int)ts.value.real_value;
		case CHAR: return (int)ts.value.char_value;
		case BOOLEAN: return (int)ts.value.bool_value;
		}
	}

	Type_Struct literal::codeGen(IR & generator)
	{
		Type_Struct ts;
		switch (this->getType()->d_type)
		{
		case INTEGER:ts.type = INTEGER;
			ts.llvmValue=TheBuilder.getInt32(this->getValue()->int_value);
			return ts;
		case REAL: ts.type = REAL;
			ts.llvmValue= llvm::ConstantFP::get(TheBuilder.getDoubleTy(), this->getValue()->real_value);
			return ts;
		case CHAR: ts.type = CHAR;
			ts.llvmValue= TheBuilder.getInt8(this->getValue()->char_value);
			return ts;
		case BOOLEAN: ts.type = BOOLEAN;
			ts.llvmValue= TheBuilder.getInt1(this->getValue()->bool_value);
			return ts;
		}
	}



	Type_Struct BinaryOp(llvm::Value* lValue, TOY_COMPILER::opType op, llvm::Value * rValue)
	{
		Type_Struct resType;
		bool flag = lValue->getType()->isDoubleTy() || rValue->getType()->isDoubleTy();
		resType.type = (flag)? REAL:INTEGER;
		switch (op)
		{
		case PLUS: resType.llvmValue = flag ? TheBuilder.CreateFAdd(lValue, rValue, "addtmpf") : TheBuilder.CreateAdd(lValue, rValue, "addtmpi");
			break;
		case MINUS: resType.llvmValue = flag ? TheBuilder.CreateFSub(lValue, rValue, "subtmpf") : TheBuilder.CreateSub(lValue, rValue, "subtmpi");
			break;
		case MUL: resType.llvmValue = flag ? TheBuilder.CreateFMul(lValue, rValue, "multmpf") : TheBuilder.CreateMul(lValue, rValue, "multmpi");
			break;
		case DIV: resType.llvmValue = TheBuilder.CreateSDiv(lValue, rValue, "tmpDiv");
			break;
		case GE: resType.type = BOOLEAN;
			resType.llvmValue = TheBuilder.CreateICmpSGE(lValue, rValue, "tmpSGE");
			break;
		case GT: resType.type = BOOLEAN;
			resType.llvmValue = TheBuilder.CreateICmpSGT(lValue, rValue, "tmpSGT");
			break;
		case LT: resType.type = BOOLEAN;
			resType.llvmValue = TheBuilder.CreateICmpSLT(lValue, rValue, "tmpSLT");
			break;
		case LE: resType.type = BOOLEAN;
			resType.llvmValue = TheBuilder.CreateICmpSLE(lValue, rValue, "tmpSLE");
			break;
		case EQUAL: resType.type = BOOLEAN;
			resType.llvmValue = TheBuilder.CreateICmpEQ(lValue, rValue, "tmpEQ");
			break;
		case UNEQUAL: resType.type = BOOLEAN;
			resType.llvmValue = TheBuilder.CreateICmpNE(lValue, rValue, "tmpNE");
			break;
		case OR: resType.llvmValue = TheBuilder.CreateOr(lValue, rValue, "tmpOR");
			break;
		case MOD: resType.type = INTEGER;
			resType.llvmValue = TheBuilder.CreateSRem(lValue, rValue, "tmpSREM");
			break;
		case AND: resType.llvmValue = TheBuilder.CreateAnd(lValue, rValue, "tmpAND");
			break;
		}
		return resType;
	}

	
	Type_Struct simpleDecl::codeGen(IR & generator) {
		Type_Struct ts;
		switch (this->getval_type())
		{
		case INTEGER: ts.type = INTEGER;
			ts.llvm=llvm::Type::getInt32Ty(TheContext);
			return ts;
		case REAL: ts.type = REAL;
			ts.llvm=llvm::Type::getDoubleTy(TheContext);
			return ts;
		case CHAR: ts.type = CHAR;
			ts.llvm=llvm::Type::getInt8Ty(TheContext);
			return ts;
		case BOOLEAN:ts.type = BOOLEAN;
			llvm::Type::getInt1Ty(TheContext);
			return ts;
		}
	}

	Type_Struct variableNode::codeGen(IR & generator){
		Type_Struct ts = *generator.findType(this->getId());
		if (ts.isconst == 1) {
			switch (ts.type)
			{
			case INTEGER:ts.type = INTEGER;
				ts.llvmValue = TheBuilder.getInt32(ts.value.int_value);
				return ts;
			case REAL: ts.type = REAL;
				ts.llvmValue = llvm::ConstantFP::get(TheBuilder.getDoubleTy(), ts.value.real_value);
				return ts;
			case CHAR: ts.type = CHAR;
				ts.llvmValue = TheBuilder.getInt8(ts.value.char_value);
				return ts;
			case BOOLEAN: ts.type = BOOLEAN;
				ts.llvmValue = TheBuilder.getInt1(ts.value.bool_value);
				return ts;
			}
		}
		else ts.llvmValue= TheBuilder.CreateLoad(generator.findValue(this->getId()), this->getId());
		return ts;
	}



	Type_Struct constNode::codeGen(IR & generator) {
		std::string name = this->getId();
		Type_Struct *ts = new Type_Struct;
		ts->isconst = 1;
		ts->Struct = NULL;
		ts->type = this->getType()->getType()->d_type;
		ts->value= *this->getType()->getValue();
		generator.InsertType(name, ts);
		return *ts;
	}

	Type_Struct constDecl::codeGen(IR & generator) {
		for (auto & constNode : *this->getDecls())constNode->codeGen(generator);
		return Type_Struct(VOID);
	}

	Type_Struct recordDecl::codeGen(IR & generator) {
		Type_Struct ts;
		Record_Struct *rs = new Record_Struct;
		llvm::StructType* structType = llvm::StructType::create(TheContext);
		std::vector<llvm::Type*> elements;
		for (auto & field : this->getFields()) {
			Type_Struct etype = field->codeGen(generator);
			for (auto & name : *field->getNamelist()) {
				etype.name = name;
				rs->elements.push_back(etype);
				elements.push_back(etype.llvm);
			}
		}
		structType->setBody(elements);
		ts.llvm = structType;
		ts.Struct = rs;
		ts.type = RECORD;
		return ts;
	}

	Type_Struct field::codeGen(IR & generator) {
		return this->getType()->codeGen(generator);
	}


	Type_Struct namesDecl::codeGen(IR & generator) {
		if (this->getIsNamelist()) {
			Type_Struct ts;
			ts.type = NAME;
			Name_Struct* ns = new Name_Struct();
			for (auto & name : this->getNames()) {
				ns->elements.push_back(name);
			}
			ts.Struct = ns;
			return ts;
		}
		else {
			std::string name = this->getNames()[0];
			return *(generator.findType(name));
		}
	}


	Type_Struct rangeDecl::codeGen(IR & generator) {
		Range_Struct *rs = new Range_Struct;
		Type_Struct ts;
		ts.Struct = rs;
		ts.type = RANGE;
		if (this->con_l == NULL) {
			int left_v, right_v;
			Type_Struct *left = generator.findConst(this->getId_l());
			Type_Struct *right = generator.findConst(this->getId_r());
			switch (left->type)
			{
			case INTEGER:left_v = left->value.int_value;
			case CHAR: left_v = left->value.char_value;
			case BOOLEAN: left_v = left->value.bool_value;
			}
			switch (right->type)
			{
			case INTEGER:right_v = right->value.int_value;
			case CHAR: right_v = right->value.char_value;
			case BOOLEAN: right_v = right->value.bool_value;
			}
			rs->begin = left_v;
			rs->end = right_v;
			rs->size = right_v - left_v+1;	
		}
		else {
			int left_v, right_v;
			switch (this->getLeftRange()->getType()->d_type)
			{
			case INTEGER:left_v=this->getLeftRange()->getValue()->int_value;
			case CHAR: left_v = this->getLeftRange()->getValue()->char_value;
			case BOOLEAN: left_v = this->getLeftRange()->getValue()->bool_value;
			}
			switch (this->getRightRange()->getType()->d_type)
			{
			case INTEGER:right_v = this->getRightRange()->getValue()->int_value;
			case CHAR: right_v = this->getRightRange()->getValue()->char_value;
			case BOOLEAN: right_v = this->getRightRange()->getValue()->bool_value;
			}
			rs->begin =(this->getLeftSign())? -1*left_v:left_v;
			rs->end = (this->getRightSign()) ? -1 * right_v : right_v;			
			rs->size = right_v - left_v + 1;
		}
		return ts;
	}

	Type_Struct arrayDecl::codeGen(IR & generator) {
		Type_Struct itype = this->getSimpleType()->codeGen(generator);
		Type_Struct ts;
		Type_Struct etype = this->getTypeDecl()->codeGen(generator);
		Array_Struct *as = new Array_Struct();
		ts.Struct = as;
		ts.type = ARRAY;
		switch (itype.type)
		{
		case NAME:
			as->indexType = itype;
			as->arrayType = NAME_AS;
			as->size = ((Name_Struct*)itype.Struct)->elements.size();
			as->elementType = etype;
			break;
		case RANGEDECL:
			as->indexType = itype;
			as->arrayType = RANGE_AS;
			as->begin = ((Range_Struct *)itype.Struct)->begin;
			as->end = ((Range_Struct *)itype.Struct)->end;
			as->size = ((Range_Struct *)itype.Struct)->size;
			as->elementType = etype;
			break;
		case SIMPLEDCEL:
			switch (etype.type)
			{
			case NAME:
				as->indexType = etype;
				as->arrayType = NAME_AS;
				as->size = ((Name_Struct*)etype.Struct)->elements.size();
				as->elementType = itype;
				break;
			case RANGEDECL:
				as->indexType = itype;
				as->arrayType = RANGE_AS;
				as->begin = ((Range_Struct *)etype.Struct)->begin;
				as->end = ((Range_Struct *)etype.Struct)->end;
				as->size = ((Range_Struct *)etype.Struct)->size;
				as->elementType = itype;
				break;
			default:
				std::cout << "Array Declaration Wrong" << std::endl;
				ts.type = ERROR;
				return ts;
			}
			break;
		default:
			std::cout << "Array Declaration Wrong" << std::endl;
			ts.type = ERROR;
			return ts;
		}
		llvm::ArrayType *array = llvm::ArrayType::get(as->elementType.llvm, as->size);
		ts.llvm = array;
		return ts;
	}


	int64_t getActualValue(llvm::Value *v)
	{
		llvm::Constant *constValue = llvm::cast<llvm::GlobalVariable>(v)->getInitializer();
		llvm::ConstantInt *constInt = llvm::cast<llvm::ConstantInt>(constValue);
		return constInt->getSExtValue();
	}

	Type_Struct varNode::codeGen(IR & generator) {
		Type_Struct type = this->getVarType()->codeGen(generator);
		for (auto & id : *(this->getNames())){
			Type_Struct *ts = new Type_Struct(type);
			ts->name = id;
			if(generator.InsertType(id, ts)!=-1){
				CreateEntryBlockAlloca(generator.getCurFunction(), id, ts->llvm);
			}
		}
		return type;
	}

	Type_Struct varNode::codeGenType(IR & generator) {
		Type_Struct type = this->getVarType()->codeGen(generator);
		type.istype = 1;
		for (auto & id : *(this->getNames())) {
			Type_Struct *ts = new Type_Struct(type);
			ts->name = id;
			generator.InsertType(id, ts);
	
		}
		return type;
	}



	Type_Struct varDecl::codeGen(IR & generator) {
		Type_Struct ts;
		for (auto & var : *(this->getDecls())) {
			ts=var->codeGen(generator);
		}
		return ts;
	}

	Type_Struct typeDefDecl::codeGen(IR & generator) {
		Type_Struct ts;
		for (auto & var : *(this->getNewType())) {
			ts = var->codeGenType(generator);
		}
		return ts;
	}

	Type_Struct parameter::codeGen(IR & generator) {
		Type_Struct ts=this->getSimpleType()->codeGen(generator);
	}

	Type_Struct functionNode::codeGen(IR & generator) {
		//Prototype
		std::vector<llvm::Type*> argTypes;
		for (auto & para : *this->getParams())
		{
			Type_Struct pts = para->codeGen(generator);
			for (auto & name : para->getNames()) {
				argTypes.push_back(pts.llvm);
			}
		}
		Type_Struct rts = this->getRetval()->codeGen(generator);
		llvm::FunctionType *funcType = llvm::FunctionType::get(rts.llvm, argTypes, false);
		llvm::Function *function = llvm::Function::Create(funcType, llvm::GlobalValue::InternalLinkage, this->getId(), generator.TheModule.get());
		generator.pushFunction(function);



		//Parameters
		llvm::Function::arg_iterator argIt = function->arg_begin();
		int index = 1;
		for (auto & args : *(this->getParams()))
		{
			for (auto & arg : args->getNames())
			{
				/*if (args->isVar)
				{
					//Check value
	//                alloc = generator.findValue(arg->getName());
					function->addAttribute(index, llvm::Attribute::NonNull);
					alloc = TheBuilder.CreateGEP(argIt++, TheBuilder.getInt32(0), arg->getName());
				}*/
				llvm::Value *llvm_a = argIt++;
				llvm_a->setName(arg);
				Type_Struct *ts = new Type_Struct(args->codeGen(generator));
				ts->name = arg;
				ts->istype = 0;
				generator.InsertType(arg,ts);
			}
		}

		//Return value
		llvm::Value* returnInst = NULL;
		if (!this->isprocedure) {
			Type_Struct *returnType = new Type_Struct(this->getRetval()->codeGen(generator));
			returnType->name = this->getId();
			generator.InsertType(this->getId(),returnType);
			returnInst= CreateEntryBlockAlloca(generator.getCurFunction(), id, returnType->llvm);
		}



		//Block
		llvm::BasicBlock *newBlock = llvm::BasicBlock::Create(TheContext, "entrypoint", function, nullptr);
		TheBuilder.SetInsertPoint(newBlock);

		//Sub routine
		this->getBody()->codeGen(generator);

		//Return 
		if (this->isprocedure) {
			TheBuilder.CreateRetVoid();
		}else {
			TheBuilder.CreateRet(returnInst);
		}

		//Pop back
		generator.popFunction();
		TheBuilder.SetInsertPoint(&(generator.getCurFunction())->getBasicBlockList().back());
		return Type_Struct(function);
	}

	Type_Struct rootProgram::codeGen(IR & generator) {

		//Const declareation part
		for (auto & decl : this->getDecls())
		{
			decl->codeGen(generator);
		}
		//Routine declareation part
		for (auto & funcs : this->getFuncs()) {
			funcs->codeGen(generator);
		}
		//Routine body
		Type_Struct res=this->getStmts().codeGen(generator);
		return res;
	}

	Type_Struct rootProgram::init(IR & generator) {
		//Main function prototype
		std::vector<llvm::Type*> argTypes;
		llvm::FunctionType * funcType = llvm::FunctionType::get(TheBuilder.getVoidTy(), makeArrayRef(argTypes), false);
		generator.mainFunction = llvm::Function::Create(funcType, llvm::GlobalValue::InternalLinkage, "main", generator.TheModule.get());
		llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create(TheContext, "entrypoint", generator.mainFunction, 0);

		generator.pushFunction(generator.mainFunction);
		TheBuilder.SetInsertPoint(basicBlock);
		//Create System functions
		generator.printf = generator.createPrintf();
		generator.scanf = generator.createScanf();
		for (auto & label : Label) {
			label.second->label = label.first;
		}
		//Code generate
		this->codeGen(generator);
		TheBuilder.CreateRetVoid();
		generator.popFunction();

		return Type_Struct((llvm::Value*)nullptr);
	}

	Type_Struct assignStmt::codeGen(IR & generator) {
		llvm::Value *res = nullptr;
		this->forward(generator);
		res = TheBuilder.CreateStore(this->getRhs()->codeGen(generator).llvmValue, generator.findValue(this->getLhs()->codeGen(generator).name));
	
		this->backward(generator);
		return Type_Struct(res);
	}

	Type_Struct mathExpr::codeGen(IR & generator) {
		opType op = this->getOp();
		Type_Struct left = this->getLeftChild()->codeGen(generator);
		Type_Struct right = this->getRightChild()->codeGen(generator);
		if (op == LBRB)return ArrayReference(generator);
		if (op == DOT)return RecordReference(generator);
		return BinaryOp(left.llvmValue, this->getOp(), right.llvmValue);
	}

	Type_Struct mathExpr::ArrayReference(IR & generator)
	{
		Type_Struct left = this->getLeftChild()->codeGen(generator);
		Type_Struct right = this->getRightChild()->codeGen(generator);
		Type_Struct ts;

		llvm::Value* arrayValue =left.llvmValue, *indexValue;
		if (left.type != ARRAY) {
			std::cout << "varaibe " << left.name << " is not array!"<<std::endl;
			return Type_Struct();
		}
		Array_Struct *as = (Array_Struct *)left.Struct;
		if (as->arrayType == RANGE_AS) {
			if (right.isconst) {
				indexValue = TheBuilder.getInt32(GetValue(right) - (as->begin));
			}else
			indexValue= BinaryOp(right.llvmValue, MINUS, TheBuilder.getInt32(as->begin));
		}
		else {
			for (int i = 0; i < ((Name_Struct *)as->indexType.Struct)->elements.size();i++) {
				if (right.name == ((Name_Struct *)as->indexType.Struct)->elements[i]) {
					indexValue = TheBuilder.getInt32(i);
					break;
				}
			}
		}
		if (indexValue == NULL) {
			std::cout << "Wrong Array Index of " << left.name << std::endl;
		}
		std::vector<llvm::Value*> indexList;
		indexList.push_back(TheBuilder.getInt32(0));
		indexList.push_back(indexValue);
		ts = as->elementType;
		ts.llvmValue = TheBuilder.CreateInBoundsGEP(arrayValue, llvm::ArrayRef<llvm::Value*>(indexList));
		return ts;
	}

	Type_Struct mathExpr::RecordReference(IR & generator) {
		Type_Struct left = this->getLeftChild()->codeGen(generator);
		Type_Struct right = this->getRightChild()->codeGen(generator);
		Type_Struct ts;

		llvm::Value* arrayValue = left.llvmValue, *indexValue;
		if (left.type != RECORD) {
			std::cout << "varaibe " << left.name << " is not array!" << std::endl;
			return Type_Struct();
		}
		Record_Struct *rs = (Record_Struct *)left.Struct;
		for (int i = 0; i < rs->elements.size(); i++) {
			if (right.name == rs->elements[i].name) {
				indexValue = TheBuilder.getInt32(i);
				ts = rs->elements[i];
				break;
			}
		}
		std::vector<llvm::Value*> indexList;
		indexList.push_back(TheBuilder.getInt32(0));
		indexList.push_back(indexValue);
		ts.llvmValue = TheBuilder.CreateInBoundsGEP(arrayValue, llvm::ArrayRef<llvm::Value*>(indexList));
		return ts;
	}

	Type_Struct functionCall::codeGen(IR & generator){
		this->forward(generator);
		if (this->getFunc_name() == "write")SysProcWrite(generator,false);
		if (this->getFunc_name() == "writeln")SysProcWrite(generator, true);
		if (this->getFunc_name() == "read")SysProcRead(generator);
		llvm::Function *function = generator.TheModule->getFunction(this->getFunc_name());
		if (function == nullptr)
		{
			std::cout << "No Function " << this->getFunc_name() << std::endl;
		}
		std::vector<llvm::Value*> args;
		for (auto & arg : *(this->getArgs()))
		{
			args.push_back(arg->codeGen(generator));
		}
		llvm::Value *res = TheBuilder.CreateCall(function, args, "calltmp");
		this->backward(generator);
		Type_Struct ts=*generator.findFunction(this->getFunc_name());
		ts.llvmValue = res;
		return ts;
	}


	Type_Struct functionCall::SysProcWrite(IR & generator, bool isLineBreak)
	{
		std::string formatStr = "";
		std::vector<llvm::Value*> params;
		if (this->getArgs()->size() != 1) std::cout << "wrong argument for write/writeln" << std::endl;
		Type_Struct arg = (*this->getArgs())[0]->codeGen(generator);
		switch (arg.type)
		{
		case INTEGER:
			formatStr += "%d";
			break;
		case CHAR:
			formatStr += "%c";
			break;
		case BOOLEAN:
			formatStr += "%d";
			break;
		case REAL:
			formatStr += "%lf";
			break;
		default:
			std::cout << "[ERROR]Invalid type to write" << std::endl;
			break;
		}
		params.push_back(arg.llvmValue);
		if (isLineBreak)
		{
			formatStr += "\n";
		}
		auto formatConst = llvm::ConstantDataArray::getString(TheContext, formatStr.c_str());
		auto formatStrVar = new llvm::GlobalVariable(*(generator.TheModule), llvm::ArrayType::get(TheBuilder.getInt8Ty(), formatStr.size() + 1), true, llvm::GlobalValue::ExternalLinkage, formatConst, ".str");
		auto zero = llvm::Constant::getNullValue(TheBuilder.getInt32Ty());
		llvm::Constant* indices[] = { zero, zero };
		auto varRef = llvm::ConstantExpr::getGetElementPtr(formatStrVar->getType()->getElementType(), formatStrVar, indices);
		//    auto varRef
		params.insert(params.begin(), varRef);
		 
		TheBuilder.CreateCall(generator.printf, llvm::makeArrayRef(params), "printf");
		return Type_Struct(VOID);
	}

	Type_Struct functionCall::SysProcRead(IR & generator)
	{
		std::string formatStr = "";
		std::vector<llvm::Value*> params;
		Type_Struct arg = (*this->getArgs())[0]->codeGen(generator);
		llvm::Value *argAddr, *argValue;
		//Just common variable
		argAddr = arg.llvmValue;
		switch (arg.type)
		{
		case INTEGER:
			formatStr += "%d";
			break;
		case CHAR:
			formatStr += "%c";
			break;
		case BOOLEAN:
			formatStr += "%d";
			break;
		case REAL:
			formatStr += "%lf";
			break;
		default:
			std::cout << "[ERROR]Invalid type to write" << std::endl;
			break;
		}
		params.push_back(argAddr);
		params.insert(params.begin(), TheBuilder.CreateGlobalStringPtr(formatStr));
		TheBuilder.CreateCall(generator.scanf, params, "scanf");
		return Type_Struct(VOID);
	}


	Type_Struct ifStmt::codeGen(IR & generator) {
		this->forward(generator);

		llvm::Value *condValue = this->getCond()->codeGen(generator).llvmValue, *thenValue = nullptr, *elseValue = nullptr;
		condValue = TheBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 0, true), "ifCond");

		llvm::Function *TheFunction = generator.getCurFunction();
		llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
		llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
		llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(TheContext, "merge", TheFunction);

		//Then
		auto branch = TheBuilder.CreateCondBr(condValue, thenBB, elseBB);
		TheBuilder.SetInsertPoint(thenBB);
		thenValue = this->getExecStmt()->codeGen(generator);
		TheBuilder.CreateBr(mergeBB);
		thenBB = TheBuilder.GetInsertBlock();


		TheBuilder.SetInsertPoint(elseBB);
		if (this->getElseStmt() != nullptr)
		{
			elseValue = this->getElseStmt()->codeGen(generator);
		}
		TheBuilder.CreateBr(mergeBB);
		elseBB = TheBuilder.GetInsertBlock();

		TheBuilder.SetInsertPoint(mergeBB);

		this->backward(generator);
		
		return Type_Struct(branch);
	}

	Type_Struct repeatStmt::codeGen(IR & generator) {
		this->forward(generator);

		llvm::Function *TheFunction = generator.getCurFunction();
		llvm::BasicBlock *condBB = llvm::BasicBlock::Create(TheContext, "cond", TheFunction);
		llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
		llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterLoop", TheFunction);

		//Loop
		TheBuilder.CreateBr(loopBB);
		TheBuilder.SetInsertPoint(loopBB);
		*(this->getStmtList())->codeGen(generator);
		TheBuilder.CreateBr(condBB);
		loopBB = TheBuilder.GetInsertBlock();

		//Cond
		TheBuilder.SetInsertPoint(condBB);
		llvm::Value *condValue = this->getCond()->codeGen(generator).llvmValue;
		condValue = TheBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 0, true), "repeateCond");
		auto branch = TheBuilder.CreateCondBr(condValue, loopBB, afterBB);

		//After
		TheBuilder.SetInsertPoint(afterBB);
		this->backward(generator);
		return Type_Struct(branch);
	}

	Type_Struct whileStmt::codeGen(IR & generator){
		this->forward(generator);
		llvm::Function *TheFunction = generator.getCurFunction();
		llvm::BasicBlock *condBB = llvm::BasicBlock::Create(TheContext, "cond", TheFunction);
		llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
		llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterLoop", TheFunction);

		//Cond
		TheBuilder.CreateBr(condBB);
		TheBuilder.SetInsertPoint(condBB);
		llvm::Value *condValue = this->getCond()->codeGen(generator).llvmValue;
		condValue = TheBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 0, true), "whileCond");
		auto branch = TheBuilder.CreateCondBr(condValue, loopBB, afterBB);
		condBB = TheBuilder.GetInsertBlock();

		//Loop
		TheBuilder.SetInsertPoint(loopBB);
		this->getStmtlist()->codeGen(generator);
		TheBuilder.CreateBr(condBB);

		//After
		TheBuilder.SetInsertPoint(afterBB);
		this->backward(generator);
		return branch;
	}

	Type_Struct forStmt::codeGen(IR & generator) {
		this->forward(generator);
		//Init
		llvm::Function *TheFunction = generator.getCurFunction();
		llvm::Value* startValue = this->getFrom()->codeGen(generator).llvmValue;
		llvm::Value* endValue = this->getTo()->codeGen(generator).llvmValue;
		llvm::Value *condValue = nullptr, *curValue = nullptr, *varValue = generator.findValue(this->getId());
		TheBuilder.CreateStore(startValue, varValue);

		llvm::BasicBlock *condBB = llvm::BasicBlock::Create(TheContext, "cond", TheFunction);
		llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
		llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterLoop", TheFunction);

		//Cond
		TheBuilder.CreateBr(condBB);
		TheBuilder.SetInsertPoint(condBB);
		//    curValue = TheBuilder.CreateLoad(varValue, this->var->getName());
		curValue = TheBuilder.CreateStore(startValue, varValue);
		if (this->getDirection())
		{
			condValue = TheBuilder.CreateICmpSLE(curValue, endValue);
		}
		else
		{
			condValue = TheBuilder.CreateICmpSGE(curValue, endValue);
		}
		condValue = TheBuilder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(TheContext), 0, true), "forCond");
		auto branch = TheBuilder.CreateCondBr(condValue, loopBB, afterBB);
		condBB = TheBuilder.GetInsertBlock();

		//Loop
		TheBuilder.SetInsertPoint(loopBB);
		this->getStmtlist()->codeGen(generator);
		llvm::Value *tmpValue = TheBuilder.CreateAdd(curValue, TheBuilder.getInt32(this->getDirection() ? 1 : -1));
		TheBuilder.CreateStore(tmpValue, varValue);
		TheBuilder.CreateBr(condBB);
		loopBB = TheBuilder.GetInsertBlock();

		//After
		TheBuilder.SetInsertPoint(afterBB);
		this->backward(generator);
		return Type_Struct(branch);
	}

	Type_Struct caseStmt::codeGen(IR & generator) {
		this->forward(generator);

		llvm::Value *cmpValue = this->getCond()->codeGen(generator).llvmValue, *condValue = nullptr;
		llvm::Function *TheFunction = generator.getCurFunction();
		llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(TheContext, "afterCase", TheFunction);
		std::vector<llvm::BasicBlock*> switchBBs, caseBBs;	
		for (int i = 0; i < this->getCases().size(); i++)
		{
			switchBBs.push_back(llvm::BasicBlock::Create(TheContext, "switch", TheFunction));
			caseBBs.push_back(llvm::BasicBlock::Create(TheContext, "case", TheFunction));
		}
		TheBuilder.CreateBr(switchBBs[0]);
		for (int i = 0; i < this->getCases().size(); i++)
		{
			//Switch
			TheBuilder.SetInsertPoint(switchBBs[i]);
			condValue = BinaryOp(cmpValue, EQUAL, this->getCases()[i]->case_->codeGen(generator).llvmValue);
			if (i < this->getCases().size() - 1)
			{
				TheBuilder.CreateCondBr(condValue, caseBBs[i], switchBBs[i + 1]);
			}
			else
			{
				TheBuilder.CreateCondBr(condValue, caseBBs[i], afterBB);
			}

			//Case
			TheBuilder.SetInsertPoint(caseBBs[i]);
			this->getCases()[i]->stmt->codeGen(generator);
			TheBuilder.CreateBr(afterBB);
		}

		//After
		TheBuilder.SetInsertPoint(afterBB);
		this->backward(generator);
		return Type_Struct((llvm::Value *)nullptr);
	}


	void utilsInterface::forward(IR & generator)
	{
		llvm::Function *TheFunction = generator.getCurFunction();
		if (this->label >= 0)
		{
			if (generator.labelBlock[this->label] == nullptr)
			{
				generator.labelBlock[this->label] = llvm::BasicBlock::Create(TheContext, "Label_" + to_string(label), TheFunction);
			}
			if (this->afterBB == nullptr)
			{
				this->afterBB = llvm::BasicBlock::Create(TheContext, "afterLabel_" + to_string(this->label), TheFunction);
			}
			TheBuilder.CreateBr(generator.labelBlock[this->label]);
			TheBuilder.SetInsertPoint(generator.labelBlock[this->label]);
		}
	}

	void utilsInterface::backward(IR & generator)
	{
		if (this->label >= 0 && afterBB != nullptr)
		{
			TheBuilder.SetInsertPoint(generator.labelBlock[this->label]);
			TheBuilder.CreateBr(this->afterBB);
			TheBuilder.SetInsertPoint(this->afterBB);
		}
	}

	Type_Struct gotoStmt::codeGen(IR & generator) {
		this->forward(generator);
		llvm::Value *res = nullptr;
		if (generator.labelBlock[this->getLabel()] == nullptr)
		{
			generator.labelBlock[this->getLabel()] = llvm::BasicBlock::Create(TheContext, "Label_" + to_string(this->getLabel()), generator.getCurFunction());
		}
		res = TheBuilder.CreateBr(generator.labelBlock[this->getLabel()]);
		//    if (this->afterBB == nullptr)
		//    {
		//        this->afterBB = llvm::BasicBlock::Create(TheContext, "afterLabel_" + to_string(this->toLabel), generator.getCurFunction());
		//    }
		//    TheBuilder.SetInsertPoint(this->afterBB);
		this->backward(generator);
		return Type_Struct(res);
	}

	Type_Struct stmtList::codeGen(IR & generator) {
		this->forward(generator);
		Type_Struct lastValue;
		for (auto & stmt : this->getStmtList())
		{
			lastValue = stmt->codeGen(generator);
		}
		this->backward(generator);
		return lastValue;
	}


}
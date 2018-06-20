#include "asm.hpp"
#include <sstream>


Reg makeExp(string val)
{
	Reg r = RegPool::getAvailReg();
	EMIT("li " + REG_TO_STR(r) + ", " + val);

	return r;
}

Reg makeBinOpExpAdd(Reg r1, Reg r2) {
	EMIT_OP("add ", r1, r2);
	if (r1 != r2)
		REG_FREE(r2);

	return r1;
}
Reg makeBinOpExpSub(Reg r1, Reg r2) {
	EMIT_OP("sub ", r1, r2);
	if (r1 != r2)
		REG_FREE(r2);

	return r1;
}
Reg makeBinOpExpMul(Reg r1, Reg r2) {
	EMIT("mult " + REG_TO_STR(r1) + " ," + REG_TO_STR(r2));
	MFLO(r1);
	if (r1 != r2)
		REG_FREE(r2);

	return r1;
}
Reg makeBinOpExpDiv(Reg r1, Reg r2) {
	Reg tmp = makeExp("0");
	EMIT("beq " + REG_TO_STR(r2) + " ," + REG_TO_STR(tmp) + " , divByZeroErr");
	REG_FREE(tmp);
	EMIT("div " + REG_TO_STR(r1) + " ," + REG_TO_STR(r2));
	MFLO(r1);

	if (r1 != r2)
		REG_FREE(r2);

	return r1;
}


Reg makeBinOpExp(string op, Reg r1, Reg r2)
{
	if (op == "+")
		return makeBinOpExpAdd(r1, r2);
	else if (op == "-")
		return makeBinOpExpSub(r1, r2);
	else if (op == "*")
		return makeBinOpExpMul(r1, r2);
	else if (op == "/")
		return makeBinOpExpDiv(r1, r2);

	return MAX_REG;
}

void makeRelOpExp(string op, Reg r1, Reg r2, vector<int>** trueList, vector<int>** falseList)
{
	string asmOp;
	if (op == "==")
		makeRelOpExpCode("beq ",r1, r2, trueList, falseList);
	else if (op == "!=")
		makeRelOpExpCode("bne ", r1, r2, trueList, falseList);
	else if (op == "<")
		makeRelOpExpCode("blt ", r1, r2, trueList, falseList);
	else if (op == ">")
		makeRelOpExpCode("bgt ", r1, r2, trueList, falseList);
	else if (op == "<=")
		makeRelOpExpCode("ble ", r1, r2, trueList, falseList);
	else if (op == ">=")
		makeRelOpExpCode("bge ", r1, r2, trueList, falseList);
	else
		assert(0);
}

void makeRelOpExpCode(string op, Reg r1, Reg r2, vector<int>** trueList, vector<int>** falseList)
{
	int trueQuad, falseQuad;

	trueQuad = EMIT(op + REG_TO_STR(r1) + " ," + REG_TO_STR(r2) + " , ");
	falseQuad = EMIT("b ");
	*trueList = new vector<int>(MAKE_LIST(trueQuad));
	*falseList = new vector<int>(MAKE_LIST(falseQuad));

	REG_FREE(r1);
	REG_FREE(r2);
}

void copyRetAddrToStack(int numOfArgs)
{
	int stackIndex = numOfArgs * REG_SIZE;
	ostringstream ostr;
	ostr << stackIndex;
	EMIT("sw $ra , " + ostr.str() + "($sp)");
}

void createDivByZeroErrFunc() {
	EMITDATA("errmsg: .asciiz \"Error division by zero\\n\"");
	EMIT("divByZeroErr:");
	EMIT("li $v0,4");
	EMIT("la $a0,errmsg");
	EMIT("syscall");
	EMIT("li $v0,10");
	EMIT("syscall");
}

void createOutOfBoundErrFunc() {
	EMITDATA("errarraymsg: .asciiz \"Error index out of bounds\\n\"");
	EMIT("outOfBoundErr:");
	EMIT("li $v0,4");
	EMIT("la $a0,errarraymsg");
	EMIT("syscall");
	EMIT("li $v0,10");
	EMIT("syscall");
}

void createPrintFunc() {
	EMIT("print:");
	EMIT("lw $a0,0($sp)");
	EMIT("li $v0,4");
	EMIT("syscall");
	EMIT("jr $ra");
}

void createPrintiFunc() {
	EMIT("printi:");
	EMIT("lw $a0,0($sp)");
	EMIT("li $v0,1");
	EMIT("syscall");
	EMIT("jr $ra");
}

Reg handleBoolVal(vector<int> *trueList, vector<int> *falseList) {
	Reg place = REG_GET_AVAIL;
	string trueLabel = NEXT_LABEL;
	EMIT("li " + REG_TO_STR(place) + ", 1");
	int branch = EMIT("b ");

	string falseLable = NEXT_LABEL;
	EMIT("li " + REG_TO_STR(place) + ", 0");
	string origCode = NEXT_LABEL;

	BACKPATCH(MAKE_LIST(branch), origCode);
	BACKPATCH(*trueList, trueLabel);
	BACKPATCH(*falseList, falseLable);

	return place;
}


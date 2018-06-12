#include "asm.hpp"

#define EMIT(str) CodeBuffer::instance().emit(str + ";")
#define REG_TO_STR(reg) RegPool::regToString(reg)
#define REG_FREE(r) RegPool::freeReg(r)
#define EMIT_OP(op,r1,r2) EMIT(op + REG_TO_STR(r1) + " ,"+ REG_TO_STR(r1)+" ," + REG_TO_STR(r2))
#define MFLO(r) EMIT(string("mflo ") + REG_TO_STR(r1))


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
	EMIT("beq " + REG_TO_STR(tmp) + " ," + REG_TO_STR(r2) + " , divByZeroErr");
	REG_FREE(tmp);
	EMIT("div " + REG_TO_STR(r1) + " ," + REG_TO_STR(r2));
	MFLO(r1);

	if (r1 != r2)
		REG_FREE(r2);

	return r1;
}


Reg makeBinOpExp(string val, Reg r1, Reg r2)
{
	if (val == "+")
		return makeBinOpExpAdd(r1, r2);

	if (val == "-")
		return makeBinOpExpSub(r1, r2);

	if (val == "*")
		return makeBinOpExpMul(r1, r2);

	if (val == "/")
		return makeBinOpExpDiv(r1, r2);

	return MAX_REG;

}


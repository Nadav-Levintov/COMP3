#ifndef ASM_H
#define ASM_H

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include "regs.h"

using namespace std;
using namespace output;

#define EMIT(str) CodeBuffer::instance().emit(str)
#define EMITDATA(str) CodeBuffer::instance().emitData(str)
#define EMITFP EMIT("subu $fp, $sp, 4")
#define REG_TO_STR(reg) RegPool::regToString(reg)
#define REG_FREE(r) RegPool::freeReg(r)
#define EMIT_OP(op,r1,r2) EMIT(op + REG_TO_STR(r1) + " ,"+ REG_TO_STR(r1)+" ," + REG_TO_STR(r2))
#define MFLO(r) EMIT(string("mflo ") + REG_TO_STR(r1))
#define MAKE_LIST(n) CodeBuffer::makelist(n)
#define NEXT_LABEL CodeBuffer::instance().genLabel()
#define BACKPATCH(address_list,loc) CodeBuffer::instance().bpatch(address_list,loc)
#define MERGE_LISTS(l1,l2) CodeBuffer::merge(l1,l2)
#define REG_GET_AVAIL RegPool::getAvailReg()
#define SAVE_ALL_REGS RegPool::regsSaveAll()
#define LOAD_ALL_REGS RegPool::regsLoadAll()

Reg makeExp(string val);
Reg makeBinOpExp(string val, Reg r1, Reg r2);
Reg makeBinOpExpAdd(Reg r1, Reg r2);
Reg makeBinOpExpSub(Reg r1, Reg r2);
Reg makeBinOpExpMul(Reg r1, Reg r2);
Reg makeBinOpExpDiv(Reg r1, Reg r2);
Reg makeBinOpExp(string val, Reg r1, Reg r2);
void makeRelOpExp(string op, Reg r1, Reg r2, vector<int>** trueList, vector<int>** falseList);
void makeRelOpExpCode(string op, Reg r1, Reg r2, vector<int>** trueList, vector<int>** falseList);
void copyRetAddrToStack(int numOfArgs);
void createDivByZeroErrFunc();
void createPrintFunc();
void createPrintiFunc();

#endif
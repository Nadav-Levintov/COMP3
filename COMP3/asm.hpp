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
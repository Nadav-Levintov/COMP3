#pragma once
#ifndef REGS_H
#define REGS_H
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stack>
#include "output.hpp"
#include "bp.hpp"
#include <assert.h>

using namespace std;
using namespace output;

#define REG_SIZE 4

typedef enum reg_e {t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,s0,s1,s2,s3,s4,s5,s6,s7,MAX_REG} Reg;

class RegPool
{
private:
	bool pool[MAX_REG+1]; // free = t, taken = f
	RegPool(){
		for (int i = 0; i < MAX_REG; i++)
			pool[i] = true;
	}

	/*Singelton Pool so lets disable these constrcurs */
	RegPool(RegPool const&);
	void operator=(RegPool const&);

public:
	static RegPool& getPoolInstance();
	static string regToString(Reg r);
	static Reg getAvailReg();
	static void freeReg(Reg r);
	static void regsSaveAll();
	static void regsLoadAll();
};


#endif // !REGS_H


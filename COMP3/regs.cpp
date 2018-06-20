#include "regs.h"
#include <sstream>

using namespace std;
using namespace output;

string regs_name[] = { "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$t8","$t9","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7" };

RegPool& RegPool::getPoolInstance() {
	static RegPool p;
	return p;
}

string RegPool::regToString(Reg r) {
	if (r == MAX_REG)
	{
		cout << "trying to print ileagle reg: " << r << endl;
		assert(0);
	}
	return regs_name[r];
}

Reg RegPool::getAvailReg()
{
	Reg i = Reg(0);
	while (i < MAX_REG)
	{
		if (RegPool::getPoolInstance().pool[i])
		{
			RegPool::getPoolInstance().pool[i] = false;
			return i;
		}
		i=Reg(i+1);
	}
	cout << "Out of regs" << endl;
	assert(0);
	return MAX_REG;
}

void RegPool::regsSaveAll()
{
	CodeBuffer::instance().emit("subu $sp ,$sp ,72");
	
	for (int i = 0; i < MAX_REG; i++)
	{
		ostringstream s;
		s << i * REG_SIZE;
		CodeBuffer::instance().emit("sw " + RegPool::getPoolInstance().regToString(Reg(i)) + "," + s.str() + "($sp)");
	}
}

void RegPool::regsLoadAll() {
	for (int i = 0; i < MAX_REG; i++)
	{
		ostringstream s;
		s << i * REG_SIZE;
		CodeBuffer::instance().emit("lw " + RegPool::getPoolInstance().regToString(Reg(i)) + "," + s.str() + "($sp)");
	}

	CodeBuffer::instance().emit("addu $sp ,$sp ,72");
}

void RegPool::freeReg(Reg r)
{
	if(r == MAX_REG)
	{
		cout << "trying to free ileagle reg" << endl;
		assert(0);
	}
	RegPool::getPoolInstance().pool[r] = true;
}
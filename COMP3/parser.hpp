#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <list>
#include <stack>
#include <climits>

using namespace std;

typedef enum type_e {
	OUR_INT,
	OUR_BYTE,
	OUR_BOOL,
	OUR_STRING,
	OUR_VOID
}Type_enum;

/* YYSTYPE */

struct Node {
	Type_enum type;
	int int_val;
	string str_val;

public:
	Node(Type_enum t = OUR_VOID, int int_val = 0, string str = "");
};


class Num : public Node {

	int value;
};

class String : public Node {

	string val;
};

class Bool : public Node {

	bool val;
};

class Int : public Num {

};

class Byte : public Num {

};


class Exp : public Node {
	string str_val;
	int int_val;
};



class Program : public Node {};
class Funcs : public Node {};
class RetType : public Node {

};
class FuncDecl : public Node {
	string id;
	RetType retType;
};

class FormalsDecl : public Node {
	string id;
	int arraySize;
	bool isArray;
	bool isArrayByte;

public:
	FormalsDecl() {}
	FormalsDecl(Type_enum t, string i, int size = 0, bool isArray = false, bool isArrayByte = false) :Node(t), id(i), arraySize(size), isArray(isArray), isArrayByte(isArrayByte) {}
};

class FormalsList : public Node {
	list<FormalsDecl> frmalsList;

public:

	void addFormal(FormalsDecl& f)
	{
		frmalsList.push_back(f);
	}
	void mergeList(FormalsList& fList)
	{
		frmalsList.merge(fList.frmalsList);
	}
};

class Formals : public Node {
	FormalsList list;

public:
	Formals(FormalsList list) :list(list) {}
};

class Statements : public Node {};
class Statement : public Node {
	string id;
	Exp e;
};
class Call : public Node {};
class ExpList : public Node {};
class Type : public Node {};



#define YYSTYPE Node*


/* Symbol table */

class Table
{
};

class VarTableEntry
{
	string name;
	Type type;
	int offset;

public:
	VarTableEntry(string name, Type type, int offset) :name(name), type(type), offset(offset) {	}
};

class FuncTableEntry
{
	string name;
	Type type;
	Type retType;
	list<FormalsDecl> frmalsList;

public:
	FuncTableEntry(string name, Type type, int offset, list<FormalsDecl> frmalsList) :name(name), type(type), offset(offset), frmalsList(frmalsList) {	}
};

class VarTable : public Table
{
	stack<VarTableEntry> rows;

public:
	VarTable()
	{
		rows = new stack<VarTableEntry>();
	}
};

class FuncTable : public Table
{
	stack<FuncTableEntry> rows;

public:
	FuncTable()
	{
		rows = new stack<FuncTableEntry>();
	}
};



#endif
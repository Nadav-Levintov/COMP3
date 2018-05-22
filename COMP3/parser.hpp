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

class Node {
public:
	Type_enum type;
	string id;
	Node(Type_enum t = OUR_VOID, string id="") :type(t), id(id) {}

	virtual ~Node() {}
};

class TypeNonTerminal : public Node {
public:
	TypeNonTerminal(Type_enum t) : Node(t) {}
};

class TypeInt : public TypeNonTerminal {
public:
	TypeInt() :TypeNonTerminal(OUR_INT) {}
};

class TypeBool : public TypeNonTerminal {
public:
	TypeBool() :TypeNonTerminal(OUR_BOOL) {}
};

class TypeByte : public TypeNonTerminal {
public:
	TypeByte() :TypeNonTerminal(OUR_BYTE) {}
};

class BoolExp : public Node {
	bool val;
public:
	BoolExp(bool v) : Node(OUR_BOOL), val(val) {}
};

class NumExp : public Node {
	int val;
public:
	NumExp(int v) : Node(OUR_INT), val(val) {}
};

class ByteExp : public Node {
	int val;
public:
	IntExp(int v) : Node(OUR_BYTE), val(val) {}
};

class StringExp : public Node {
	string val;
public:
	StringExp(string v) : Node(OUR_STRING), val(val) {}
};

class BinOp : public Node {
	Node *first, *second;
public:
	BinOp(Node* _first, Node* _second) :Node(OUR_BYTE) {
		first = _first;
		second = _second;
		if (_first->type == OUR_INT || _second->type == OUR_INT)
			this.type = OUR_INT;
	}
};

class RelOp : public Node {
	Node *first, *second;
public:
	RelOp(Node* _first, Node* _second) :Node(OUR_BOOL) {
		first = _first;
		second = _second;
	}
};

class And : public Node {
	Node *first, *second;
public:
	And(Node* _first, Node* _second) :Node(OUR_BOOL) {
		first = _first;
		second = _second;
	}
};

class Or : public Node {
	Node *first, *second;
public:
	Or(Node* _first, Node* _second) :Node(OUR_BOOL) {
		first = _first;
		second = _second;
	}
};

class Not : public Node {
	Node *first;
public:
	Not(Node* _first) :Node(OUR_BOOL) {
		first = _first;
	}
};

Class Num : public Node{
public:
	int val;
	Num(Type_enum t, int val) :Node(t),val(val) {}
}

Class Array : public Node{
public:
	int size;
	Array(Type_enum t, int size) :Node(t), size(size) {}
}

class ExpList : public Node {
public:
	list<Node*> lst;
	ExpList() {	}
};

public:
	RetType(type_e t) :Node(type) {}

};

class FormalsDecl : public Node {
public:
	string id;
	int arraySize;
	bool isArray;
	bool isArrayByte;

	bool operator<(const FormalsDecl& a)
	{
		return this->id < a.id;
	}
	FormalsDecl() {}
	FormalsDecl(FormalsDecl &f) {
		this->type = f.type;
		this->id = f.id;
		this->arraySize = f.arraySize;
		this->isArray = f.isArray;
		this->isArrayByte = f.isArrayByte;
	}
	FormalsDecl(Type_enum t, string i, int size = 0, bool isArray = false, bool isArrayByte = false) :Node(t), id(i), arraySize(size), isArray(isArray), isArrayByte(isArrayByte) {}

	bool operator==(FormalsDecl f)
	{
		if (this.id != f.id)
			return false;
		return true;
	}

	bool compareType(FormalsDecl f)
	{
		if (this->type != f.type)
			return false;
		if (this->isArray != f.isArray)
			return false;
		if (this->arraySize != f.size)
			return false;

		return true;
	}
};

class FormalsList : public Node {
	list<FormalsDecl> frmalsList;

public:

	void addFormal(FormalsDecl& f)
	{
		frmalsList.push_back(f);
	}
	void addFormal(FormalsDecl* f)
	{
		frmalsList.push_back(*f);
	}
	void mergeList(FormalsList& fList)
	{
		frmalsList.merge(fList.frmalsList);
	}
	void mergeList(FormalsList *fList)
	{
		frmalsList.merge((*fList).frmalsList);
	}
};

class Formals : public Node {
public:
	FormalsList list;
	Formals(FormalsList *list) :list(*list) {}
	Formals(FormalsList list) :list(list) {}
};

class Statements : public Node {};
class Statement : public Node {
	string id;
	Exp e;
};
class Call : public Node {};
class ExpList : public Node {};
class TypeNonTerminal : public Node {};

class FuncDecl : public Node {
	string id;
	RetType retType;
	Formals formals;

public:
	FuncDecl(RetType *retType, string id, Formals *formals) :id(id), retType(*retType), formals(*formals) {}
};


/*
class Exp : public Node {
};

class Op : public Node {

};

class Not : public Exp {
	Exp* e;

public:
	Not(Exp *e) : e(e) {}
};

class OR : public Exp {
	Exp *e1, *e2;

public:
	Or(Exp *e1, Exp *e2) : e1(e1), e2(e2) {}
};

class And : public Exp {
	Exp *e1, *e2;

public:
	And(Exp *e1, Exp *e2) : e1(e1), e2(e2) {}
};

class Binop : public Exp {
	Exp *e1, *e2;

public:
	Binop(Exp *e1, Exp *e2) : e1(e1), e2(e2) {}
};

class Relop : public Exp {
	Exp *e1, *e2;

public:
	Relop(Exp *e1, Exp *e2) : e1(e1), e2(e2) {}
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






class Program : public Node {};
class Funcs : public Node {};
class RetType : public Node {

*/



#define YYSTYPE Node*


/* Symbol table */

class VarType {
public:
	Type_enum type;
	VarType(Type_enum type) :type(type) {}
};

class ArrayType : public VarType {
public:
	int size;
	ArrayType(Type_enum type, int size) :VarType(type), size(size) {}
};

class Table
{
};

class VarTableEntry
{
	FormalsDecl frml;
	int offset;

public:
	VarTableEntry(FormalsDecl frml, int offset) : frml(frml), offset(offset) {	}
};

class FuncTableEntry
{
	string id;
	Type_enum retType;
	list<FormalsDecl> frmalsList;

public:
	FuncTableEntry(string id, Type_enum retType, list<VarType> frmalsList) :id(id), retType(retType), frmalsList(frmalsList) {	}
};

class VarTable : public Table //Scope table
{
public:
	list<VarTableEntry> rows;
	bool is_while;
	VarTable(bool is_while = false) :is_while(is_while) {}

	void push(VarTableEntry entry)
	{
		rows.push_back(entry);
	}
};

class FuncTable : public Table
{
	list<FuncTableEntry> rows;

public:
	FuncTable() {}

	void push(FuncTableEntry entry)
	{
		rows.push_back(entry);
	}
};



#endif
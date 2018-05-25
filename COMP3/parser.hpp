#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <list>
#include <stack>
#include <climits>

using namespace std;

#define YYSTYPE Node*

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
	int intVal;
	int arraySize;
	bool isArray;

	list<Node*> expList;
	list<Node*> frmlList;

	Node() {}
	Node(string id, Type_enum type) {
		this->id = id;
		this->type = type;

		this->intVal = 0;
		this->arraySize = 0;
		this->isArray = false;
	}
	Node(string id, Type_enum type, int array_size) {
		this->id = id;
		this->arraySize = arraySize;
		this->isArray = true;
		this->type = type;

		this->intVal = 0;
	}
	Node(string id) {
		this->id = id;
		this->type = OUR_STRING;

		this->intVal = 0;
		this->arraySize = 0;
		this->isArray = false;
	}
	Node(int intVal, string id) {
		this->intVal = intVal;
		this->type = OUR_INT;

		this->id = id;
		this->arraySize = 0;
		this->isArray = false;
	}
	Node(Type_enum type) {
		this->type = type;

		this->id = "";
		this->intVal = 0;
		this->arraySize = 0;
		this->isArray = false;
	}
	Node(Type_enum type, int intVal) {
		this->type = type;
		this->intVal = intVal;

		this->id = "";
		this->arraySize = 0;
		this->isArray = false;
	}

	bool operator<(const Node& a)
	{
		return this->id < a.id;
	}

	bool compareType(Node* node)
	{
		if (this->type != node->type)
			return false;
		if (this->isArray != node->isArray)
			return false;
		if (this->arraySize != node->arraySize)
			return false;
		return true;
	}

	bool compareId(Node* node)
	{
		return (this->id == node->id);
	}

	bool operator==(Node* node)
	{
		return this->compareId(node) && this->compareType(node);
	}

	bool isBool()
	{
		return this->type == OUR_BOOL && !this->isArray;
	}

	bool isNum()
	{
		return (this->type == OUR_INT || this->type == OUR_BYTE) && !this->isArray;
	}
	
	bool compareVar(Node *node)
	{
		return this->id == node->id && this->type == node->type && this->isArray == node->isArray;
	}
	
	virtual ~Node() {}


};
/*
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
	ExpList(list<Node*> lst):lst(lst) {	}
	ExpList() {	}
	bool operator== (ExpList l)
	{
		int i = 0;
		for (Node *n : this.lst)
		{
			if (n.id != l.lst.get(i).id || n.type != l.lst.get(i).type)
				return false;
			i++;
		}
		return true;
	}
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

	bool operator<(const Node& a)
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
class TypeNonTerminal : public Node {};

class FuncDecl : public Node {
	string id;
	RetType retType;
	Formals formals;

public:
	FuncDecl(RetType *retType, string id, Formals *formals) :id(id), retType(*retType), formals(*formals) {}
};
*/


/* Symbol table */

//class VarType {
//public:
//	Type_enum type;
//	VarType(Type_enum type) :type(type) {}
//};
//
//class ArrayType : public VarType {
//public:
//	int size;
//	ArrayType(Type_enum type, int size) :VarType(type), size(size) {}
//};

class TableEntry
{
public:
	virtual ~TableEntry() {}
};

class Table
{
public:
	bool is_while;
	Type_enum retType;
	Table() {}
	Table(bool is_while = false, Type_enum retType = OUR_VOID) :is_while(is_while), retType(retType) {}

	Type_enum get_scope_type()
	{
		return this->retType;
	}
	virtual void push(TableEntry entry) = 0;
	virtual ~Table() {}
};

class VarTableEntry : public TableEntry
{
	Node *node;
	int offset;

public:
	VarTableEntry(Node *node, int offset) : node(node), offset(offset) {	}
};

class FuncTableEntry : public TableEntry
{
	string id;
	Type_enum retType;
	list<Node*> nodeList;

public:
	FuncTableEntry(string id, Type_enum retType, list<Node*> nodeList) :id(id), retType(retType), nodeList(nodeList) {	}
};

class VarTable : public Table //Scope table
{
public:
	list<VarTableEntry*> rows;
	VarTable(bool is_while = false) :Table(is_while) {}

	virtual void push(TableEntry *entry)
	{
		rows.push_back(dynamic_cast<VarTableEntry*>(entry));
	}
};

class FuncTable : public Table
{
	list<FuncTableEntry*> rows;

public:
	FuncTable(bool is_while = false) :Table(is_while) {}

	virtual void push(TableEntry *entry)
	{
		rows.push_back(dynamic_cast<FuncTableEntry*>(entry));
	}
};



#endif
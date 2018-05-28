#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;
using namespace output;

#define YYSTYPE Node*

typedef enum type_e {
	OUR_INT,
	OUR_BYTE,
	OUR_BOOL,
	OUR_STRING,
	OUR_VOID
}Type_enum;

static string get_type_string(Type_enum t)
{
	switch (t)
	{
	case OUR_INT:
		return "INT";
	case OUR_BYTE:
		return "BYTE";
	case OUR_BOOL:
		return "BOOL";
	case OUR_STRING:
		return "STRING";
	default:
		return "VOID";
	}
}

/* YYSTYPE */

class Node {
public:
	Type_enum type;
	string id;
	int intVal;
	int arraySize;
	bool isArray;

	vector<Node*> expList;
	vector<Node*> frmlList;

	Node() {}
	Node(string id, Type_enum type) {
		this->id = id;
		this->type = type;

		this->intVal = 0;
		this->arraySize = 0;
		this->isArray = false;
	}
	Node(string id, Type_enum type, int arraySize) {
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
	Node(Node *node) {
		this->type = node->type;
		this->intVal = node->intVal;
		this->id = node->id;
		this->arraySize = node->arraySize;
		this->isArray = node->isArray;
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
		if (this->isArray && node->isArray && this->arraySize != node->arraySize)
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

	bool isByte()
	{
		return this->type == OUR_BYTE && !this->isArray;
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

	virtual void print_scope() = 0;

	virtual ~Table() {}
};

class VarTableEntry : public TableEntry
{
public:
	Node * node;
	int offset;
	VarTableEntry(Node *node, int offset) : node(node), offset(offset) {	}
};

class FuncTableEntry : public TableEntry
{
public:
	string id;
	Type_enum retType;
	vector<Node*> nodeList;

	FuncTableEntry(string id, Type_enum retType, vector<Node*> nodeList) :id(id), retType(retType), nodeList(nodeList) {	}
};

class VarTable : public Table //Scope table
{
public:
	vector<VarTableEntry*> rows;
	VarTable(bool is_while, Type_enum type) :Table(is_while, type) {}

	void push(VarTableEntry *entry)
	{
		rows.push_back(entry);
	}

	virtual void print_scope()
	{
		string t = "";
		for (int i = 0; i < this->rows.size(); i++)
		{
			t = get_type_string(rows[i]->node->type);
			if (rows[i]->node->isArray)
			{
				t = makeArrayType(t, rows[i]->node->arraySize);
			}
			printID(rows[i]->node->id, rows[i]->offset, t);
		}
	}
};

class FuncTable : public Table
{
public:
	vector<FuncTableEntry*> rows;
	FuncTable(bool is_while = false) :Table(is_while) {}

	void push(FuncTableEntry *entry)
	{
		rows.push_back(entry);
	}

	virtual void print_scope()
	{
		string t = "";
		vector<string> types;
		for (int i = 0; i < this->rows.size(); i++)
		{
			t = get_type_string(rows[i]->retType);
			for (int j = 0; j < rows[i]->nodeList.size(); j++)
			{
				if (rows[i]->nodeList[j]->isArray)
					types.push_back(makeArrayType(get_type_string(rows[i]->nodeList[j]->type), rows[i]->nodeList[j]->arraySize));
				else
					types.push_back(get_type_string(rows[i]->nodeList[j]->type));
			}
			t = makeFunctionType(t, types);

			printID(rows[i]->id, 0, t);

			types.clear();
		}
	}

};



#endif
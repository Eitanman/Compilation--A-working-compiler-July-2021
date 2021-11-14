#ifndef _util_
#define _util_

#define VOID_string "VOID"
#define FUNCTION_OFFSET 0
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stack>
#include <iostream>
#include "bp.hpp"

#define YYSTYPE Node*
using std::string;
using std::list;
using std::vector;
using std::map;
using std::stack;
using std::pair;


class parameter {
    std::string name;
    std::string type;

public:
    parameter(string n = "", string t = "") :name(n),type(t) {};
    parameter(const parameter& p): name(p.name), type(p.type){};
    string getName() {return name;}
    string getType() {return type;}
    void setName(string n) {this->name = n;}
    void setType(string t) {this->type = t;}

};


class Node {

public:
    virtual ~Node(){};
    virtual string getType(){return "";};
    virtual parameter* getPar(){parameter* p = new parameter(); return p; };
    virtual void setType(string t){std::cout<< "set type wrong: " << std::endl;};
    virtual bool isNumerical(){return true;};
    virtual void push_front(string type){};
    virtual vector<string>* getTypes(){vector<string>* v = new vector<string>(); return v;};
    virtual void setTypes(vector<string>* types){}
    virtual int getValue(){return 0;};
    virtual string getSTR(){return "";};
    virtual string getName(){return "";};
    virtual vector<string>& getArgTypes(){vector<string>* v = new vector<string>(); return *v;};
    virtual string getRetType(){return "";};
    virtual list<parameter>* getParList(){list<parameter>* p = new list<parameter>(); return p;};
    virtual void setParList(list<parameter>* p){};
	virtual void setReg(string s) {}
	virtual string getReg() { return ""; }
	virtual string getLabel(){std::cout << "Node getLabel" << std::endl; return "";}
	virtual string getDefaultLabel() { return ""; }
	virtual bool getDefaultFlag() { return true; }
	virtual void setNextList(vector<pair<int,BranchLabelIndex>> NL){std::cout << "Node setNextList" << std::endl;}
	virtual void setBreakList(vector<pair<int,BranchLabelIndex>> BL){}
	virtual vector<pair<int,BranchLabelIndex>> getBreakList(){return vector<pair<int,BranchLabelIndex>>();}
	virtual vector<pair<int,BranchLabelIndex>> getNextList(){std::cout << "Node getNextList" << std::endl;return vector<pair<int,BranchLabelIndex>>();}
	virtual void setTrueList(vector<pair<int,BranchLabelIndex>> TL){}
	virtual vector<pair<int,BranchLabelIndex>> getTrueList(){return vector<pair<int,BranchLabelIndex>>();}
	virtual void setFalseList(vector<pair<int,BranchLabelIndex>> FL){}
	virtual vector<pair<int,BranchLabelIndex>> getFalseList(){return vector<pair<int,BranchLabelIndex>>();}
	virtual stack<int>& getValueStack(){stack<int>* temp = new stack<int>(); return (*temp);}
	virtual stack<string>& getLabelStack(){stack<string>* temp = new stack<string>(); return (*temp);}
	virtual string getString(){return "";}
	virtual void setRegVector(vector<string>* VR){}
	virtual void push_front_reg(string reg) {}
	virtual vector<string>* getRegVector(){vector<string>* temp = new vector<string>(); return temp;}
	virtual vector<pair<int,BranchLabelIndex>> getConList(){return vector<pair<int,BranchLabelIndex>>();}
	virtual void setConList(vector<pair<int,BranchLabelIndex>> CL){}



};



class Formals : public Node {
	list<parameter>* par_list;
public:
    Formals(list<parameter>* pl = nullptr): par_list(pl)
    {
    	if (pl == nullptr)
		{
			par_list = new list<parameter>();
		}
    }

	list<parameter>* getParList();
    void setParList(list<parameter>* p){this->par_list = p;}
};
class FormalsList : public Node {
	list<parameter>* par_list;
public:
	FormalsList(list<parameter>* pl = nullptr): par_list(pl)
	{
		if (pl == nullptr)
		{
			par_list = new list<parameter>();
		}
	}
	list<parameter>* getParList();
    void setParList(list<parameter>* p){this->par_list = p;}
};
class FormalDecl : public Node {
	parameter* p;
	
public:
	FormalDecl(string name, string type)
	{
		this->p = new parameter(name,type);
	}
	parameter* getPar() { return p;}
};
class Type: public Node {
	string type;

public:
	Type(string s = ""): type(s) {}
	string getType() { return type; }
	void setType(string t)
	{
		string temp = t;
		this->type = temp;
	}
	virtual void setReg(string s) {}
	virtual string getReg() { return ""; }
};
class retType: public Type {

public:
	retType(string s): Type(s){}
	virtual void setReg(string s) {}
	virtual string getReg() { return ""; }
};
class Call: public retType {
	string reg;
public:
	Call(string s, string r = ""): retType(s), reg(r) {}
	void setReg(string s) { reg = s; }
	string getReg() { return reg; }
};
class VOID: public Type {
};
class Exp: public Node {
	string type;
	string reg;
public:
	vector<pair<int,BranchLabelIndex>> falseList;
	vector<pair<int,BranchLabelIndex>> trueList;
	Exp(string t = "", string r = ""):type(t),reg(r){}
	void setType(string t)
	{
		string temp = t;
		this->type = temp;
	}
	string getType() {return type;}
	bool isNumerical() { return (type == "INT") || (type == "BYTE");}
	string getReg () {return reg;}
	void setReg(string s) { reg = s; }
	void setTrueList(vector<pair<int,BranchLabelIndex>> TL){trueList = TL;}
	vector<pair<int,BranchLabelIndex>> getTrueList(){return trueList;}
	void setFalseList(vector<pair<int,BranchLabelIndex>> FL){falseList = FL;}
	vector<pair<int,BranchLabelIndex>> getFalseList(){return falseList;}


};
class IfExp: public Exp{
	
public:
	IfExp(): Exp("BOOL") {}
};
class ExpList: public Node {
	vector<string>* expTypes;
public:
	vector<string>* regVector;
	ExpList(vector<string>* vs = nullptr): expTypes(vs)
	{
		if(vs == nullptr)
		{
			expTypes = new vector<string>();
		}
	}
	void push_front(string type) {
		expTypes->insert(expTypes->begin(),type);
	}
	void push_front_reg(string reg) {
		regVector->insert(regVector->begin(),reg);
	}
	vector<string>* getTypes() {
		return expTypes;
	}
	void setTypes(vector<string>* types)
	{
		expTypes = types;
	}
	void setRegVector(vector<string>* VR){regVector = VR;}
	vector<string>* getRegVector(){return regVector;}
};
class NUM_t: public Node{
    int num;
    string num_str;
public:
    NUM_t(char* n): num(atoi(n)), num_str(string(n)){};
    NUM_t(string n): num(stoi(n)), num_str(n){};
    int getValue(){return num;}
    string getSTR() {return num_str;}
};
class ID_t: public Node{
    string name;
public:
    ID_t(string n): name(n){}
    ID_t(char* n): name(string(n)){}
    string getName() {return name;}
};
class PLUS_t: public Node {
	string command;
public:
	PLUS_t(string s) : command(s) {};
};


class Symbol {
	string name;
	string type;
	int offset;
public:
	Symbol(string n = "", string t = "",int o = 0) :name(n),type(t),offset(o) {};
    string getType() {return type;};
	string getName() {return name;};
	int getOffset() {return offset;};

};
class Function {
	string name;
	string retType;
	vector<string> argTypes;
public :
    Function(string n = "", string rt = "",const vector<string> args = vector<string>()):name(n),
		retType(rt), argTypes(args) {}
	vector<string>& getArgTypes() { return argTypes; }
	string getRetType() { return retType;}
	string getName() {return name;}
	
		
};

Symbol* findSymbol(vector<map<string,Symbol*>*>& symbol_vector,string name);


bool IDDefined(vector<map<string,Symbol*>*>& symbol_vector,string name);


void insertSymbol(vector<map<string,Symbol*>*>& symbol_vector,stack<int>& offset_stack,stack<vector<Symbol*>*>& symbol_stack,const string name,const string type);

// HW5


class L: public Node{
	string label;
public :
	L(string l): label(l) {}
	string getLabel(){ return label;}
};

class N: public Node{

public:
	vector<pair<int,BranchLabelIndex>> nextList;
	void setNextList(vector<pair<int,BranchLabelIndex>> NL){nextList=NL;}
	vector<pair<int,BranchLabelIndex>> getNextList(){return nextList;}
};

class R: public Node {
	string reg;
public:
	R(string r): reg(r) {}
	string getReg() { return reg; }
	void setReg(string s) { reg = s; }
};
class Statement: public Node{
public:
	vector<pair<int,BranchLabelIndex>> continueList;
	vector<pair<int,BranchLabelIndex>> nextList;
	vector<pair<int,BranchLabelIndex>> breakList;
	void setBreakList(vector<pair<int,BranchLabelIndex>> BL){breakList = BL;}
	vector<pair<int,BranchLabelIndex>> getBreakList(){return breakList;}
	void setNextList(vector<pair<int,BranchLabelIndex>> NL){nextList = NL;}
	vector<pair<int,BranchLabelIndex>> getNextList(){return nextList;}
	vector<pair<int,BranchLabelIndex>> getConList(){return continueList;}
	void setConList(vector<pair<int,BranchLabelIndex>> CL){continueList=CL;}
};

class Statements: public Node{
	
public:
	vector<pair<int,BranchLabelIndex>> continueList;
	vector<pair<int,BranchLabelIndex>> nextList;
	vector<pair<int,BranchLabelIndex>> breakList;
	void setBreakList(vector<pair<int,BranchLabelIndex>> BL){breakList = BL;}
	vector<pair<int,BranchLabelIndex>> getBreakList(){return breakList;}
	void setNextList(vector<pair<int,BranchLabelIndex>> NL){nextList=NL;}
	vector<pair<int,BranchLabelIndex>> getNextList(){return nextList;}
	vector<pair<int,BranchLabelIndex>> getConList(){return continueList;}
	void setConList(vector<pair<int,BranchLabelIndex>> CL){continueList=CL;}

};

class CaseList: public Node{
	string defaultLabel;
	bool defaultFlag;
public:
	vector<pair<int,BranchLabelIndex>> continueList;
	vector<pair<int,BranchLabelIndex>> nextList;
	vector<pair<int,BranchLabelIndex>> breakList;
	stack<int> value_stack;
	stack<string> label_stack;
	CaseList(vector<pair<int,BranchLabelIndex>> next, stack<int> values, stack<string> labels, string dLabel, bool flag):
		nextList(next), value_stack(values), label_stack(labels), defaultLabel(dLabel), defaultFlag(flag) {}
	string getDefaultLabel() { return defaultLabel; }
	bool getDefaultFlag() { return defaultFlag; }
	void setBreakList(vector<pair<int,BranchLabelIndex>> BL){breakList = BL;}
	vector<pair<int,BranchLabelIndex>> getBreakList(){return breakList;}
	void setNextList(vector<pair<int,BranchLabelIndex>> NL){nextList=NL;}
	vector<pair<int,BranchLabelIndex>> getNextList(){return nextList;}
	stack<int>& getValueStack(){return value_stack;}
	stack<string>& getLabelStack(){return label_stack;}
	vector<pair<int,BranchLabelIndex>> getConList(){return continueList;}
	void setConList(vector<pair<int,BranchLabelIndex>> CL){continueList=CL;}


};

class CaseDecl: public Node{
	int value;
	string label;
public:
	vector<pair<int,BranchLabelIndex>> continueList;
	vector<pair<int,BranchLabelIndex>> nextList;
	vector<pair<int,BranchLabelIndex>> breakList;
	CaseDecl(vector<pair<int,BranchLabelIndex>> next, int v, string s):
		nextList(next), value(v), label(s) {}
	int getValue() { return value; }
	string getLabel() { return label; }
	void setBreakList(vector<pair<int,BranchLabelIndex>> BL){breakList = BL;}
	vector<pair<int,BranchLabelIndex>> getBreakList(){return breakList;}
	void setNextList(vector<pair<int,BranchLabelIndex>> NL){nextList=NL;}
	vector<pair<int,BranchLabelIndex>> getNextList(){return nextList;}
	vector<pair<int,BranchLabelIndex>> getConList(){return continueList;}
	void setConList(vector<pair<int,BranchLabelIndex>> CL){continueList=CL;}

};

class STRING_t: public Node {
public:
	string s;
	STRING_t(string str = ""): s(str) {}
	string getString(){return s;}
};

string genReg();
string genSTR();




#endif
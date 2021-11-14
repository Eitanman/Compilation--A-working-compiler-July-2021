#include "utility.hpp"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

list<parameter>* Formals::getParList()
{
    return par_list;
}

list<parameter>* FormalsList::getParList()
{
    return par_list;
}


Symbol* findSymbol(vector<map<string,Symbol*>*>& symbol_vector,string name) {
    for (unsigned int i=0; i<symbol_vector.size();i++) {
        if (symbol_vector[i]->find(name) != symbol_vector[i]->end()) {
            return (*symbol_vector[i])[name];
        }
    }
    return nullptr;
}

bool IDDefined(vector<map<string,Symbol*>*>& symbol_vector,string name) {
    for (unsigned int i=0; i<symbol_vector.size();i++) {
        if (symbol_vector[i]->find(name) != symbol_vector[i]->end()) {
            return true;
        }
    }
    return false;
}
void insertSymbol(vector<map<string,Symbol*>*>& symbol_vector,stack<int>& offset_stack,stack<vector<Symbol*>*>& symbol_stack,const string name,const string type) {
    Symbol* new_symbol = new Symbol(name,type,offset_stack.top());
    (*symbol_vector[symbol_vector.size()-1])[name] = new_symbol;
    offset_stack.top()++;
    symbol_stack.top()->push_back(new_symbol);

}

string genReg() {
	static unsigned int reg_num = 0;
	std::stringstream reg;
	reg << "%var";
	reg << reg_num++;
	std::string ret(reg.str());
	return ret;
}

string genSTR() {
	static unsigned int str_num = 0;
	std::stringstream s;
	s << "string";
	s << str_num++;
	std::string ret(s.str());
	return ret;
}	
#ifndef VARIABLE_H
#define VARIABLE_H
#include <vector>
#include <string>
using std::string;
#include "term.h"
#include "atom.h"
#include "number.h"
#include "struct.h"
class Variable : public Term{
public:
	string _symbol;
	Variable(string v) : _symbol(v),_value(v){}
	string symbol() const { return _symbol;}
	string value() const {
		if(_structAssignable) {
			return _struct->value();
			
		}
		return _value;
	}

	bool getassignable();

	//bool match(Atom &atom);
	
	//bool match(Number &num);

	bool match(Term &term);

	void cp(Variable *ps);

	std::vector<Variable *> _args;
private:
	
	string _value;
	bool _assignable = true;
	//std::vector<Variable *> _args;
	Struct *_struct;
	bool _structAssignable = false;
};



#endif
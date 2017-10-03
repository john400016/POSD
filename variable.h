#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
using std::string;

class Atom;
class Number;

class Variable{
public:
	string _value;
	Variable(string s);
	//string symbol();
	string value();

	string getValue();

	void setValue(string key);

	bool getAssignable();

	void setAssignable(bool key);

	bool match(Atom atom);

	bool match(Number num);


private:
	string _symbol;
	//string _value;
	bool _assignable = true;

};



#endif
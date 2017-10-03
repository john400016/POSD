#ifndef ATOM_H
#define ATOM_H

#include <string>
using std::string;

class Number;
class Variable;

class Atom{
public:

	Atom(string v);
	string symbol();

	bool match(Number num);

	bool match(Variable &v);


private:
	string _symbol;
	

};





#endif
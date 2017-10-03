#ifndef NUMBER_H
#define NUMBER_H

#include <string>
using namespace std;

class Atom;
class Variable;

class Number{
public:

	Number(string s, int v);
	string value();
	string symbol();

	bool match(Number num);

	bool match(Atom atom);

	bool match(Variable &variable);

private :
	int _value;
	string _symbol;

};



#endif
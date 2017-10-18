#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"

using namespace std;
class Atom : public Term{
public:

	Atom (string s) : _symbol(s){}

	string symbol () const{ return _symbol; }

	bool match(Term &term);
private:
	string _symbol;
};

#endif
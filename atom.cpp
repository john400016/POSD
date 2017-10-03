#include "atom.h"
#include "variable.h"
#include "number.h"

#include <string>
using std::string;

Atom :: Atom(string s) : _symbol(s){}
string Atom :: symbol(){ return _symbol; }

bool Atom :: match(Number num){ return false; }

bool Atom :: match(Variable &v){ 

	if(v.getAssignable() || v.value() == _symbol){
		v.setValue(_symbol);
		v.setAssignable(false);
		return true;
	}
	return false;
}

#include "variable.h"
#include "atom.h"
#include "number.h"

#include <sstream>
#include <string>
using namespace std;

Number :: Number(string s, int v) : _symbol(s), _value(v){}
string Number :: value(){
	
	std :: stringstream ss;
	ss << _value;

	return ss.str();
}
string Number :: symbol(){return _symbol;}


bool Number :: match(Number num){ 

	std :: stringstream snum;
	snum << _value;

	return snum.str() == num.value();
}


bool Number :: match(Atom atom){ return false; }


bool Number :: match(Variable &variable){

	std :: stringstream svar;
	svar << _value;

	if(variable.getAssignable() || svar.str() == variable.value()){
		variable.setValue(svar.str());
		variable.setAssignable(false);
		return true;
	}
	return false;
}

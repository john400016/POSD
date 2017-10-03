#include "number.h"
#include "variable.h"
#include "atom.h"

#include <string>
using std::string;

Variable :: Variable(string v) : _value(v){}
//string symbol(){ return _symbol;}
string Variable :: value(){ return _value;}


string Variable :: getValue(){
		return _value;
}

void Variable :: setValue(string key){
		_value = key;
}

bool Variable :: getAssignable(){
		return _assignable;
}

void Variable :: setAssignable(bool key){
		_assignable = key;
}

bool Variable :: match(Atom atom){ 
	if(_assignable || atom.symbol() == _value){
		_value = atom.symbol();
		_assignable = false;
		return true;
	}
	return false;
}
	
bool Variable :: match(Number num){ 
	if(_assignable || num.value() == _value){
		_value = num.value();
		_assignable = false;
		return true;
	}
	return false;
}

#include "variable.h"
#include "atom.h"
#include "number.h"
#include "term.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool Variable :: getassignable(){
	return _assignable;
}

/*bool Variable :: match(Atom &atom){ 
	if(_assignable || atom.symbol() == _value){
		_value = atom.symbol();
		_assignable = false;
		return true;
	}
	return false;
}
	
bool Variable :: match(Number &num){ 
	if(_assignable || num.value() == _value){
		_value = num.value();
		_assignable = false;
		return true;
	}
	return false;
}

bool Variable :: match(Variable &var){

	Variable * ps = dynamic_cast<Variable *>(&var);
	bool ret = _assignable;
	if(ps){
		if(_assignable && var._assignable){
			_value = var.value();
			_args.push_back(&(var));
			var._args = _args;
			return true;
		}else if(!_assignable && var._assignable){
			for(int i = 0 ;i < var._args.size() ; i++){
				var._args[i]->value() = _value;
			}
			var._assignable = false;
		}else if(_assignable && !var._assignable){
			for(int i = 0 ;i < var._args.size() ; i++){
				_args[i]->value() = var.value();
			}
			_assignable = false;
		}else{
			return (_value == var.value());
		}
	}
	return false;
}*/
bool Variable ::match(Term &term) {
	Variable *ps = dynamic_cast<Variable *>(&term);
	Struct *pt = dynamic_cast<Struct *>(&term);
	if(ps) {
		if(_assignable && ps->_assignable){
			_value = term.value();
			cp(ps);
			return true;
		}else if(!_assignable && ps->_assignable){

			cp(ps);			
			for(int i = 0; i < _args.size(); i++){
				_args[i]->_value = _value;
				_args[i]->_assignable = false;
			}
			return true;
		}else if(_assignable && !ps->_assignable){
			cp(ps);
			for(int i = 0; i < ps->_args.size(); i++){
				ps->_args[i]->_value = ps->_value;
				ps->_args[i]->_assignable = false;
			}
			cp(ps);
			return true;
		}else{
			return false;
		}
		

	}
	if(pt) {
		if(!_structAssignable || _value == pt->value()) {
			_struct = pt;
			_structAssignable = true;
			return true;
		}
		return false;
	}
	bool ret = _assignable;
	if(ret || _value == term.value()) {

		_value = term.value();
		_assignable = false;
		ret = true;

		for(int i = 0; i < _args.size(); i++){
			_args[i]->_value = _value;
			_args[i]->_assignable = false;
		}
	}
	return ret;
}

void Variable :: cp(Variable *ps){
	for(int i = 0; i < ps->_args.size(); i++){
		_args.push_back(ps->_args[i]);
	}
	for(int i = 0; i < _args.size(); i++){
		ps->_args.push_back(_args[i]);
	}
	for(int i = 0; i < _args.size() ; i++){
		_args[i]->_args.push_back(ps);		
	}
	_args.push_back(ps);
	ps->_args.push_back(this);	
}


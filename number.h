#ifndef NUMBER_H
#define NUMBER_H

#include <sstream>
#include <string>
using namespace std;
#include "term.h"

class Number : public Term{
public:

	Number(double v) : _value(v){}
	Number(string s) : _symbol(s){}
	string value() const{
	
		stringstream ss;
		ss << _value;
		return ss.str();
	}

	string symbol() const{
	
		stringstream ss;
		ss << _value;
		return ss.str();
	}


private :
	double _value;
	string _symbol;

};



#endif
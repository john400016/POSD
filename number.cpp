#include "number.h"
#include "variable.h"

#include <string>
using namespace std;

bool Number :: match(Term &term) {
	Variable *ps = dynamic_cast<Variable *>(&term);
	if(ps)
		return ps->match(*this);
	return value() == term.value();
}
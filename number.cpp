#include "number.h"
#include "variable.h"
#include "list.h"
#include <string>
using namespace std;

bool Number :: match(Term &term) {
	Variable *ps = dynamic_cast<Variable *>(&term);
	List *pl = dynamic_cast<List *>(&term);
	if(ps)
		return ps->match(*this);
	if(pl)
		return false;
	return value() == term.value();
}
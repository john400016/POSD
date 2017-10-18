#include "atom.h"
#include "variable.h"
#include <string>
using std::string;

	
bool Atom :: match(Term &term) {
		Variable *ps = dynamic_cast<Variable *>(&term);
		if(ps)
			return ps->match(*this);
		return value() == term.value();
}
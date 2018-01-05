#include "atom.h"
Atom::Atom(std::string s):
    _symbol(s) 
{

}  
bool Atom::match(Term &term)
{
    Variable *var = dynamic_cast<Variable*>(&term);
    if(var)
        return var->match(*this);
    return _symbol == term.symbol();
}
std::string Atom::symbol() const
{
    return _symbol;
}

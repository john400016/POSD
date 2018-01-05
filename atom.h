#ifndef ATOM_H
#define ATOM_H
#include "term.h"
#include "variable.h"
class Atom : public Term
{
public:
    Atom (std::string s);
    bool match(Term &term);
    std::string symbol() const;
private:
    std::string _symbol;
};
#endif

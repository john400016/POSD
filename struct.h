#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include <string>
#include "atom.h"
template<class Item>
class Iterator;
class Struct : public Term
{
public:
    Struct(Atom const &name, std::vector<Term *> args);
    Term * args(int index);
    void setArg(int index, Term* term); //For parser.
    int arity() const;
    Atom const& name() const;
    std::string value() const;
    std::string symbol() const;
    bool match(Term &term);
    Iterator<Term*> *createIterator();
    Iterator<Term*> *createDFSIterator();
    Iterator<Term*> *createBFSIterator();
private:
    Atom const _name;
    std::vector<Term *> _args;
};
#endif

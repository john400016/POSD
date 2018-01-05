#ifndef TERM_H
#define TERM_H

#include <string>
template<class Item>
class Iterator;
class Term
{
public:
    virtual std::string symbol() const = 0;
    virtual bool match(Term &term) = 0;
    virtual std::string value() const;
    virtual void setArg(int i, Term *term);
    virtual Iterator<Term*>* createIterator();
    virtual Iterator<Term*>* createDFSIterator();
    virtual Iterator<Term*>* createBFSIterator();
};

#endif

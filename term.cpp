#include "term.h"
#include "iterator.h"
std::string Term::value() const
{
    return symbol();
}

void Term::setArg(int i, Term *term)
{
    
}

Iterator<Term*>* Term::createIterator()
{
    return new NullIterator<Term*>(this);
}

Iterator<Term*>* Term::createDFSIterator()
{
    return new NullIterator<Term*>(this);
}

Iterator<Term*>* Term::createBFSIterator()
{
    return new NullIterator<Term*>(this);
}

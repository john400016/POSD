#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "variable.h"

#include <vector>
#include <memory>

using std::vector;
template<class Item>
class Iterator;
class List : public Term
{
public:
    List();
    List(vector<Term *> const & elements);
    Term* head() const;
    List* tail() const;
    std::string symbol() const;
    std::string value() const;
    bool match(Term &term);

//These three functions are for parser when parsing the expression.
    int   arity();
    Term* args(int index);
    void  setArg(int index, Term* term);

    Iterator<Term*> *createIterator();
    Iterator<Term*> *createDFSIterator();
    Iterator<Term*> *createBFSIterator();

private:
    bool matchListDiffVar(List *list);
    vector<Term*> _elements;
};
#endif

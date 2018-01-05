#include "list.h"
#include "iterator.h"
List::List()
    : _elements()
{

}
List::List(vector<Term*> const &elements)
    : _elements(elements)
{

}
Term* List::head() const
{
    if(_elements.empty())
        throw std::string("Accessing head in an empty list");
    else
        return _elements[0];
}
List* List::tail() const
{
    if(_elements.empty())
        throw std::string("Accessing tail in an empty list");
    else
    {
        std::vector<Term*> v(_elements.begin() + 1, _elements.end());
        return new List(v);
    }
}
std::string List::value() const
{
    std::string sym_name;
    if(_elements.empty())
        return "[]";
    sym_name += '[';
    for(size_t i=0;i<_elements.size()-1;i++)
    {
        sym_name += _elements[i]->value();
        sym_name += ", ";
    }
    sym_name += _elements[_elements.size() - 1]->value();
    sym_name += ']';
    return sym_name;
}
std::string List::symbol() const
{
    std::string sym_name;
    if(_elements.empty())
        return "[]";
    sym_name += '[';
    for(size_t i=0;i<_elements.size()-1;i++)
    {
        sym_name += _elements[i]->symbol();
        sym_name += ", ";
    }
    sym_name += _elements[_elements.size() - 1]->symbol();
    sym_name += ']';
    return sym_name;
}
bool List::match(Term &term)
{
    Variable *var = dynamic_cast<Variable*>(&term);
    List *list = dynamic_cast<List*>(&term);
    if(var)
        return var->match(*this);
    else if(list)
        return matchListDiffVar(list);
    return symbol() == term.symbol();
}
bool List::matchListDiffVar(List *list)
{
    Variable *var1, *var2;
    if(list->_elements.size() != _elements.size())
        return false;
    for(size_t i=0; i<_elements.size(); i++)
    {
        var1 = dynamic_cast<Variable*>(_elements[i]);
        var2 = dynamic_cast<Variable*>(list->_elements[i]);
        if(var1 && var2 &&
                !(var1->symbol() == var1->value() &&
                    var2->symbol() == var2->value()))
        {
            return false;
        }
        else if(var1 == nullptr && var2)
        {
            bool ret = var2->match(*list->_elements[i]);
            if(!ret)
                return false;
        }
        else if(var2 == nullptr && var1)
        {
            bool ret = var1->match(*list->_elements[i]);
            if(!ret)
                return false;
        }
        else if(!var1 && !var2 &&
           _elements[i]->symbol() != list->_elements[i]->symbol())
        {
            return false;
        }
    }
    return true;
}
int   List::arity()
{
    return _elements.size();
}
Term* List::args(int index)
{
    return _elements[index];
}
void  List::setArg(int index, Term* term)
{
    _elements[index] = term;
}

Iterator<Term*> *List::createIterator()
{
    return new ListIterator<Term*>(this);
}

Iterator<Term*> *List::createDFSIterator()
{
    return new DFSIterator<Term*>(this);
}

Iterator<Term*> *List::createBFSIterator()
{
    return new BFSIterator<Term*>(this);
}

#include "struct.h"
#include "iterator.h"
Struct::Struct(Atom const &name, std::vector<Term *> args)
    : _name(name), _args(args)
{

}
Term * Struct::args(int index)
{
    return _args[index];
}
void Struct::setArg(int index, Term *term)
{
    _args[index] = term;
}
int Struct::arity() const
{
    return _args.size();
}
Atom const& Struct::name() const
{
    return _name;
}
std::string Struct::value() const
{
    std::string sym_name(_name.symbol());
    if(_args.empty())
        return sym_name + "()";
    sym_name += '(';
    for(size_t i=0;i<_args.size()-1;i++)
    {
        sym_name += _args[i]->value();
        sym_name += ", ";
    }
    sym_name += _args[_args.size() - 1]->value();
    sym_name += ')';
    return sym_name;
}
std::string Struct::symbol() const
{
    std::string sym_name(_name.symbol());
    if(_args.empty())
        return sym_name + "()";
    sym_name += '(';
    for(size_t i=0;i<_args.size()-1;i++)
    {
        sym_name += _args[i]->symbol();
        sym_name += ", ";
    }
    sym_name += _args[_args.size() - 1]->symbol();
    sym_name += ')';
    return sym_name;
}
bool Struct::match(Term &term)
{
    Variable *var = dynamic_cast<Variable*>(&term);
    if(var)
        return var->match(*this);
    return symbol() == term.symbol();
}

Iterator<Term*> *Struct::createIterator()
{
    return new StructIterator<Term*>(this);
}

Iterator<Term*> *Struct::createDFSIterator()
{
    return new DFSIterator<Term*>(this);
}

Iterator<Term*> *Struct::createBFSIterator()
{
    return new BFSIterator<Term*>(this);
}

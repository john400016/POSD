#ifndef VARIABLE_H
#define VARIABLE_H
#include "atom.h"
#include "list.h"
#include <vector>
#include <sstream>
class Variable : public Term
{
public:
    Variable(std::string s);
    std::string value() const;
    std::string symbol() const;
    bool match(Term &term);
    std::string const _symbol;
    Variable& operator=(Variable const& var);
private:
    void add_shared_var(Variable *var);
    void instantiate_shared_var(Term *_nvalue);
    bool checkInsideList(Term const *term) const;
    Term * _value;
    std::vector<Variable*> _sharedlist;
    bool _instantiated;
};
#endif

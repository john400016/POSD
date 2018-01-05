#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED
#include <string>
#include <sstream>
#include <iomanip>
#include "term.h"
#include "variable.h"
class Number : public Term
{
public:
    Number(int v);
    Number(double v);
    Number(std::string symbol);
    bool match(Term &term);
    std::string symbol() const;
private:
    std::string _symbol;
};
#endif

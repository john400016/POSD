#include "global.h"
#include "iterator.h"
std::vector<std::pair<std::string, int>> symtable;
Context _context;
bool isSpecialCh(char c)
{
  return c == '+'
      // || c == '=' // ... the matching operator
         || c == '-'
         || c == '*'
         || c == '_'
         || c == '/'
         || c == '<'
         || c == '>'
         || c == '.'
         || c == '&'
         || c == '\\'
         || c == '~'
         || c == '^'
         || c == '$'
         || c == '#'
         || c == '@'
         || c == '?'
         || c == ':';
}

bool symbolExist(std::string s, int & val)
{
    bool found = false;
    val = -1;
    std::vector<std::pair<std::string, int>>::iterator it =
        find_if(symtable.begin(), symtable.end(),
                [s](std::pair<std::string, int> ele)
                {
                    return ele.first == s;
                });
    found = symtable.end() != it;
    if (found)
        val = it - symtable.begin();
    return found;
}

bool termExist(Context *context, std::string s, Term **term)
{
    bool found = false;
    *term = nullptr;
    std::vector<std::pair<std::string, Term*>>::iterator it =
        find_if(context->begin(), context->end(),
                [s](std::pair<std::string, Term*> ele)
                {
                    return ele.first == s;
                });
    found = context->end() != it;
    if (found)
        *term = it->second;
    return found;
}

void termAddToContext(Context *context, Term &term)
{
    int i;
    Term* t;
    Iterator<Term*> *it = term.createIterator();
    i = 0;
    for(it->first();!it->isDone();i++, it->next())
    {
        t = it->currentItem();
        if(!termExist(context, t->symbol(), &t))
            termAddToContext(context, *it->currentItem());
        else
            term.setArg(i, t);
    }
    context->push_back(std::pair<std::string, Term*>(term.symbol(), &term));
}

void printSymbolTable()
{
    for(size_t i=0;i<symtable.size();i++)
    {
        printf("[%zd] -> %s, %d\n", i, symtable[i].first.c_str(), symtable[i].second);
    }
}

#ifndef LIST_H
#define LIST_H

#include <vector>
#include "term.h"
#include <vector>
using namespace std;


class List : public Term {
public:
    
    string symbol() const;
    string value() const;
    bool match(Term & term);

    List (): _elements() {}
    List (std ::vector<Term *> const & elements):_elements(elements){}
   
    Term * head() const;
    List * tail() const;

    int eleSize(){ return _elements.size();}
    string getEle(int index){ return _elements[index]->value();}
	
private:
    std::vector<Term *> _elements;

};

#endif

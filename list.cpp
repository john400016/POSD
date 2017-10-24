#include "list.h"
#include "variable.h"
#include <string>
using namespace std;

string List::symbol() const{
    if(!_elements.size()){
        return "[]";
    }
    string ret = "[";
    for(int i = 0; i < _elements.size() -1 ; i++){
        ret += _elements[i]-> symbol() + ", ";
    }
    ret += _elements[_elements.size() -1] -> symbol() + "]";
    return ret;
}

string List::value() const{
    if(!_elements.size()){
        return "[]";
    }
    string ret = "[";
    for(int i = 0; i < _elements.size() -1 ; i++){
        ret += _elements[i]-> value() + ", ";
    }
    ret += _elements[_elements.size() -1] -> value() + "]";
    return ret;
}

bool List::match(Term & term){
    List * pl = dynamic_cast<List *>(&term);
    Variable * pv = dynamic_cast<Variable *>(&term);
    if (pl){
        if(_elements.size()!= pl->_elements.size())
            return false;
        for(int i = 0;i < _elements.size() ;i++){
            bool ret = _elements[i] -> match(*(pl -> _elements[i]));
            if(!ret)
                return false;
        }
        return true;
    }

    if(pv){
        return pv->match(*this);
    }    
    return false;
}

Term * List::head() const{ 
        if(!_elements.size())
            throw  string("Accessing head in an empty list");

    return _elements[0];
}

List * List::tail() const{
    if(!_elements.size())
    throw  string("Accessing tail in an empty list");
    std ::vector<Term *> v = {};
    for(int i =1; i < _elements.size();i++){
        v.push_back(_elements[i]);
    }
    List * l = new List(v);
    return l;
}
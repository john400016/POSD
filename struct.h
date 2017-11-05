#ifndef STRUCT_H
#define STRUCT_H

#include "list.h"
#include "term.h"
#include "atom.h"
#include <vector>
#include <string>

using std::string;

class Struct:public Term
{
public:
    Struct(Atom const & name, std::vector<Term *> args):_name(name), _args(args) {
    }//建立一個struct 名字為name，內容物為_args[] 

    Term * args(int index) {
        return _args[index];
      }

    int arity(){
        return _args.size();
    }

    Atom const &name() {
        return _name;
    }

    string value() const{
        string ret =_name.value() + "(";
        for(int i = 0; i < _args.size() - 1 ; i++){
            ret += _args[i]-> value() + ", ";
        }
        ret += _args[_args.size()-1]-> value() + ")";
        return  ret;
    }

    string symbol() const{
        string ret =_name.symbol() + "(";
        if ( _args.empty()){
            ret +=  ")";
            return  ret;
        }
        for(int i = 0; i < _args.size() - 1 ; i++){
            ret += _args[i]-> symbol() + ", ";
        }
        ret += _args[_args.size()-1]-> symbol() + ")";
        return  ret;
    }

    bool match(Term &term){
        Struct * ps = dynamic_cast<Struct *>(&term);
        if (ps){
            if (!_name.match(ps->_name))
                return false;
            if(_args.size()!= ps->_args.size())
                return false;
            for(int i=0;i<_args.size();i++){
                if(_args[i]->symbol() != ps->_args[i]->symbol())
                return false;
            }
            return true;
            }
        return false;
    }



private:
    Atom _name;
    std::vector<Term *> _args;
};

#endif

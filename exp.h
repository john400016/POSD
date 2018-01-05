#ifndef EXP_H
#define EXP_H

#include "atom.h"
#include "global.h"
#include <set>
std::vector<std::string> expStringToArray(std::string s);
std::string subSame(std::string s1, std::string s2);
class Exp {
public:
  virtual bool evaluate() = 0;
  virtual std::string symbol() const = 0;
};

class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    Term *t;
    if(termExist(&_context, _left->symbol(), &t))
      _left = t;
    else
      termAddToContext(&_context, *_left);
    if(termExist(&_context, _right->symbol(), &t))
      _right = t;
    else
      termAddToContext(&_context, *_right);

    return _left->match(*_right);
  }

  std::string symbol() const{
    if(_left->symbol() == _right->symbol())
      return "true";
    if(!_left->match(*_right))
      return "";
    return _left->symbol() + " = " + _right->value();
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

  std::string symbol() const{
    if(!(_left->evaluate() && _right->evaluate()))
      return "";
    if(_left->symbol() == _right->symbol())
      return _left->symbol();
    if(_left->symbol() == "true")
      return _right->symbol();
    if(_right->symbol() == "true")
      return _left->symbol();
    // return _left->symbol() + ", " + _right->symbol();
    std::string o = subSame(_left->symbol(), _right->symbol());
    std::string a = _left->symbol() + ", " + _right->symbol();
    if(o.empty())
      return a;
    else if(o.length() < a.length())
      return o;
    else
      return a;
    // return subSame(_left->symbol(), _right->symbol());
  }

private:
  Exp * _left;
  Exp * _right;
  std::set<std::string> _duplicateExp;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    bool ret;
    ret = _left->evaluate();
    _context.clear();
    ret = ret || _right->evaluate();
    return ret;
  }

  std::string symbol() const{
    std::string c = "; ";
    std::string symleft;
    std::string symright;
    symleft  = _left->symbol();
    symright = _right->symbol();
    if(symleft.empty() || symright.empty())
      c.clear();
    return _left->symbol() + c + _right->symbol();
  }

private:
  Exp * _left;
  Exp * _right;
};
#endif

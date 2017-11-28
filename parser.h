#ifndef PARSER_H
#define PARSER_H
#include <string>
using namespace std;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "utParser.h"
#include <iostream>

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      Term *term = new Variable(symtable[_scanner.tokenValue()].first);
      if(check(pos, term))
        term = sameTerm[pos];
      else
        sameTerm.push_back(term);
      return term;
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    } else if(token == '=') {
      _node.push_back(new Node(EQUALITY));
    } else if(token == ',') {
      _node.push_back(new Node(COMMA));
    } else if(token == ';') {
      _node.push_back(new Node(SEMICOLON));
      sameTerm.clear();
    }

    return nullptr;
  }

  

  

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  Node * expressionTree() { 
    return root; 
  }  

  void matchings() {
    Term *term;
    while(_scanner.currentChar() != EOS) {
      if(_scanner.currentChar() == '.')
        break;
      if(term = createTerm()) {
        _terms.push_back(term);
        _node.push_back(new Node(TERM, term, nullptr, nullptr));
      }
    }
    inToPost();
    vector<Node *>stack;
    for(int i = 0; i < _post.size(); i++) {
      if(_post[i]->payload == TERM)
        stack.push_back(_post[i]);
      else {
        _post[i]->right = stack.back();
        stack.pop_back();
        _post[i]->left = stack.back();
        stack.pop_back();
        stack.push_back(_post[i]);
      }
    }
    root = stack[0];
  }


private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  int pos;
  Node *root;
  vector<Node *>_node, _post;
  vector<Term *> sameTerm;

  bool check(int &pos, Term *term) {
    for(int i = 0; i < sameTerm.size(); i++) {
      if(term->symbol() == sameTerm[i]->symbol()) {
        pos = i;
        return true;
      }
    }
    return false;
  }

  int priority(Operators op) {
    switch(op) {
      case EQUALITY:
        return 2;
      case COMMA:
        return 1;
      case SEMICOLON:
        return 1;
      default:
        return 0;
    }
  }

  void inToPost() {
    vector<Node *>stack;
    for(int i = 0; i < _node.size(); i++) {
      if(priority(_node[i]->payload) == 0) {
        _post.push_back(_node[i]);
      } else if(stack.empty() && priority(_node[i]->payload) != 0) {
        stack.push_back(_node[i]);
      } else if(priority(_node[i]->payload) < priority(stack.back()->payload)) {
        _post.push_back(stack.back());
        stack.pop_back();
        stack.push_back(_node[i]);
      } else if(priority(_node[i]->payload) > priority(stack.back()->payload)) {
        stack.push_back(_node[i]);
      }
    }
    for(;!stack.empty();){
      _post.push_back(stack.back());
      stack.pop_back();
    }  
  }
};
#endif
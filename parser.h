#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "term.h"
#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}

  	Term* createTerm(){

		int token = _scanner.nextToken();
    	if(token == VAR){
    	  	return new Variable(symtable[_scanner.tokenValue()].first);
    	}else if(token == NUMBER){
    	  	return new Number(_scanner.tokenValue());
    	}else if(token == ATOM || token == ATOMSC){
			vector<Term*> terms = {};
			Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
			if( _scanner.currentChar() == '(' ){
				_scanner.nextToken();
				if( _scanner.currentChar() == ')'){
					_scanner.nextToken();
					return new Struct(*atom, terms);
				}else if(_scanner.currentChar() != ')'){
					terms = getArgs();
					if(_currentToken == ')'){
						return new Struct(*atom, terms);
					}
				}
			}else
          		return atom;
    	}else if(token == '['){
			vector<Term*> terms = {};
			_scanner.skipLeadingWhiteSpace();
			if( _scanner.currentChar() != ']' ){
				terms = getArgs();
				if( _currentToken == ']'){
					return new List(terms);
				}else{
					throw string("unexpected token");
				}
			}else if( _scanner.currentChar() == ']' ){
				_scanner.nextToken();
				return new List(terms);
			}
        }
    	return nullptr;
  	}

  	vector<Term*> getArgs(){
    	Term* term = createTerm();
    	vector<Term*> args;
    	if(term)
      		args.push_back(term);
    	while((_currentToken = _scanner.nextToken()) == ',') {
      		args.push_back(createTerm());
    	}
    	return args;
  	}



private:
  	Scanner _scanner;
  	int _currentToken;
};
#endif

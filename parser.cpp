#include "parser.h"
Parser::Parser(Scanner scanner)
  : _scanner(scanner), _terms()
{

}
Term* Parser::createTerm(){
  int token = _scanner.nextToken();
  _currentToken = token;
  if(token == VAR){
    return new Variable(symtable[_scanner.tokenValue()].first);
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
  }

  return nullptr;
}



Term * Parser::structure() {
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
    throw string("Unbalanced operator");
  }
}

Term * Parser::list() {
  int startIndexOfListArgs = _terms.size();
  createTerms();
  if(_currentToken == ']')
  {
    vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
    _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
    if(args.size()==0){
      return new Atom("[]");
    }
    return new List(args);
  } else {
    throw string("Unbalanced operator");
  }
}

vector<Term *> & Parser::getTerms() {
  return _terms;
}

void Parser::buildExpression(){
  // createTerm();
  disjunctionMatch();
  restDisjunctionMatch();
  if (createTerm() != nullptr || _currentToken != '.')
    throw string("Missing token '.'");
}

void Parser::restDisjunctionMatch() {
  if (_scanner.currentChar() == ';') {
    createTerm();
    disjunctionMatch();
    Exp *right = _expStack.top();
    _expStack.pop();
    Exp *left = _expStack.top();
    _expStack.pop();
    _expStack.push(new DisjExp(left, right));
    restDisjunctionMatch();
  }
}

void Parser::disjunctionMatch() {
  conjunctionMatch();
  restConjunctionMatch();
}

void Parser::restConjunctionMatch() {
  if (_scanner.currentChar() == ',') {
    createTerm(); //Eat ','
    conjunctionMatch();
    Exp *right = _expStack.top();
    _expStack.pop();
    Exp *left = _expStack.top();
    _expStack.pop();
    _expStack.push(new ConjExp(left, right));
    restConjunctionMatch();
  }
}

void Parser::conjunctionMatch() {
  Term *left, *term;
  char prevChar = static_cast<char>(_currentToken);
  left = createTerm();
  if(left == nullptr)
  {
    throw std::string("Unexpected \'") + prevChar +
      + "\'" +  " before \'" + (char)_currentToken + "\'";
  }
  else if ((term = createTerm()) == nullptr && _currentToken == '=') {
     Term * right = createTerm();
    _expStack.push(new MatchExp(left, right));
  }
  else if(term == nullptr && _currentToken == '.')
  {
    throw std::string(left->symbol()) + " does never get assignment";
  }
  else if(_scanner.currentChar() == '.')
  {
    throw std::string("Unexpected \'") + (char)_currentToken
      + "\'" +  " before \'" + _scanner.currentChar() + "\'";
  }
}

Exp* Parser::getExpressionTree(){
  ::_context.clear();
  return _expStack.top();
}

std::vector<Exp*> Parser::getTreeContext(){
  return _context;
}

void  Parser::createTerms() {
 Term* term = createTerm();
 if(term!=nullptr)
 {
   _terms.push_back(term);
   while((_currentToken = _scanner.nextToken()) == ',') {
     _terms.push_back(createTerm());
   }
 }
}

#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "exp.h"
#include <stack>
#ifndef FRIEND_TEST
    #include <gtest/gtest_prod.h>
#endif
using std::stack;

class Parser
{
public:
  Parser(Scanner scanner);
  Term* createTerm();
  Term * structure();
  Term * list();
  vector<Term *> & getTerms();
  void buildExpression();
  void restDisjunctionMatch();
  void disjunctionMatch();
  void restConjunctionMatch();
  void conjunctionMatch();
  Exp* getExpressionTree();
  std::vector<Exp*> getTreeContext();
private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest, ListOfTermsEmpty);
  FRIEND_TEST(ParserTest, listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
  FRIEND_TEST(ParserTest, createTerms);
  void createTerms();
  Scanner _scanner;
  vector<Term *> _terms;
  std::vector<Exp*> _context;
  int _currentToken;
  //MatchExp* _root;
  stack<Exp*> _expStack;
};
#endif

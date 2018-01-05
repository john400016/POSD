#include "shell.h"
std::string PrologShell::execute(std::string input)
{
  Scanner scanner(input);
  Parser parser(scanner);
  parser.buildExpression();
  return execute(parser.getExpressionTree());
}
std::string PrologShell::execute(Exp *exp)
{
  bool ret;
  std::string output;
  ret = exp->evaluate();
  if(ret)
    output += exp->symbol();
  else
    output += "false";
  output += '.';
  return output;
}
std::string PrologShell::execute(std::vector<Exp*> context)
{
  bool ret;
  std::string output;
  for(size_t i=0;i<context.size();i++)
  {
    ret = context[i]->evaluate();
    if(ret)
      output += context[i]->symbol();
    else
      output += "false";
  }
  output += '.';
  return output;
}

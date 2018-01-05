#ifndef SHELL_H
#define SHELL_H
#include "parser.h"
#include "exp.h"
#include <vector>
class PrologShell
{
public:
  std::string execute(std::string input);
  std::string execute(Exp *exp);
  std::string execute(std::vector<Exp*> context);
private:
  FRIEND_TEST(ShellTest, exceptionMissingPeriodToken);

};
#endif

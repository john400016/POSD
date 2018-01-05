#ifndef SCANNER_H
#define SCANNER_H

#include "global.h"

#include <string>
#include <vector>
class Scanner
{
public:
    Scanner (std::string in="");
    void setInput(std::string in);
    int nextToken();
    int tokenValue() const;
    int skipLeadingWhiteSpace();
    int position() const;
    int rewind(int offset);
    char currentChar();
    int extractNumber();
    std::string extractAtom();
    std::string extractAtomSC(); //Special characters
    std::string extractVar();
    char extractChar();
private:
    std::string buffer;
    int pos;
    int _tokenValue;

private:
    template <int TokenType>
    void processToken(std::string const & s)
    {
        int val = -1;
        if (symbolExist(s,val))
        {
            _tokenValue = val;
        }
        else
        {
            symtable.push_back(std::pair<std::string, int>(s,TokenType));
            _tokenValue = symtable.size()-1; // index to symtable
        }
    }
};


#endif

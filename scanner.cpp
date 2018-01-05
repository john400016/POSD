#include "scanner.h"
Scanner::Scanner(std::string in)
    : buffer(in), pos(0), _tokenValue(NONE)
{

}

void Scanner::setInput(std::string in)
{
    buffer = in;
}

int Scanner::nextToken()
{
    if (skipLeadingWhiteSpace() >= static_cast<int>(buffer.length()))
        return EOS;
    else if (isdigit(currentChar()))
    {
        _tokenValue = extractNumber();
        return NUMBER;
    }
    else if (islower(currentChar()))
    {
        std::string s = extractAtom();
        processToken<ATOM>(s);
        return ATOM;
    }
    else if (isSpecialCh(currentChar()) && position() < static_cast<int>(buffer.length()) - 1)
    {
        std::string s = extractAtomSC();
        processToken<ATOMSC>(s);
        return ATOMSC;
    }
    else if (isupper(currentChar()) || currentChar() == '_')
    {
        std::string s = extractVar();
        processToken<VAR>(s);
        return VAR;
    }
    else
    {
        _tokenValue = NONE;
        return extractChar();
    }
}

int Scanner::tokenValue() const
{
    return _tokenValue;
}

int Scanner::skipLeadingWhiteSpace()
{
    for (; (buffer[pos] == ' ' || buffer[pos] == '\t') && pos < static_cast<int>(buffer.length()); ++pos);
    return position();
}

int Scanner::position() const
{
    return pos;
}

int Scanner::rewind(int offset)
{
    pos -= offset;
    return pos;
}

char Scanner::currentChar()
{
    return buffer[pos];
}

// extractX: extract X and set position right after X
int Scanner::extractNumber()
{
    int posBegin = position();
    for (;isdigit(buffer[pos]); ++pos);
    return stoi(buffer.substr(posBegin, pos-posBegin));
}

std::string Scanner::extractAtom()
{
    int posBegin = position();
    for (;isalnum(buffer[pos]) || buffer[pos] == '_'; ++pos);
    return buffer.substr(posBegin, pos-posBegin);
}

std::string Scanner::extractAtomSC()
{
    int posBegin = position();
    for (;isSpecialCh(buffer[pos]); ++pos);
    return buffer.substr(posBegin, pos-posBegin);
}

std::string Scanner::extractVar()
{
    int posBegin = position();
    for (;isalnum(buffer[pos]) || buffer[pos] == '_'; ++pos);
    return buffer.substr(posBegin, pos-posBegin);
}

char Scanner::extractChar()
{
    return buffer[pos++];
}

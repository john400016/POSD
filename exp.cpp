#include "exp.h"
std::vector<std::string> expStringToArray(std::string s)
{
  std::vector<std::string> charArray;
  std::string comma_token;
  std::stringstream scomma(s);
  while(std::getline(scomma,comma_token,','))
  {
      std::string space_token;
      std::stringstream sspace(comma_token);
      while(std::getline(sspace,comma_token,' '))
      {
        if(!comma_token.empty())
          charArray.push_back(comma_token);
      }
  }
  return charArray;
}
std::string subSame(std::string s1, std::string s2)
{
  std::vector<std::string> s1_array;
  std::vector<std::string> s2_array;
  s1_array = expStringToArray(s1);
  s2_array = expStringToArray(s2);
  std::string out;
  if(s1_array.size() % 3 != 0)
    return "";
  if(s2_array.size() % 3 != 0)
    return "";

  out += s1;
  out += ", ";

  for(size_t j=0;j<s2_array.size();j+=3)
  {
    bool dup = false;
    for(size_t i=0;i<s1_array.size();i+=3)
    {
      if(s1_array[i]   == s2_array[j]   &&
         s1_array[i+1] == s2_array[j+1] &&
         s1_array[i+2] == s2_array[j+2])
      {
        dup = true;
      }
    }
    if(!dup)
      out += s2_array[j]   + ' ' +
             s2_array[j+1] + ' ' +
             s2_array[j+2] + ',';
  }
  if(!out.empty())
  {
    if(out[out.size() - 1] == ' ')
      out.resize(out.size() - 2);
    else
      out.resize(out.size() - 1);
  }
  return out;
}

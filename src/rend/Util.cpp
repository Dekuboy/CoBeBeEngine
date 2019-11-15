#include "Util.h"

namespace rend
{

void Util::splitStringLineEnding(const std::string& input, std::sr1::vector<std::string>& output)
{
  std::string curr;

  output.clear();

  for(size_t i = 0; i < input.length(); i++)
  {
    if(input.at(i) == '\n')
    {
      output.push_back(curr);
      curr = "";
    }
    else if(input.at(i) == '\r')
    {
      // Ignore
    }
    else
    {
      curr += input.at(i);
    }
  }

  if(curr.length() > 0)
  {
    output.push_back(curr);
  }
}

void Util::splitStringWhitespace(const std::string& input, std::sr1::vector<std::string>& output)
{
  std::string curr;

  output.clear();

  for(size_t i = 0; i < input.length(); i++)
  {
    if(input.at(i) == ' ' ||
      input.at(i) == '\r' ||
      input.at(i) == '\n' ||
      input.at(i) == '\t')
    {
      if(curr.length() > 0)
      {
        output.push_back(curr);
        curr = "";
      }
    }
    else
    {
      curr += input.at(i);
    }
  }

  if(curr.length() > 0)
  {
    output.push_back(curr);
  }
}

void Util::splitString(const std::string& input, char splitter, std::sr1::vector<std::string>& output)
{
  std::string curr;

  output.clear();

  for(size_t i = 0; i < input.length(); i++)
  {
    if(input.at(i) == splitter)
    {
      output.push_back(curr);
      curr = "";
    }
    else
    {
      curr += input.at(i);
    }
  }

  if(curr.length() > 0)
  {
    output.push_back(curr);
  }
}

}

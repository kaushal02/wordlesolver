#pragma once
#include "config.h"

/* check if input word is valid */
bool isValidWord(std::string word)
{
  if (word.size() != WORDLENGTH)
  {
    std::cout << "Please enter " << WORDLENGTH << "-letter word\n\n";
    return false;
  }
  for (char c : word)
  {
    if (!islower(c))
    {
      std::cout << "Please make sure that your word has only a-z characters\n\n";
      return false;
    }
  }
  return true;
}

/* check if input verdict is valid */
bool isValidVerdict(std::string word)
{
  if (word.size() != WORDLENGTH)
  {
    std::cout << "Please enter " << WORDLENGTH << "-letter verdict\n\n";
    return false;
  }
  for (char c : word)
  {
    if (c < '0' or c > '2')
    {
      std::cout << "Please make sure that your verdict has only 0-1-2 characters\n\n";
      return false;
    }
  }
  return true;
}

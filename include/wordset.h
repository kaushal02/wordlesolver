#pragma once
#include "config.h"

class wordset
{
  private:
    std::string data;
    int weight;
    int variety;
    std::vector<int> count;

  public:
    wordset(std::string word);
    void setWeight(std::vector<int> &charweights);
    std::string getData();
    std::pair<int, int> getWeightage() const;
    bool isValid(std::string &checkword, std::string &verdict);
    bool operator<(wordset const &word) const;
};


/* Initializer for wordset */
wordset::wordset(std::string word)
{
  assert(word.size() == WORDLENGTH);
  data = word;
  weight = 0;

  count.resize(26, 0);
  for (char c : data)
  {
    count[c - 'a']++;
  }

  variety = 0;
  for (int c : count)
  {
    variety += (c > 0);
  }
}

/* based on charweights array, set the weight of word */
void wordset::setWeight(std::vector<int> &charweights)
{
  weight = 0;
  for (char c : data)
  {
    weight += count[c - 'a'] * charweights[c - 'a'];
  }
}

/* data getter */
std::string wordset::getData()
{
  return data;
}

/* weight getter */
std::pair<int, int> wordset::getWeightage() const
{
  return std::make_pair(variety, weight);
}

/* check if the word should be considered further for the puzzle */
bool wordset::isValid(std::string &checkword, std::string &verdict)
{
  for (int i = 0; i < WORDLENGTH; i++)
  {
    if ((verdict[i] == '0') ^ (!count[checkword[i] - 'a']))
    {
      return false;
    }

    if (verdict[i] == '1' and data[i] == checkword[i])
    {
      return false;
    }

    if (verdict[i] == '2' and data[i] != checkword[i])
    {
      return false;
    }
  }
  return true;
}

/* operator for sorting and fetching top guesses */
bool wordset::operator<(wordset const &word) const
{
  return getWeightage() > word.getWeightage();
}

#pragma once
#include "config.h"

class attributes
{
public:
    bool valid;
    int variety;
    int weight;
    attributes(): valid(true), variety(0), weight(0) {}
    bool operator<(attributes const &attrib) const
    {
        if (variety == attrib.variety)
        {
            if (weight == attrib.weight)
            {
                return valid > attrib.valid;
            }
            return weight > attrib.weight;
        }
        return variety > attrib.variety;
    }
    bool operator==(attributes const &attrib) const
    {
        return (valid == attrib.valid and variety == attrib.variety and weight == attrib.weight);
    }
};

class wordset
{
    private:
        std::string data;
        std::vector<int> count;
        attributes attrib;

    public:
        wordset(std::string word);
        void reset();
        void setWeight(std::vector<int> &charweights);
        std::string getData() const;
        attributes getAttributes() const;
        std::string getVerdict(std::string word);
        bool validate(std::string &checkword, std::string &verdict);
        bool operator<(wordset const &word) const;
};

/* initializer */
wordset::wordset(std::string word)
{
    assert(word.size() == WORDLENGTH);

    data = word;
    count.resize(26, 0);
    for (char c : data)
    {
        count[c - 'a']++;
    }

    int variety = 0;
    for (int c : count)
    {
        variety += (c > 0);
    }
    attrib.variety = variety;
}

/* reset the wordset */
void wordset::reset()
{
    attrib.valid = true;
    attrib.weight = 0;
}

/* based on charweights array, set the weight of word */
void wordset::setWeight(std::vector<int> &charweights)
{
    int weight = 0;
    for (char c : data)
    {
        weight += count[c - 'a'] * charweights[c - 'a'];
    }
    attrib.weight = weight;
}

/* data getter */
std::string wordset::getData() const
{
    return data;
}

/* attributes getter */
attributes wordset::getAttributes() const
{
    return attrib;
}

/* find the verdict if entered the given word */
std::string wordset::getVerdict(std::string word)
{
    std::string verdict = "";
    for (int i = 0; i < WORDLENGTH; i++)
    {
        if (word[i] == data[i])
        {
            verdict += "2";
        }
        else if (count[word[i] - 'a'])
        {
            verdict += "1";
        }
        else
        {
            verdict += "0";
        }
    }
    return verdict;
}

/* check if the word should be considered further for the puzzle */
bool wordset::validate(std::string &checkword, std::string &verdict)
{
    for (int i = 0; i < WORDLENGTH; i++)
    {
        if ((verdict[i] == '0') ^ (!count[checkword[i] - 'a']))
        {
            attrib.valid = false;
        }

        if (verdict[i] == '1' and data[i] == checkword[i])
        {
            attrib.valid = false;
        }

        if (verdict[i] == '2' and data[i] != checkword[i])
        {
            attrib.valid = false;
        }
    }
    return attrib.valid;
}

/* operator for sorting and fetching top guesses */
bool wordset::operator<(wordset const &word) const
{
    return attrib < word.getAttributes();
}

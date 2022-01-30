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
            return weight > attrib.weight;
        }
        return variety > attrib.variety;
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
        void setWeight(std::vector<int> &charweights);
        std::string getData() const;
        attributes getAttributes() const;
        void validate(std::string &checkword, std::string &verdict);
        bool operator<(wordset const &word) const;
};


/* Initializer for wordset */
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

/* check if the word should be considered further for the puzzle */
void wordset::validate(std::string &checkword, std::string &verdict)
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
}

/* operator for sorting and fetching top guesses */
bool wordset::operator<(wordset const &word) const
{
    return attrib < word.getAttributes();
}

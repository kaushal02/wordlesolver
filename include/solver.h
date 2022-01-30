#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "config.h"
#include "utility.h"
#include "wordset.h"

class solver
{
    private:
        int totalValidWords;
        std::vector<int> matches;
        std::vector<wordset> words;

    public:
        solver(std::string filename = FILENAME);
        void reset();
        std::vector<std::string> suggest();
        std::vector<wordset> getWords();
        bool read();
        void validate(std::string checkword, std::string verdict);
};

/* initializer */
solver::solver(std::string filename)
{
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cout << "Unable to open file";
        exit(1);
    }
    std::string word;
    while (fin >> word)
    {
        words.push_back(wordset(word));
    }
    fin.close();

    totalValidWords = words.size();
    matches = std::vector<int>(26, 0);
}

/* reset the solver */
void solver::reset()
{
    for (wordset &w : words)
    {
        w.reset();
    }
    totalValidWords = words.size();
    matches = std::vector<int>(26, 0);
}

/* list of best guesses */
std::vector<std::string> solver::suggest()
{
    std::vector<std::string> ret;
    if (!totalValidWords)
    {
        return ret;
    }

    if (totalValidWords == 1)
    {
        for (wordset &w : words)
        {
            if (w.getAttributes().valid)
            {
                ret.push_back(w.getData());
                return ret;
            }
        }
    }

    std::vector<int> count(26, 0);
    for (wordset &w : words)
    {
        for (char c : w.getData())
        {
            if (w.getAttributes().valid and !matches[c - 'a'])
            {
                count[c - 'a']++;
            }
        }
    }
    for (wordset &w : words)
    {
        w.setWeight(count);
    }
    std::sort(words.begin(), words.end());

    int weight = words[0].getAttributes().weight;
    if (!weight)
    {
        for (wordset &w : words)
        {
            if (w.getAttributes().valid)
            {
                ret.push_back(w.getData());
            }
        }
    }
    else
    {
        int i = 0;
        while (i < words.size() and words[i].getAttributes() == words[0].getAttributes())
        {
            ret.push_back(words[i++].getData());
        }
    }
    return ret;
}

/* words getter */
std::vector<wordset> solver::getWords()
{
    return words;
}

/* read and validate the response */
bool solver::read()
{
    std::string checkword;
    do {
        std::cout << "Please enter the word: ";
        std::cin >> checkword;
    } while (!isValidWord(checkword));

    std::string verdict;
    do {
        std::cout << "Please enter the verdict: ";
        std::cin >> verdict;
    } while (!isValidVerdict(verdict));

    if (verdict == "22222")
    {
        std::cout << "Congratulations you solved the puzzle!\n";
        return false;
    }
    validate(checkword, verdict);
    return true;
}

/* validate the remaining words as per response */
void solver::validate(std::string checkword, std::string verdict)
{
    for (int i = 0; i < WORDLENGTH; i++)
    {
        if (verdict[i] == '1' or verdict[i] == '2')
        {
            matches[checkword[i] - 'a'] = true;
        }
    }
    totalValidWords = 0;
    for (wordset &w : words)
    {
        w.validate(checkword, verdict);
        totalValidWords += w.getAttributes().valid;
    }
}

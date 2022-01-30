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
        void suggest_words();
        bool capture_response();
};

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
    std::cout << "Loaded " << totalValidWords << " valid " << WORDLENGTH << "-letter words.\n";
}

void solver::suggest_words()
{
    if (!totalValidWords)
    {
        std::cout << "No words remaining. Please check the inputs. Terminating.\n";
        exit(0);
    }

    if (totalValidWords == 1)
    {
        std::cout << "Congratulations, you solved the puzzle. Correct answer is: ";
        for (wordset &w : words)
        {
            if (w.getAttributes().valid)
            {
                std::cout << w.getData() << '\n';
                exit(0);
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

    std::cout << "Suggested guesses:\n";
    std::cout << "word  | weight  | valid\n";
    std::cout << "------+---------+------\n";
    for (int i = 0; i < SUGGESTCOUNT; i++)
    {
        std::cout << words[i].getData() << " | " << words[i].getAttributes().weight << "\t| " << std::boolalpha << words[i].getAttributes().valid << '\n';
    }
    std::cout << "Few valid words (out of " << totalValidWords << "):\n";
    int i = 0, toPrint = std::min(REMAININGCOUNT, totalValidWords);
    while (toPrint--)
    {
        while (i < words.size() and !words[i].getAttributes().valid)
        {
            i++;
        }
        if (i >= words.size())
        {
            break;
        }
        std::cout << words[i++].getData() << ' ';
    }
    std::cout << '\n';
}

bool solver::capture_response()
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
    return true;
}

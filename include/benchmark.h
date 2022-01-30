#pragma once
#include <iostream>
#include <map>
#include "solver.h"
#include "wordset.h"

class benchmark : public solver
{
    private:
        std::string getVerdict(std::string word, wordset trueword);

    public:
        benchmark() {}
        void run();
        int solve(wordset &word);
};

/* run the benchmark */
void benchmark::run()
{
    std::map<int,int> stepsTaken;
    std::vector<wordset> words(getWords());
    for (wordset &w : words)
    {
        stepsTaken[solve(w)]++;
    }
    std::cout << "Total number of " << WORDLENGTH << "-letter words = " << words.size() << "\n";
    int totalSteps = 0;
    for (std::pair<int,int> steps_count : stepsTaken)
    {
        std::cout << steps_count.first << " steps taken by " << steps_count.second << " words.\n";
        totalSteps += steps_count.first * steps_count.second;
    }
    std::cout << "Average steps taken to solve is " << ((double)totalSteps / words.size()) << "\n";
}

int benchmark::solve(wordset &word)
{
    reset();
    int ans = 0;
    std::string verdict = "";
    while (verdict != "22222")
    {
        std::vector<std::string> guesses = suggest();
        if (guesses.empty() or ans > 15)
        {
            return -1;
        }
        verdict = getVerdict(guesses[0], word);
        validate(guesses[0], verdict);
        ans++;
    }
    return ans;
}

std::string benchmark::getVerdict(std::string word, wordset trueword)
{
    std::string verdict = "";
    for (int i = 0; i < WORDLENGTH; i++)
    {
        if (word[i] == trueword.getData()[i])
        {
            verdict += "2";
        }
        else if (trueword.exists(word[i]))
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

#pragma once
#include <iostream>
#include <map>
#include "solver.h"
#include "wordset.h"

class benchmark : public solver
{
    private:
        const int MAX_STEPS = 10;

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
    int totalSteps = 0, totalSolvedWords = 0;
    for (std::pair<int,int> steps_count : stepsTaken)
    {
        if (steps_count.first == -1)
        {
            std::cout << "More than " << MAX_STEPS << " steps taken by " << steps_count.second << " words.\n";
        }
        else
        {
            std::cout << steps_count.first << " steps taken by " << steps_count.second << " words.\n";
            totalSteps += steps_count.first * steps_count.second;
            totalSolvedWords += steps_count.second;
        }
    }
    std::cout << "Solved " << totalSolvedWords << "/" << words.size() << " words in average " << ((double)totalSteps / totalSolvedWords) << " steps.\n\n";

    const int STEPS_100 = words.size() / 250;

    for (std::pair<int,int> steps_count : stepsTaken)
    {
        if (steps_count.first == -1)
        {
            std::cout << "- ";
        }
        else
        {
            std::cout << steps_count.first << " ";
        }
        for (int i = 0; i <steps_count.second / STEPS_100; i++)
        {
            std::cout << "|";
        }
        std::cout << "\n";
    }
}

int benchmark::solve(wordset &word)
{
    reset();
    int ans = 0;
    std::string verdict = "";
    while (verdict != "22222")
    {
        std::vector<std::string> guesses = suggest();
        if (guesses.empty() or ans > MAX_STEPS)
        {
            return -1;
        }
        verdict = word.getVerdict(guesses[0]);
        validate(guesses[0], verdict);
        ans++;
    }
    return ans;
}


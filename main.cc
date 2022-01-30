#include "include/solver.h"
#include "include/benchmark.h"

int main()
{
    benchmark().run();

    solver s;
    do {
        auto guesses = s.suggest();
        if (guesses.empty())
        {
            std::cout << "No word remaining. Please check inputs. Exiting.\n";
            return 0;
        }
        std::cout << "\nPlease enter one of the following words: ";
        for (std::string guess : guesses)
        {
            std::cout << guess << " ";
        }
        std::cout << "\n";
    } while (s.read());

    return 0;
}
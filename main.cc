#include "include/solver.h"
#include "include/benchmark.h"

int main(int argc, char **argv)
{
    if (argc == 2 and strcmp(argv[1], "benchmark") == 0)
    {
        benchmark().run();
        return 0;
    }

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
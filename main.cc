#include "include/solver.h"

int main()
{
    solver s;
    do {
        s.suggest_words();
    } while (s.capture_response());

    return 0;
}
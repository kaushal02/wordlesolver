# wordlesolver
interactive solver for [wordle](https://www.powerlanguage.co.uk/wordle/) in C++

## how to run

1. Clone the repo to your local

```
git clone https://github.com/kaushal02/wordlesolver.git
```

2. Change directory and make run

```
cd wordlesolver
make run
```

3. This will initiate the program and suggest top few words. Enter one of the words on the game website.


4. Enter the word you chose in the terminal. Then enter the verdict as a string of 0-1-2

> For black letter, use 0
>
> For yellow letter, use 1
>
> For green letter, use 2

For example, if you entered `"arose"` and all letters turned black except `o` which was yellow, your verdict is `"00100"`.

5. Repeat step 4 until you solve the puzzle.

## sample run

Enter the following command to initiate the program and solve a daily wordle.

```shell
$ make
g++ -O3 -std=c++11 main.cc -o main.out
./main.out

Please enter one of the following words: arose
Please enter the word: arose
Please enter the verdict: 00000

Please enter one of the following words: unity
Please enter the word: unity
Please enter the verdict: 00110

Please enter one of the following words: gulch
Please enter the word: gulch
Please enter the verdict: 10101

Please enter one of the following words: light
Please enter the word: light
Please enter the verdict: 22222
Congratulations you solved the puzzle!
```

Benchmark results may be checked by running the following command:

```shell
$ make test
g++ -O3 -std=c++11 main.cc -o main.out
./main.out benchmark
Total number of 5-letter words = 5757
1 steps taken by 1 words.
2 steps taken by 35 words.
3 steps taken by 1132 words.
4 steps taken by 2766 words.
5 steps taken by 1438 words.
6 steps taken by 334 words.
7 steps taken by 45 words.
8 steps taken by 5 words.
9 steps taken by 1 words.
Solved 5757/5757 words in average 4.1843 steps.
```
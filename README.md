# wordlesolver
interactive solver for wordle in C++

## how to run

1. Clone the repo to your local

```
git clone https://github.com/kaushal02/wordlesolver.git
```

2. make run

```
make run
```

3. This will initiate the program and suggest top few words. Enter one of the words at [wordle](https://www.powerlanguage.co.uk/wordle/)

4. Enter the word you chose in the console. Then enter the verdict as a string of 0-1-2

> For black letter, use 0
> For yellow letter, use 1
> For green letter, use 2

For example, if you entered `"arose"` and all letters turned black except `o` which was yellow, your verdict is `"00100"`.

5. Repeat the above step until you solve the puzzle.
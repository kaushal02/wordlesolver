#include <fstream>
#include <iostream>
#include <vector>
#include "include/config.h"
#include "include/utility.h"
#include "include/wordset.h"

void read_from_file(std::vector<wordset> &words) {
  std::ifstream fin(FILENAME);
  if (!fin.is_open()) {
    std::cout << "Unable to open file";
    exit(1);
  }
  std::string word;
  while (fin >> word) {
    words.push_back(wordset(word));
  }
  fin.close();
}

void suggest_words(std::vector<wordset> &words) {
  std::vector<int> count(26, 0);
  for (wordset &w : words) {
    for (char c : w.getData()) {
      count[c - 'a']++;
    }
  }
  for (wordset &w : words) {
    w.setWeight(count);
  }
  std::sort(words.begin(), words.end());

  std::cout << "Suggested words:\n";
  if (words.empty()) {
    std::cout << "No words remaining. Please check your inputs. Terminating.";
    exit(0);
  }
  for (int i = 0; i < std::min(SUGGESTCOUNT, (int)words.size()); i++) {
    std::cout << words[i].getData() << " " << words[i].getWeightage().second << '\n';
  }
  if (words.size() < SUGGESTCOUNT) {
    std::cout << "(these are the only remaining words)\n";
  }
  std::cout << '\n';
}

bool capture_response(std::vector<wordset> &words) {
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
  
  if (verdict == "22222") {
    std::cout << "Congratulations you cracked the puzzle!";
    return false;
  }

  std::vector<wordset> filteredwords;
  for (wordset &w : words) {
    if (w.isValid(checkword, verdict)) {
      filteredwords.push_back(w);
    }
  }
  words.swap(filteredwords);
  return true;
}

int main() {
  std::vector<wordset> words;
  read_from_file(words);

  do {
    suggest_words(words);
  } while (capture_response(words));
  
  return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const string FILENAME = "/Users/cartmanbrah/Desktop/Codes/local/data/fiveletterwords.txt";
const int SUGGESTCOUNT = 5;
const int WORDLENGTH = 5;

class wordset {
private:
  string data;
  int weight;
  int variety;
  vector<int> count;

public:
  wordset(string word) {
    assert(word.size() == WORDLENGTH);
    data = word;
    weight = 0;
    count.resize(26, 0);
    for (char c : data) {
      count[c - 'a']++;
    }
    variety = 0;
    for (int c : count) {
      if (c > 0) {
        variety++;
      }
    }
  }
  string getData() {
    return data;
  }
  pair<int,int> getWeightage() const {
    return make_pair(variety, weight);
  }
  void setWeight(vector<int> &charweights) {
    weight = 0;
    for (char c : data) {
      int ch = (c - 'a');
      weight += count[ch] * charweights[ch];
    }
  }
  bool operator < (wordset const &word) const {
    return getWeightage() > word.getWeightage();
  }
  bool isValid(string &checkword, string &verdict) {
    for (int i = 0; i < WORDLENGTH; i++) {
      if ((verdict[i] == '0') ^ (!count[checkword[i] - 'a'])) {
        return false;
      }
      if (verdict[i] == '1' and data[i] == checkword[i]) {
        return false;
      }
      if (verdict[i] == '2' and data[i] != checkword[i]) {
        return false;
      }
    }
    return true;
  }
};
vector<wordset> words;

void read_from_file(string filename) {
  ifstream fin(filename);
  if (!fin.is_open()) {
    cout << "Unable to open file";
    exit(1);
  }
  string word;
  while (fin >> word) {
    words.push_back(wordset(word));
  }
  fin.close();
}

void suggest_words() {
  vector<int> count(26, 0);
  for (wordset &w : words) {
    for (char c : w.getData()) {
      count[c - 'a']++;
    }
  }
  for (wordset &w : words) {
    w.setWeight(count);
  }
  sort(words.begin(), words.end());
  cout << "Suggested words:\n";
  for (int i = 0; i < min(SUGGESTCOUNT, (int)words.size()); i++) {
    cout << words[i].getData() << " " << words[i].getWeightage().second << '\n';
  }
}

bool capture_response() {
  cout << "Please enter the word: ";
  string checkword; cin >> checkword;
  cout << "Please enter the verdict: ";
  string verdict; cin >> verdict;

  if (verdict == "22222") {
    cout << "Congratulations you cracked the puzzle!";
    return false;
  }

  vector<wordset> filteredwords;
  for (wordset &w : words) {
    if (w.isValid(checkword, verdict)) {
      filteredwords.push_back(w);
    }
  }
  words.swap(filteredwords);
  return true;
}

int main() {
  read_from_file(FILENAME);
  
  do {
    suggest_words();
  } while (capture_response());
  
  return 0;
}
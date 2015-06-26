/*
  ID: paulius10
  PROG: lgame
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <set>

using namespace std;
struct trie {
  char c;
  bool ends;
  trie *sibling, *child;
};

map<char, int> input_values() {
    map<char, int> values;
  values['q'] = 7;
  values['w'] = 6;
  values['e'] = 1;
  values['r'] = 2;
  values['t'] = 2;
  values['y'] = 5;
  values['u'] = 4;
  values['i'] = 1;
  values['o'] = 3;
  values['p'] = 5;
  values['a'] = 2;
  values['s'] = 1;
  values['d'] = 4;
  values['f'] = 6;
  values['g'] = 5;
  values['h'] = 5;
  values['j'] = 7;
  values['k'] = 6;
  values['l'] = 3;
  values['z'] = 7;
  values['x'] = 7;
  values['c'] = 4;
  values['v'] = 6;
  values['b'] = 5;
  values['n'] = 2;
  values['m'] = 5;
  return values;
}

void solve(trie *root, trie *node, int sum, int &highest, string letters,
           string word, string first_word, set<string> &words,
           map<char, int> values) {
  if (!node) return;
  for (int i = 0; i < letters.length(); i++) {
    trie *n;
    for (n = node->child; n && n->c < letters[i]; n = n->sibling) {}
    if (n && n->c == letters[i]) {
      string new_word = word + letters[i];
      int min_length = min(new_word.length(), first_word.length());
      if (new_word.substr(0, min_length) < first_word.substr(0, min_length))
        continue;
      int new_sum = sum + values[letters[i]];
      string remaining_letters = letters.substr(0, i) + letters.substr(i + 1);
      solve(root, n, new_sum, highest, remaining_letters, new_word, first_word,
            words, values);
      if (n->ends) {
        solve(root, root, new_sum, highest, remaining_letters, "", new_word,
              words, values);
        if (new_sum >= highest) {
          if (new_sum > highest) {
            highest = new_sum;
            words.clear();
          }
          string final_word = (first_word == "") ? new_word :
            first_word + " " + new_word;
          words.insert(final_word);
        }
      }
    }
  }
}

int main() {
  map<char, int> values = input_values();
  trie root;
  root.child = NULL;
  ifstream fdict("lgame.dict");
  while (true) {
    string word;
    fdict >> word;
    if (word == ".") break;
    trie *node = &root;
    for (int i = 0; i < word.length(); i++) {
      trie *t = new trie;
      t->c = word[i];
      t->ends = (i == word.length() - 1);
      t->child = NULL;
      if (!node->child || node->child->c > word[i]) {
        t->sibling = node->child;
        node->child = t;
        node = t;
        continue;
      }
      for (node = node->child; node->sibling && node->sibling->c <= word[i];
           node = node->sibling) {}
      if (node->c == word[i]) continue;
      t->sibling = node->sibling;
      node->sibling = t;
      node = t;
    }
    node = &root;
  }
  fdict.close();
  ifstream fin("lgame.in");
  string letters;
  fin >> letters;
  fin.close();
  int highest = 0;
  set<string> words;
  solve(&root, &root, 0, highest, letters, "", "", words, values);
  ofstream fout("lgame.out");
  fout << highest << endl;
  for (set<string>::iterator it = words.begin(); it != words.end(); it++)
    fout << *it << endl;
  fout.close();
}

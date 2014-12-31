/*
  ID: paulius10
  PROG: prefix
  LANG: C++
*/

#include <fstream>
#include <set>

using namespace std;

struct node {
  char letter;
  bool end;
  node *child;
  node *sibling;
};

/*int magic(string &str, node *root, int startingIndex) {
  int max = 0;
  if (startingIndex >= str.length()) return max;
  node *pointer = root;
  for (int i = startingIndex; i < str.length(); i++) {
    if (pointer == NULL) return max;
    while (pointer->letter != str[i]) {
      pointer = pointer->sibling;
      if (pointer == NULL) return max;
    }
    if (pointer->end) {
      int future = i - startingIndex + 1 + magic(str, root, i + 1);
      if (future > max) max = future;
    }
    pointer = pointer->child;
  }
  return max;
  }*/

int main() {
  ifstream fin("prefix.in");
  set<string> primitives;
  while (true) {
    string input;
    fin >> input;
    if (input == ".") break;
    primitives.insert(input);
  }
  string str;
  while (!fin.eof()) {
    string input;
    fin >> input;
    str += input;
  }
  fin.close();
  node *root = NULL;
  for (set<string>::iterator it = primitives.begin(); it != primitives.end();
       it++) {
    node *pointer = root;
    node *parent = NULL;
    for (int i = 0; i < it->length(); i++) {
      node *previous = NULL;
      while (true) {
        if (pointer == NULL) {
          pointer = new node;
          pointer->letter = (*it)[i];
          pointer->end = (i == it->length() - 1);
          pointer->child = NULL;
          pointer->sibling = NULL;
          if (previous != NULL) previous->sibling = pointer;
          else if (parent != NULL) parent->child = pointer;
          else root = pointer;
          break;
        }
        if (pointer->letter == (*it)[i]) break;
        previous = pointer;
        pointer = pointer->sibling;
      }
      parent = pointer;
      pointer = pointer->child;
    }
  }
  bool dp[str.length() + 1];
  dp[0] = true;
  for (int i = 1; i <= str.length(); i++) dp[i] = false;
  for (int i = 1; i <= str.length(); i++) {
    for (set<string>::iterator it = primitives.begin();
         it != primitives.end(); it++) {
      bool impossible = false;
      int j = i - 1;
      for (int k = (*it).length() - 1; k >= 0; k--) {
        if (j < 0 || (*it)[k] != str[j]) {
          impossible = true;
          break;
        }
        j--;
      }
      if (!impossible && dp[i - (*it).length()]) {
        dp[i] = true;
        break;
      }
    }
  }
  ofstream fout("prefix.out");
  for (int i = str.length(); i >= 0; i--) {
    if (dp[i]) {
      fout << i << endl;
      break;
    }
  }
  fout.close();
  return 0;
}

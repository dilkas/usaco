/*
  ID: paulius10
  PROG: heritage
  LANG: C++
*/

#include <fstream>
#include <map>

using namespace std;

void initialize(map<char, bool> m) {
  for (char c = 'A'; c <= 'Z'; c++) m[c] = false;
}

void print(string in, string pre, map<char, bool> considering, ofstream &fout) {
  char root = '0';
  for (int i = 0; i < pre.size(); i++) {
    if (considering[pre[i]]) {
      root = pre[i];
      break;
    }
  }
  if (root == '0') return;
  map<char, bool> left;
  initialize(left);
  int i;
  for (i = 0; in[i] != root; i++) {
    if (considering[in[i]]) left[in[i]] = true;
  }
  map<char, bool> right;
  for (i++; i < in.size(); i++) {
    if (considering[in[i]]) right[in[i]] = true;
  }
  print(in, pre, left, fout);
  print(in, pre, right, fout);
  fout << root;
}

int main() {
  ifstream fin("heritage.in");
  string in, pre;
  fin >> in >> pre;
  fin.close();
  map<char, bool> everything;
  initialize(everything);
  for (int i = 0; i < in.length(); i++) everything[in[i]] = true;
  ofstream fout("heritage.out");
  print(in, pre, everything, fout);
  fout << endl;
  fout.close();
  return 0;
}

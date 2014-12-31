/*
  ID: paulius10
  PROG: calfflac
  LANG: C++
*/

#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
  ifstream fin("calfflac.in");
  ofstream fout("calfflac.out");
  string s((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
  int ns = s.length();
  string T = "^";
  vector<int> indices;
  indices.push_back(0);
  for (int i = 0; i < ns; i++) {
    if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
      stringstream ss;
      string temp;
      ss << (char) tolower(s[i]);
      ss >> temp;
      T += "#" + temp;
      indices.push_back(0);
      indices.push_back(i);
    }
  }
  T += "#$";
  indices.push_back(0);
  indices.push_back(0);
  int n = T.length();
  int P[n];
  int C = 0, R = 0;
  for (int i = 1; i < n - 1; i++) {
    int i_mirror = 2 * C - i;
    P[i] = (R > i) ? min(R - i, P[i_mirror]) : 0;
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) P[i]++;
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }
  int maxLen = 0;
  int centerIndex = 0;
  for (int i = 1; i < n - 1; i++) {
    if (P[i] > maxLen) {
      maxLen = P[i];
      centerIndex = i;
    }
  }
  int start = indices[centerIndex - maxLen + 1];
  fout << maxLen << endl << s.substr(start, indices[centerIndex + maxLen - 1] - start + 1) << endl;
  return 0;
}

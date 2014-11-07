/*
  ID: paulius10
  PROG: palsquare
  LANG: C++
 */

#include <fstream>
#include <math.h>
#include <iostream>

using namespace std;

int maxDeg(int N, int B) {
  int t = 1;
  while (t <= N) t *= B;
  return t / B;
}

int maxCoef(int N, int B) {
  int coef = 1;
  int t = B;
  while (t <= N) {
    t += B;
    coef++;
  }
  return coef - 1;
}

string toBase(int N, int B, char numerals[]) {
  string s = "";
  int deg = maxDeg(N, B);
  while (deg >= 1) {
    int c = maxCoef(N, deg);
    s += numerals[c];
    N -= c * deg;
    deg /= B;
  }
  return s;
}

bool isPalindrome(string s) {
  for (int i = 0; i < s.length() / 2; i++) {
    if (s[s.length() - i - 1] != s[i]) return false;
  }
  return true;
}

int main() {
  ifstream fin("palsquare.in");
  ofstream fout("palsquare.out");
  char numerals[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  int B;
  fin >> B;
  for (int N = 1; N <= 300; N++) {
    string squared = toBase(N * N, B, numerals);
    if (isPalindrome(squared)) fout << toBase(N, B, numerals) << " " << squared << endl;
  }
  return 0;
}

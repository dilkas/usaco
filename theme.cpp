/*
  ID: paulius10
  PROG: theme
  LANG: C++
*/

#include <fstream>

using namespace std;
const int MIN_LENGTH = 4;

int main() {
  int N;
  ifstream fin("theme.in");
  fin >> N;
  int differences[--N];
  int a;
  fin >> a;
  for (int i = 0; i < N; i++) {
    int b;
    fin >> b;
    differences[i] = b - a;
    a = b;
  }
  fin.close();
  int m = -1;
  for (int diff = 0; diff < N; diff++) {
    int v = 0;
    for (int i = diff; i < N; i++) {
      v = (differences[i] == differences[i - diff] &&
           diff - 1 > v) ? v + 1 : 0;
      if (v >= MIN_LENGTH && v > m) m = v;
    }
  }
  ofstream fout("theme.out");
  fout << m + 1 << endl;
  fout.close();
  return 0;
}

/*
  ID: paulius10
  PROG: concom
  LANG: C++
*/

#include <fstream>

#define MAX_COMPANIES 101

using namespace std;

void update(int first[][MAX_COMPANIES], int second[][MAX_COMPANIES],
            bool controlled[][MAX_COMPANIES], int i, int j) {
  if (controlled[i][j] || i == j) return;
  controlled[i][j] = true;
  for (int k = 0; k < MAX_COMPANIES; k++) {
    second[i][k] += first[j][k];
    if (first[i][k] + second[i][k] > 50) update(first, second, controlled, i, k);
  }
}

int main() {
  int first[MAX_COMPANIES][MAX_COMPANIES];
  int second[MAX_COMPANIES][MAX_COMPANIES];
  bool controlled[MAX_COMPANIES][MAX_COMPANIES];
  for (int i = 0; i < MAX_COMPANIES; i++) {
    for (int j = 0; j < MAX_COMPANIES; j++) {
      first[i][j] = 0;
      second[i][j] = 0;
      controlled[i][j] = false;
    }
  }
  ifstream fin("concom.in");
  int n;
  fin >> n;
  for (int x = 0; x < n; x++) {
    int i, j;
    fin >> i >> j;
    fin >> first[i][j];
  }
  fin.close();
  for (int i = 0; i < MAX_COMPANIES; i++) {
    for (int j = 0; j < MAX_COMPANIES; j++) {
      if (first[i][j] > 50) update(first, second, controlled, i, j);
    }
  }
  ofstream fout("concom.out");
  for (int i = 0; i < MAX_COMPANIES; i++) {
    for (int j = 0; j < MAX_COMPANIES; j++) {
      if (controlled[i][j]) fout << i << ' ' << j << endl;
    }
  }
  fout.close();
  return 0;
}

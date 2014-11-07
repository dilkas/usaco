/*
  ID: paulius10
  PROG: barn1
  LANG: C++
*/

#include <fstream>
#include <iostream>

using namespace std;

int main() {
  ifstream fin("barn1.in");
  ofstream fout("barn1.out");
  int M, S, C;
  fin >> M >> S >> C;
  bool used[S];
  bool cows[S];
  for (int i = 0; i < S; i++) {
    used[i] = false;
    cows[i] = false;
  }
  for (int i = 0; i < C; i++) {
    int t;
    fin >> t;
    cows[t - 1] = true;
  }
  int n = S;
  for (int i = 0; i < S; i++) {
    if (!cows[i]) {
      n--;
      used[i] = true;
    }
    else break;
  }
  for (int i = S - 1; i >= 0; i--) {
    if (!cows[i]) {
      n--;
      used[i] = true;
    }
    else break;
  }
  for (int i = 0; i < M - 1; i++) {
    int max_counter = 0;
    int start_i = 0;
    for (int j = 0; j < S; j++) {
      int counter = 0;
      for (int k = j; k < S; k++) {
	if (cows[k] || used[k]) break;
	counter++;
      }
      if (counter > max_counter && j != 0 && j + counter != S) {
	max_counter = counter;
	start_i = j;
      }
    }
    n -= max_counter;
    for (int k = start_i; k < start_i + max_counter; k++) used[k] = true;
  }
  fout << n << endl;
  return 0;
}

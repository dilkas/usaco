/*
  ID: paulius10
  PROG: game1
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <limits>

#define MAX_N 100

using namespace std;

int maximize(int seq[], int memo[][MAX_N], int N, int a, int b) {
  if (memo[a][b] != numeric_limits<int>::max()) return memo[a][b];
  int score = max(seq[a] - maximize(seq, memo, N, a + 1, b),
                  seq[b] - maximize(seq, memo, N, a, b - 1));
  memo[a][b] = score;
  return score;
}

int main() {
  ifstream fin("game1.in");
  int N;
  fin >> N;
  int seq[N];
  for (int i = 0; i < N; i++) fin >> seq[i];
  fin.close();
  int sum = 0;
  for (int i = 0; i < N; i++) sum += seq[i];
  int memo[N][MAX_N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) memo[i][j] = numeric_limits<int>::max();
    memo[i][i] = seq[i];
  }
  int difference = maximize(seq, memo, N, 0, N - 1); // calculating p1-p2
  ofstream fout("game1.out");
  fout << (difference + sum) / 2 << " " << (sum - difference) / 2 << endl;
  fout.close();
  return 0;
}

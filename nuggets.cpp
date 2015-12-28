/*
  ID: paulius10
  PROG: nuggets
  LANG: C++
*/

#include <fstream>
#include <stdlib.h>

using namespace std;

int gcd(int a, int b) {
  if (!b) return a;
  return gcd(b, a % b);
}

void output(int n) {
  ofstream fout("nuggets.out");
  fout << n << endl;
  fout.close();
  exit(0);
}

int main() {
  ifstream fin("nuggets.in");
  int N;
  fin >> N;
  int nuggets[N];
  for (int i = 0; i < N; i++) fin >> nuggets[i];
  fin.close();
  if (N == 1 && nuggets[0] != 1) output(0);
  int g = gcd(nuggets[0], nuggets[1]);
  for (int i = 2; i < N; i++) g = gcd(g, nuggets[i]);
  if (g != 1) output(0);
  int max_e = nuggets[0];
  for (int i = 1; i < N; i++) {
    if (nuggets[i] > max_e) max_e = nuggets[i];
  }
  int limit = max_e * (max_e - N);
  bool *dp = new bool[limit];
  dp[0] = true;
  int largest = 0;
  for (int i = 1; i < limit; i++) {
    bool value = false;
    for (int j = 0; j < N; j++) {
      int previous = i - nuggets[j];
      if (previous >= 0 && dp[previous]) {
        value = true;
        break;
      }
    }
    dp[i] = value;
    if (!dp[i]) largest = i;
  }
  delete[] dp;
  output(largest);
}

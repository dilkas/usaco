/*
  ID: paulius10
  PROG: nocows
  LANG: C++
*/

#include <fstream>

#define MOD 9901
#define MAX_N 200
#define MAX_K 100

using namespace std;

int main() {
  int N, K;
  ifstream fin("nocows.in");
  fin >> N >> K;
  fin.close();
  int p[MAX_N][MAX_K];
  int s[MAX_N][MAX_K];
  for (int k = 0; k < MAX_K; k++) {
    for (int n = 0; n < MAX_N; n++) {
      p[n][k] = 0;
      s[n][k] = 0;
    }
  }
  p[1][1] = 1;
  for (int k = 2; k < MAX_K; k++) s[1][k] = 1;
  for (int k = 2; k < MAX_K; k++) {
    for (int n = 0; n < MAX_N; n++) {
      for (int n1 = 0; n1 < n; n1++) {
        p[n][k] = (p[n][k] + p[n1][k - 1] * (2 * s[n - n1 - 1][k - 1] +
                                             p[n - n1 - 1][k - 1])) % MOD;
      }
    }
    for (int n = 3; n < MAX_N; n++) {
      for (int k1 = 1; k1 < k; k1++) s[n][k] = (s[n][k] + p[n][k1]) % MOD;
    }
  }
  ofstream fout("nocows.out");
  fout << p[N][K] << endl;
  fout.close();
  return 0;
}

/*
  ID: paulius10
  PROG: kimbits
  LANG: C++
*/

#include <fstream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main() {
  long long N, L, I;
  ifstream fin("kimbits.in");
  fin >> N >> L >> I;
  fin.close();

  long long binomial[N][N];
  binomial[0][0] = 1;
  for (long long n = 1; n < N; n++) {
    binomial[n][0] = 1;
    binomial[n][n] = 1;
    for (long long k = 1; k < n; k++)
      binomial[n][k] = binomial[n - 1][k - 1] + binomial[n - 1][k];
  }

  long long sums[N][N];
  for (long long n = 0; n < N; n++) {
    long long sum = 0;
    for (long long k = 0; k <= n; k++) {
      sum += binomial[n][k];
      sums[n][k] = sum;
    }
  }
  
  ofstream fout("kimbits.out");
  for (N--; N >= 0; N--) {
    if (L > N) L = N;
    if (sums[N][L] >= I) {
      fout << 0;
    } else {
      fout << 1;
      I -= sums[N][L];
      L--;
    }
  }
  fout << endl;
  fout.close();
  return 0;
}

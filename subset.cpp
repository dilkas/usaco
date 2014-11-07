/*
  ID: paulius10
  PROG: subset
  LANG: C++
*/

#include <fstream>

using namespace std;

int main() {
  ifstream fin("subset.in");
  int N;
  fin >> N;
  fin.close();
  int remainder = N % 4;
  if (remainder == 1 || remainder == 2) {
    ofstream fout("subset.out");
    fout << 0 << endl;
    fout.close();
    return 0;
  }
  int maxSum = N * (N + 1) / 4;
  unsigned long long data[N + 1][maxSum + 1];
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= maxSum; j++) data[i][j] = 0;
  }
  data[0][0] = 1;
  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= maxSum; j++) {
      data[i][j] += data[i - 1][j];
      int newSum = i + j;
      if (newSum <= maxSum) data[i][newSum] += data[i - 1][j];
    }
  }
  ofstream fout("subset.out");
  fout << data[N][maxSum] / 2 << endl;
  fout.close();
  return 0;
}

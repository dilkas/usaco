/*
  ID: paulius10
  PROG: inflate
  LANG: C++
*/

#include <fstream>

using namespace std;

int main() {
  ifstream fin("inflate.in");
  int M, N;
  fin >> M >> N;
  int points[N];
  int minutes[N];
  for (int i = 0; i < N; i++) fin >> points[i] >> minutes[i];
  fin.close();
  int max[M + 1];
  for (int m = 0; m <= M; m++) {
    max[m] = 0;
    for (int i = 0; i < N; i++) {
      if (minutes[i] <= m) {
        int p = points[i] + max[m - minutes[i]];
        if (p > max[m]) max[m] = p;
      }
    }
  }
  ofstream fout("inflate.out");
  fout << max[M] << endl;
  fout.close();
  return 0;
}

/*
  ID: paulius10
  PROG: range
  LANG: C++
*/

#include <algorithm>
#include <fstream>

#define MAX_N 250

using namespace std;

int max_line(string field[], int x, int y, int dx, int dy) {
  int c;
  for (c = 0; x >= 0 && y >= 0; x += dx, y += dy, c++) {
    if (field[x][y] == '0') return c;
  }
  return c;
}

void dp(string field[], int N, int x, int y, int m[][MAX_N]) {
  m[x][y] = field[x][y] - '0';
  for (int i = 1; x + i < N && y + i < N; i++)
    m[x + i][y + i] = min(m[x + i - 1][y + i - 1] + 1,
                          min(max_line(field, x + i, y + i, -1, 0),
                              max_line(field, x + i, y + i, 0, -1)));
}

int main() {
  ifstream fin("range.in");
  int N;
  fin >> N;
  string field[N];
  for (int i = 0; i < N; i++) fin >> field[i];
  fin.close();
  int m[N][MAX_N];
  dp(field, N, 0, 0, m);
  for (int i = 1; i < N; i++) {
    dp(field, N, 0, i, m);
    dp(field, N, i, 0, m);
  }
  int sizes[N + 1];
  for (int i = 0; i <= N; i++) sizes[i] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 2; k <= m[i][j]; k++) sizes[k]++;
    }
  }
  ofstream fout("range.out");
  for (int i = 2; i <= N; i++) {
    if (sizes[i]) fout << i << " " << sizes[i] << endl;
  }
  fout.close();
  return 0;
}

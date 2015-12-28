/*
  ID: paulius10
  PROG: rockers
  LANG: C++
*/

#include <fstream>
#include <numeric>
#include <stdlib.h>

using namespace std;

bool works(int used[], int lengths[], int N, int T, int M) {
  int n_full_disks = 0;
  int time_left = T;
  for (int i = 0; i < N; i++) {
    if (!used[i]) continue;
    if (lengths[i] > T) return false;
    if (lengths[i] <= time_left) time_left -= lengths[i];
    else {
      n_full_disks++;
      time_left = T - lengths[i];
    }
    if (n_full_disks >= M) return false;
  }
  return true;
}

void truncated_dfs(int nextpos, int depth, int used[], int lengths[], int N,
                   int T, int M) {
  if (works(used, lengths, N, T, M)) {
    ofstream fout("rockers.out");
    fout << accumulate(used, used + N, 0) << endl;
    fout.close();
    exit(0);
  }
  if (depth == 0) return;
  for (int i = nextpos; i < N; i++) {
    if (used[i]) {
      used[i] = 0;
      truncated_dfs(i + 1, depth - 1, used, lengths, N, T, M);
      used[i] = 1;
    }
  }
}

int main() {
  ifstream fin("rockers.in");
  int N, T, M;
  fin >> N >> T >> M;
  int lengths[N];
  for (int i = 0; i < N; i++) fin >> lengths[i];
  fin.close();
  int used[N];
  for (int i = 0; i < N; i++) used[i] = 1;
  for (int depth = 0; depth <= N; depth++) truncated_dfs(0, depth, used, lengths, N, T, M);
  return 0;
}

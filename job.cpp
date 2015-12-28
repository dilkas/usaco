/*
  ID: paulius10
  PROG: job
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <limits>

using namespace std;

int main() {
  ifstream fin("job.in");
  int N, M1, M2;
  fin >> N >> M1 >> M2;
  int A_times[M1], B_times[M2], A_ready[M1], B_ready[M2];
  for (int i = 0; i < M1; i++) {
    fin >> A_times[i];
    A_ready[i] = 0;
  }
  for (int i = 0; i < M2; i++) {
    fin >> B_times[i];
    B_ready[i] = 0;
  }
  fin.close();
  int intermediate[N];
  for (int i = 0; i < N; i++) {
    int m = 0;
    for (int j = 0; j < M1; j++) {
      if (A_ready[j] + A_times[j] < A_ready[m] + A_times[m]) m = j;
    }
    A_ready[m] += A_times[m];
    intermediate[i] = A_ready[m];
  }
  int min_time = B_times[0];
  for (int i = 0; i < M2; i++) {
    if (B_times[i] < min_time) min_time = B_times[i];
  }
  int end_time;
  for (end_time = intermediate[N - 1] + min_time; ; end_time++) {
    bool working = true;
    for (int i = 0; i < M2; i++) B_ready[i] = end_time;
    for (int i = N - 1; i >= 0; i--) {
      int index = -1;
      int value = 0;
      for (int j = 0; j < M2; j++) {
        int new_time = B_ready[j] - B_times[j];
        if (new_time < intermediate[j]) continue;
        if (new_time > value) {
          value = new_time;
          index = j;
        }
      }
      if (index != -1) B_ready[index] = value;
      else {
        working = false;
        break;
      }
    }
    if (working) break;
  }
  ofstream fout("job.out");
  fout << intermediate[N - 1] << " " << end_time << endl;
  fout.close();
  return 0;
}

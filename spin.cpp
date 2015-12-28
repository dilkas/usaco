/*
  ID: paulius10
  PROG: spin
  LANG: C++
*/

#include <fstream>

#define N_WHEELS 5
#define MAX_W 5
#define MOD 360

struct wedge {
  int start_angle, extent;
};

using namespace std;

int main() {
  int rotation_speed[N_WHEELS];
  int W[N_WHEELS];
  wedge wedges[N_WHEELS][MAX_W];
  ifstream fin("spin.in");
  for (int i = 0; i < N_WHEELS; i++) {
    fin >> rotation_speed[i] >> W[i];
    for (int j = 0; j < W[i]; j++) {
      fin >> wedges[i][j].start_angle >> wedges[i][j].extent;
    }
  }
  fin.close();
  ofstream fout("spin.out");
  int t;
  for (t = 0; t < MOD; t++) {
    bool open[MOD];
    for (int i = 0; i < MOD; i++) open[i] = true;
    for (int i = 0; i < N_WHEELS; i++) {
      bool open_on_wheel[MOD];
      for (int j = 0; j < MOD; j++) open_on_wheel[j] = false;
      for (int j = 0; j < W[i]; j++) {
        int start = (wedges[i][j].start_angle + rotation_speed[i] * t) % MOD;
        int end = (start + wedges[i][j].extent) % MOD;
        if (start <= end) {
        for (int k = start; k <= end; k++) open_on_wheel[k] = true;
        } else {
          for (int k = start; k < MOD; k++) open_on_wheel[k] = true;
          for (int k = 0; k <= end; k++) open_on_wheel[k] = true;
        }
      }
      for (int j = 0; j < MOD; j++) open[j] = open[j] && open_on_wheel[j];
    }
    for (int i = 0; i < MOD; i++) {
      if (open[i]) {
        fout << t << endl;
        fout.close();
        return 0;
      }
    }
  }
  fout << "none" << endl;
  fout.close();
  return 0;
}

/*
  ID: paulius10
  PROG: ratios
  LANG: C++
*/

#include <fstream>

#define N_COMPONENTS 3
#define N_MIXTURES 3
#define MAX_COMPONENT 99

using namespace std;

int test(int solution[], int goal[], int mixtures[][N_COMPONENTS]) {
  int values[N_COMPONENTS];
  for (int i = 0; i < N_COMPONENTS; i++) values[i] = 0;
  for (int i = 0; i < N_MIXTURES; i++) {
    for (int j = 0; j < N_COMPONENTS; j++)
      values[j] += solution[i] * mixtures[i][j];
  }
  int multiple = -1;
  for (int i = 0; i < N_COMPONENTS; i++) {
    if (goal[i] != 0) {
      if (values[i] == 0 || values[i] % goal[i] != 0 ||
          (multiple != -1 && values[i] / goal[i] != multiple)) {
        return -1;
      }
      multiple = values[i] / goal[i];
    } else if (values[i] != 0) {
      return -1;
    }
  }
  return multiple;
}

bool next(int solution[]) {
  for (int i = N_MIXTURES - 1; i >= 0; i--) {
    if (solution[i] == MAX_COMPONENT) continue;
    solution[i]++;
    for (int j = i + 1; j < N_MIXTURES; j++) solution[j] = 0;
    return true;
  }
  return false;
}

int main() {
  int goal[N_COMPONENTS];
  int mixtures[N_MIXTURES][N_COMPONENTS];
  ifstream fin("ratios.in");
  for (int i = 0; i < N_COMPONENTS; i++) fin >> goal[i];
  for (int i = 0; i < N_MIXTURES; i++) {
    for (int j = 0; j < N_COMPONENTS; j++) fin >> mixtures[i][j];
  }
  fin.close();

  ofstream fout("ratios.out");
  int solution[N_MIXTURES];
  for (int i = 0; i < N_MIXTURES; i++) solution[i] = 0;
  do {
    int multiple = test(solution, goal, mixtures);
    if (multiple != -1) {
      for (int i = 0; i < N_MIXTURES; i++) fout << solution[i] << " ";
      fout << multiple << endl;
      return 0;
    }
  } while (next(solution));
  fout << "NONE" << endl;
  fout.close();
  return 0;
}

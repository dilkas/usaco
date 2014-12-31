/*
  ID: paulius10
  PROG: sort3
  LANG: C++
*/

#include <fstream>

#define CATEGORIES 3

using namespace std;

int magic(int boundaries[], int data[], bool perfect) {
  int exchanges = 0;
  bool changesDone = true;
  while (changesDone) {
    changesDone = false;
    for (int i = 0; i < CATEGORIES; i++) {
      for (int j = boundaries[i]; j < boundaries[i + 1]; j++) {
        if (data[j] != i + 1) {
          for (int k = boundaries[data[j] - 1]; k < boundaries[data[j]]; k++)
            {
              if ((perfect && data[k] == i + 1) || (!perfect && data[k] != data[j])) {
                exchanges++;
                changesDone = true;
                int temp = data[k];
                data[k] = data[j];
                data[j] = temp;
                break;
              }
            }
        }
      }
    }
  }
  return exchanges;
}

int main() {
  ifstream fin("sort3.in");
  int N;
  fin >> N;
  int data[N];
  int boundaries[CATEGORIES + 1];
  for (int i = 0; i <= CATEGORIES; i++) boundaries[i] = 0;
  for (int i = 0; i < N; i++) {
    fin >> data[i];
    for (int j = data[i]; j <= CATEGORIES; j++) boundaries[j]++;
  }
  fin.close();
  ofstream fout("sort3.out");
  fout << magic(boundaries, data, true) + magic(boundaries, data, false) << endl;
  fout.close();
  return 0;
}

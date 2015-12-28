/*
  ID: paulius10
  PROG: fence
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <vector>

#define N 500

using namespace std;

vector<int> fences[N];
vector<int> circuit;

void find_circuit(int i) {
  if (fences[i].empty()) {
    circuit.push_back(i);
    return;
  }
  while (!fences[i].empty()) {
    int j = fences[i][0];
    fences[i].erase(fences[i].begin());
    for (vector<int>::iterator it = fences[j].begin(); it != fences[j].end();
         it++) {
      if (*it == i) {
        fences[j].erase(it);
        break;
      }
    }
    find_circuit(j);
  }
  circuit.push_back(i);
}

void find_euler_circuit(int i) {
  circuit.clear();
  find_circuit(i);
  ofstream fout("fence.out");
  for (vector<int>::reverse_iterator rit = circuit.rbegin();
       rit != circuit.rend(); rit++) {
    fout << *rit + 1 << endl;
  }
  fout.close();
  exit(0);
}

void copy_fences(vector<int> original_fences[]) {
  for (int i = 0; i < N; i++) fences[i] = original_fences[i];
}

int main() {
  ifstream fin("fence.in");
  int F;
  fin >> F;
  vector<int> original_fences[N];
  for (int i = 0; i < F; i++) {
    int intersection1, intersection2;
    fin >> intersection1 >> intersection2;
    intersection1--;
    intersection2--;
    original_fences[intersection1].push_back(intersection2);
    original_fences[intersection2].push_back(intersection1);
  }
  fin.close();
  for (int i = 0; i < N; i++)
    sort(original_fences[i].begin(), original_fences[i].end());
  copy_fences(original_fences);
  for (int i = 0; i < N; i++) {
    if (fences[i].size() % 2 == 1) find_euler_circuit(i);
  }
  copy_fences(original_fences);
  for (int i = 0; i < N; i++) {
    if (!fences[i].empty()) find_euler_circuit(i);
  }
}

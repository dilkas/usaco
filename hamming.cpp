/*
  ID: paulius10
  PROG: hamming
  LANG: C++
*/

#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

int distance(int a, int b, int max) {
  int differences = a ^ b;
  int counter = 0;
  for (int powerOfTwo = 1; powerOfTwo < max; powerOfTwo *= 2) {
    if (differences & powerOfTwo) counter++;
  }
  return counter;
}

bool ok(int code, vector<int> codes, int max, int D) {
  for (int i = 0; i < codes.size(); i++) {
    if (distance(code, codes[i], max) < D) return false;
  }
  return true;
}

int main() {
  ifstream fin("hamming.in");
  int N, B, D;
  fin >> N >> B >> D;
  fin.close();
  const int max = pow(2, B);
  vector<int> codes;
  codes.push_back(0);
  while (codes.size() < N) {
    for (int code = codes[codes.size() - 1] + 1; code < max; code++) {
      if (ok(code, codes, max, D)) {
        codes.push_back(code);
        break;
      }
    }
  }
  ofstream fout("hamming.out");
  int i = 0;
  while (true) {
    fout << codes[i];
    if (++i == codes.size()) {
      fout << endl;
      fout.close();
      return 0;
    }
    for (int j = 1; j < 10; j++) {
      fout << " " << codes[i];
      if (++i == codes.size()) {
        fout << endl;
        fout.close();
        return 0;
      }
    }
    fout << endl;
  }
  fout.close();
  return 0;
}

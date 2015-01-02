/*
  ID: paulius10
  PROG: zerosum
  LANG: C++
*/

#include <fstream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int apply(char signs[], int i) {
  if (i < 0) return 1;
  int n = i + 2;
  if (signs[i] == '+') return n;
  if (signs[i] == '-') return -n;
  int previous = apply(signs, i - 1);
  if (previous < 0) return 10 * previous - n;
  return 10 * previous + n;
}

int evaluate(char signs[], int N) {
  int sum = 0;
  int skip = 0;
  for (int i = N - 2; i >= -1; i--) {
    if (skip > 0) {
      skip--;
    } else {
      int value = apply(signs, i);
      sum += value;
      skip = int(log10(abs(value)));
    }
  }
  return sum;
}

void recurse(char signs[], int i, int N, ofstream& fout) {
  if (i == N - 1) {
    if (evaluate(signs, N) == 0) {
      fout << 1;
      for (int j = 0; j < N - 1; j++) {
        fout << signs[j] << j + 2;
      }
      fout << endl;
    }
    return;
  }
  char possible_signs[] = {' ', '+', '-'};
  for (int j = 0; j < 3; j++) {
    signs[i] = possible_signs[j];
    recurse(signs, i + 1, N, fout);
  }
}

int main() {
  int N;
  ifstream fin("zerosum.in");
  fin >> N;
  fin.close();
  ofstream fout("zerosum.out");
  char signs[N - 1];
  recurse(signs, 0, N, fout);
  fout.close();
  return 0;
}

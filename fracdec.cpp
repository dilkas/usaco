/*
  ID: paulius10
  PROG: fracdec
  LANG: C++
*/

#include <fstream>
#include <sstream>
#include <stdlib.h>

#define LINE 76

using namespace std;

void print(ofstream& fout, stringstream& ss, int& counter) {
  char c;
  while (ss.get(c)) {
    if (counter == LINE) {
      fout << endl;
      counter = 0;
    }
    fout << c;
    counter++;
  }
}

int power(int n, int d) {
  int p;
  int divisor = 1;
  for (p = 0; n % divisor == 0; p++) divisor *= d;
  return p;
}

void divide(ofstream& fout, int& N, int D, int& counter) {
  int q = N / D;
  stringstream ss;
  ss << q;
  print(fout, ss, counter);
  N = 10 * (N - D * q);
}

void abort(ofstream& fout, int N, int& counter, string c = "") {
  if (N == 0) {
    stringstream ss;
    ss << c;
    print(fout, ss, counter);
    fout << endl;
    fout.close();
    exit(0);
  }
}

int main() {
  int N, D;
  ifstream fin("fracdec.in");
  fin >> N >> D;
  fin.close();
  int counter = 0;
  int m = 0;
  for (int n = 2; n <= 5; n += 3) m = max(m, power(D, n) - power(N, n));
  ofstream fout("fracdec.out");
  divide(fout, N, D, counter);
  stringstream ss;
  ss << '.';
  print(fout, ss, counter);
  abort(fout, N, counter, "0");
  for (int i = 0; i < m; i++) divide(fout, N, D, counter);
  abort(fout, N, counter);
  stringstream ss2;
  ss2 << '(';
  print(fout, ss2, counter);
  bool seen[D];
  for (int i = 0; i < D; i++) seen[i] = false;
  while (N > 0) {
    int remainder = N / 10;
    if (seen[remainder]) break;
    seen[remainder] = true;
    divide(fout, N, D, counter);
  }
  stringstream ss3;
  ss3 << ')';
  print(fout, ss3, counter);
  fout << endl;
  fout.close();
  return 0;
}

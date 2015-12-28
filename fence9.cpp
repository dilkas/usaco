/*
  ID: paulius10
  PROG: fence9
  LANG: C++
*/

#include <math.h>
#include <algorithm>
#include <fstream>

using namespace std;

int my_floor(double x) {
  if (ceil(x) - x < 0.0001) return ceil(x);
  return floor(x);
}

int my_ceil(double x) {
  if (x - floor(x) < 0.0001) return floor(x);
  return ceil(x);
}

int main() {
  ifstream fin("fence9.in");
  int n, m, p;
  fin >> n >> m >> p;
  fin.close();
  unsigned long long count = 0;
  double c1 = (double) m / n;
  double c2 = (double) m / (n - p);
  for (int x = 1; x < min(p, n); x++)
    count += my_ceil(c1 * x) - 1;
  if (n < p) {
    for (int x = (n)? n : 1; x < p; x++)
      count += my_ceil(c2 * (x - p)) - 1;
  } else if (p < n) {
    for (int x = (p) ? p : 1; x < n; x++)
      count += my_ceil(c1 * x) - my_floor(c2 * (x - p)) - 1;
  }
  ofstream fout("fence9.out");
  fout << count << endl;
  fout.close();
  return 0;
}

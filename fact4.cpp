/*
  ID: paulius10
  LANG: C++
  PROG: fact4
*/

#include <fstream>

using namespace std;

int main() {
  int N;
  ifstream fin("fact4.in");
  fin >> N;
  fin.close();

  // N! = 2^k * 5^m * n => remove 10^min(k, m)
  int twosCount = 0;
  int fivesCount = 0;
  int factorialMod10 = 1;
  for (int n = 1; n <= N; n++) {
    int simplifiedN = n;
    while (simplifiedN % 2 == 0) {
      twosCount++;
      simplifiedN /= 2;
    }
    while (simplifiedN % 5 == 0) {
      fivesCount++;
      simplifiedN /= 5;
    }
    factorialMod10 = (factorialMod10 * simplifiedN) % 10;
  }

  for (int i = 0; i < twosCount - fivesCount; i++)
    factorialMod10 = (factorialMod10 * 2) % 10;
  for (int i = 0; i < fivesCount - twosCount; i++)
    factorialMod10 = (factorialMod10 * 5) % 10;

  ofstream fout("fact4.out");
  fout << factorialMod10 << endl;
  fout.close();
  return 0;
}

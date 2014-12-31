/*
  ID: paulius10
  PROG: ariprog
  LANG: C++
*/

#include <fstream>
#include <set>
#include <utility>

using namespace std;

int main() {
  ifstream fin("ariprog.in");
  int N, M;
  fin >> N >> M;
  int MAX = 2 * M * M;
  fin.close();
  set<pair<int, int> > progressions;
  bool bisquary[MAX + 1];
  for (int i = 0; i <= MAX; i++)
    bisquary[i] = false;
  for (int p = 0; p <= M; p++) {
    for (int q = 0; q <= M; q++) {
      bisquary[p * p + q * q] = true;
    }
  }
  for (int a = 0; a < MAX; a++) {
    if (!bisquary[a]) continue;
    for (int b = 1; a + (N - 1) * b <= MAX; b++) {
      bool wrong = false;
      int max_n = a + (N - 1) * b;
      for (int n = a + b; n <= max_n; n += b) {
	if (!bisquary[n]) {
	  wrong = true;
	  break;
	}
      }
      if (!wrong) {
	progressions.insert(make_pair(b, a));
      }
    }
  }
  ofstream fout("ariprog.out");
  if (progressions.size()) {
    for (set<pair<int, int> >::iterator it = progressions.begin(); it != progressions.end(); it++) {
      fout << (*it).second << " " << (*it).first << endl;
    }
  } else {
    fout << "NONE" << endl;
  }
  fout.close();
  return 0;
}

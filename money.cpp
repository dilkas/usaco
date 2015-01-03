/*
  ID: paulius10
  PROG: money
  LANG: C++
*/

#include <fstream>

using namespace std;

int main() {
  int V, N;
  ifstream fin("money.in");
  fin >> V >> N;
  int coins[V];
  for (int i = 0; i < V; i++) fin >> coins[i];
  fin.close();
  long long ways[V + 1][N + 1];
  ways[0][0] = 1;
  for (int i = 1; i <= N; i++) ways[0][i] = 0;
  for (int i = 1; i <= V; i++) {
    for (int j = 0; j <= N; j++) {
      ways[i][j] = 0;
      for (int n = 0; n <= j; n += coins[i - 1]) ways[i][j] += ways[i - 1][j - n];
    }
  }
  ofstream fout("money.out");
  fout << ways[V][N] << endl;
  fout.close();
  return 0;
}

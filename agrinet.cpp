/*
  ID: paulius10
  PROG: agrinet
  LANG: C++
*/

#include <fstream>
#include <limits>

using namespace std;

int main() {
  ifstream fin("agrinet.in");
  int N;
  fin >> N;
  int weight[N][N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) fin >> weight[i][j];
  }
  fin.close();
  int distance[N];
  int source[N];
  int infinity = numeric_limits<int>::max();
  bool intree[N];
  for (int i = 0; i < N; i++) {
    distance[i] = infinity;
    intree[i] = false;
    source[i] = -1;
  }
  int treesize = 1;
  int treecost = 0;
  intree[0] = true;
  for (int i = 1; i < N; i++) {
    if (weight[0][i] < infinity) {
      distance[i] = weight[0][i];
      source[i] = 0;
    }
  }
  while (treesize < N) {
    int i = -1;
    for (int j = 0; j < N; j++) {
      if (!intree[j] && (i == -1 || distance[j] < distance[i])) i = j;
    }
    treesize++;
    treecost += distance[i];
    intree[i] = true;
    for (int j = 0; j < N; j++) {
      if (weight[i][j] < infinity && j != i && distance[j] > weight[i][j]) {
        distance[j] = weight[i][j];
        source[j] = i;
      }
    }
  }
  ofstream fout("agrinet.out");
  fout << treecost << endl;
  fout.close();
  return 0;
}

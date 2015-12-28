/*
  ID: paulius10
  PROG: ditch
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

int main() {
  ifstream fin("ditch.in");
  int N, M;
  fin >> N >> M;
  int capacity[M][M];
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) capacity[i][j] = 0;
  }
  for (int i = 0; i < N; i++) {
    int S, E, C;
    fin >> S >> E >> C;
    S--;
    E--;
    capacity[S][E] += C;
  }
  fin.close();
  int sink = M - 1;
  int totalflow = 0;
  while (true) {
    int prevnode[M], flow[M];
    bool visited[M];
    for (int i = 0; i < M; i++) {
      prevnode[i] = -1;
      flow[i] = 0;
      visited[i] = false;
    }
    flow[0] = numeric_limits<int>::max();
    int maxloc;
    while (true) {
      int maxflow = 0;
      maxloc = -1;
      for (int i = 0; i < M; i++) {
        if (flow[i] > maxflow && !visited[i]) {
          maxflow = flow[i];
          maxloc = i;
        }
      }
      if (maxloc == -1 || maxloc == sink) break;
      visited[maxloc] = true;
      for (int i = 0; i < M; i++) {
        if (capacity[maxloc][i] <= 0) continue;
        int m = min(maxflow, capacity[maxloc][i]);
        if (flow[i] < m) {
          prevnode[i] = maxloc;
          flow[i] = m;
        }
      }
    }
    if (maxloc == -1) break;
    int pathcapacity = flow[sink];
    totalflow += pathcapacity;
    int curnode = sink;
    while (curnode != 0) {
      int nextnode = prevnode[curnode];
      capacity[nextnode][curnode] -= pathcapacity;
      capacity[curnode][nextnode] += pathcapacity;
      curnode = nextnode;
    }
  }
  ofstream fout("ditch.out");
  fout << totalflow << endl;
  fout.close();
  return 0;
}

/*
  ID: paulius10
  PROG: stall4
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <limits>

using namespace std;

int main() {
  ifstream fin("stall4.in");
  int N, M;
  fin >> N >> M;
  int V = N + M + 2;
  int source = 0, sink = V - 1, cows_start = 1, cows_end = N;
  int stalls_start = N + 1, stalls_end = N + M;
  int capacity[V][V];
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) capacity[i][j] = 0;
  }
  for (int i = stalls_start; i <= stalls_end; i++) capacity[i][sink] = 1;
  for (int cow = cows_start; cow <= cows_end; cow++) {
    int S;
    fin >> S;
    capacity[0][cow] = 1;
    for (int j = 0; j < S; j++) {
      int stall;
      fin >> stall;
      capacity[cow][stall + N] = 1;
    }
  }
  fin.close();
  int totalflow = 0;
  while (true) {
    int prevnode[V], flow[V];
    bool visited[V];
    for (int i = 0; i < V; i++) {
      prevnode[i] = -1;
      flow[i] = 0;
      visited[i] = false;
    }
    flow[source] = numeric_limits<int>::max();
    int maxloc;
    while (true) {
      int maxflow = 0;
      maxloc = -1;
      for (int i = 0; i < V; i++) {
        if (flow[i] > maxflow && !visited[i]) {
          maxflow = flow[i];
          maxloc = i;
        }
      }
      if (maxloc == -1 || maxloc == sink) break;
      visited[maxloc] = true;
      for (int i = 0; i < V; i++) {
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
    while (curnode != source) {
      int nextnode = prevnode[curnode];
      capacity[nextnode][curnode] -= pathcapacity;
      capacity[curnode][nextnode] += pathcapacity;
      curnode = nextnode;
    }
  }
  ofstream fout("stall4.out");
  fout << totalflow << endl;
  fout.close();
  return 0;
}

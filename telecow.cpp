/*
  ID: paulius10
  PROG: telecow
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <limits>
#include <vector>

using namespace std;

int network_flow(int source, int sink, int N, bool enabled[],
                 vector<vector<int> > capacity) {
  if (source == sink)
    return numeric_limits<int>::max();
  int totalflow = 0;
  while (true) {
    // find path with highest capacity from source to sink
    // uses a modified dijkstra's algorithm
    int prevnode[N], flow[N];
    bool visited[N];
    for (int i = 0; i < N; i++) {
      prevnode[i] = -1;
      flow[i] = 0;
      visited[i] = (enabled[i]) ? false : true;
    }
    flow[source] = numeric_limits<int>::max();
    int maxloc;
    while (true) {
      int maxflow = 0;
      maxloc = -1;
      // find the unvisited node with the highest capacity to it
      for (int i = 0; i < N; i++) {
        if (flow[i] > maxflow && !visited[i]) {
          maxflow = flow[i];
          maxloc = i;
        }
      }
      if (maxloc == -1 || maxloc == sink)
        break;
      visited[maxloc] = true;
      // update its neighbors
      for (int i = 0; i < N; i++) {
        if (!capacity[maxloc][i])
          continue;
        int m = min(maxflow, capacity[maxloc][i]);
        if (flow[i] < m) {
          prevnode[i] = maxloc;
          flow[i] = m;
        }
      }
    }
    if (maxloc == -1) // no path
      break;
    int pathcapacity = flow[sink];
    totalflow += pathcapacity;
    // add that flow to the network, update capacity appropriately
    int curnode = sink;
    // for each arc, prevnode[curnode], curnode on path:
    while (curnode != source) {
      int nextnode = prevnode[curnode];
      capacity[nextnode][curnode] -= pathcapacity;
      capacity[curnode][nextnode] += pathcapacity;
      curnode = nextnode;
    }
  }
  return totalflow;
}

int main() {
  int N, M, c1, c2;
  ifstream fin("telecow.in");
  fin >> N >> M >> c1 >> c2;
  c1--;
  c2--;
  vector<vector<int> > capacity(2 * N, vector<int>(2 * N, 0));
  for (int i = 0; i < M; i++) {
    // id-1 is the in-node, N+id-1 is the out-node
    int id1, id2;
    fin >> id1 >> id2;
    id1--;
    id2--;
    // links from out-nodes to in-nodes of different nodes and from in-nodes to
    // out-nodes for each node individually
    capacity[id1][N + id1] = capacity[id2][N + id2] = capacity[N + id1][id2] =
      capacity[N + id2][id1] = 1;
  }
  fin.close();
  // used to conveniently disable nodes without going through all the edges
  bool enabled[2 * N];
  for (int i = 0; i < 2 * N; i++)
    enabled[i] = true;
  int remaining_flow = network_flow(N + c1, c2, 2 * N, enabled, capacity);
  ofstream fout("telecow.out");
  fout << remaining_flow << endl;
  bool first_number = true; // used to format output spacing
  for (int i = 0; i < N && remaining_flow; i++) {
    if (i == c1 || i == c2)
      continue;
    enabled[i] = enabled[N + i] = false;
    int new_flow = network_flow(N + c1, c2, 2 * N, enabled, capacity);
    if (new_flow < remaining_flow) {
      remaining_flow = new_flow;
      if (first_number) {
        fout << i + 1;
        first_number = false;
      } else {
        fout << " " << i + 1;
      }
    } else {
      enabled[i] = enabled[N + i] = true;
    }
  }
  fout << endl;
  fout.close();
}

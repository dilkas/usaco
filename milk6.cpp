/*
  ID: paulius10
  PROG: milk6
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <limits>
#include <vector>

#define MAX_M 1000

using namespace std;
typedef vector<vector<long long> > Matrix;

long long network_flow(long long N, Matrix capacity) {
  long long totalflow = 0;
  long long sink = N - 1;
  while (true) {
    long long prevnode[N];
    long long flow[N];
    bool visited[N];
    // find path with highest capacity from source to sink
    // uses a modified Dijkstra's algorithm
    for (long long i = 0; i < N; i++) {
      prevnode[i] = -1;
      flow[i] = 0;
      visited[i] = false;
    }
    flow[0] = numeric_limits<long long>::max();
    long long maxloc;
    while (true) {
      long long maxflow = 0;
      maxloc = -1;
      // find the unvisited node with the highest capacity to it
      for (long long i = 0; i < N; i++) {
        if (flow[i] > maxflow && !visited[i]) {
          maxflow = flow[i];
          maxloc = i;
        }
      }
      if (maxloc == -1 || maxloc == sink) break;
      visited[maxloc] = true;
      // update its neighbours
      for (long long i = 0; i < N; i++) {
        long long m = min(maxflow, capacity[maxloc][i]);
        if (flow[i] < m) {
          prevnode[i] = maxloc;
          flow[i] = m;
        }
      }
    }
    if (maxloc == -1) break; // no path
    long long pathcapacity = flow[sink];
    totalflow += pathcapacity;
    // add that flow to the network, update capacity appropriately
    long long curnode = sink;
    while (curnode != 0) {
      long long nextnode = prevnode[curnode];
      capacity[nextnode][curnode] -= pathcapacity;
      capacity[curnode][nextnode] += pathcapacity;
      curnode = nextnode;
    }
  }
  return totalflow;
}

vector<long long> truncated_dfs(long long N, long long M, long long C,
                                long long T, long long routes[][3],
                                vector<long long> removed_edges,
                                Matrix capacity) {
  vector<long long> failed;
  if (T == 0) {
    if (C == 0) return removed_edges;
    return failed;
  }
  for (long long i = (removed_edges.empty()) ? 0 : *removed_edges.rbegin() + 1;
       i < M; i++) {
    capacity[routes[i][0]][routes[i][1]] -= routes[i][2];
    removed_edges.push_back(i);
    if (network_flow(N, capacity) == C - routes[i][2]) {
      vector<long long> result = truncated_dfs(N, M, C - routes[i][2], T - 1,
                                               routes, removed_edges, capacity);
      if (!result.empty()) return result;
    }
    removed_edges.pop_back();
    capacity[routes[i][0]][routes[i][1]] += routes[i][2];
  }
  return failed;
}

int main() {
  ifstream fin("milk6.in");
  long long N, M;
  fin >> N >> M;
  Matrix capacity(N, vector<long long>(N, 0));
  Matrix capacity2(N, vector<long long>(N, 0));
  long long routes[M][3];
  for (long long i = 0; i < M; i++) {
    fin >> routes[i][0] >> routes[i][1] >> routes[i][2];
    capacity[--routes[i][0]][--routes[i][1]] += routes[i][2];
    capacity2[routes[i][0]][routes[i][1]] += (MAX_M + 1) * routes[i][2] + 1;
  }
  fin.close();
  long long C = network_flow(N, capacity);
  long long T = network_flow(N, capacity2) % (MAX_M + 1);
  vector<long long> no_removed_edges;
  vector<long long> removed_edges = truncated_dfs(N, M, C, T, routes,
                                                  no_removed_edges, capacity);
  ofstream fout("milk6.out");
  fout << C << " " << T << endl;
  for (vector<long long>::iterator it = removed_edges.begin();
       it != removed_edges.end(); it++)
    fout << *it + 1 << endl;
  fout.close();
  return 0;
}

/*
  ID: paulius10
  PROG: fence6
  LANG: C++
*/

#include <fstream>
#include <limits>
#include <set>
#include <vector>

using namespace std;

void input_edges(int s, int i, int N, int edge_to_vertices[][2],
                 vector<set<int> > &vertex_to_edges, ifstream &fin) {
  set<int> edges;
  edges.insert(s);
  for (int j = 0; j < N; j++) {
    int edge;
    fin >> edge;
    edges.insert(edge - 1);
  }
  int index = -1;
  int size = vertex_to_edges.size();
  for (int j = 0; j < size; j++) {
    if (vertex_to_edges[j] == edges) {
      index = j;
      break;
    }
  }
  if (index != -1) {
    edge_to_vertices[s][i] = index;
  } else {
    edge_to_vertices[s][i] = size;
    vertex_to_edges.push_back(edges);
  }
}

int dfs(int vertex, int distance, int min, bool visited[], int L[],
        int distances[], vector<set<int> > vertex_to_edges,
        int edge_to_vertices[][2]) {
  if (distances[vertex] >= 0) return distance - distances[vertex];
  distances[vertex] = distance;
  for (set<int>::iterator edge = vertex_to_edges[vertex].begin();
       edge != vertex_to_edges[vertex].end(); edge++) {
    if (visited[*edge]) continue;
    int new_distance = distance + L[*edge];
    if (new_distance >= min) continue;
    int neighbour = (edge_to_vertices[*edge][0] == vertex) ?
      edge_to_vertices[*edge][1] : edge_to_vertices[*edge][0];
    visited[*edge] = true;
    int d = dfs(neighbour, new_distance, min, visited, L, distances,
                vertex_to_edges, edge_to_vertices);
    visited[*edge] = false;
    if (d < min) min = d;
  }
  distances[vertex] = -1;
  return min;
}

int main() {
  ifstream fin("fence6.in");
  int N;
  fin >> N;
  int L[N], edge_to_vertices[N][2];
  vector<set<int> > vertex_to_edges;
  for (int i = 0; i < N; i++) {
    int s, N1, N2;
    fin >> s;
    s--;
    fin >> L[s] >> N1 >> N2;
    input_edges(s, 0, N1, edge_to_vertices, vertex_to_edges, fin);
    input_edges(s, 1, N2, edge_to_vertices, vertex_to_edges, fin);
  }
  fin.close();
  int size = vertex_to_edges.size();
  bool visited[N];
  for (int i = 0; i < N; i++) visited[i] = false;
  int distances[size];
  for (int i = 0; i < size; i++) distances[i] = -1;
  ofstream fout("fence6.out");
  fout << dfs(0, 0, numeric_limits<int>::max(), visited, L, distances,
              vertex_to_edges, edge_to_vertices)
       << endl;
  fout.close();
  return 0;
}

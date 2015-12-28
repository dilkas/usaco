/*
  ID: paulius10
  PROG: cowtour
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <limits>
#include <math.h>
#include <queue>
#include <utility>

#define PRECISION 6
#define DISTANCE(i, j) sqrt(pow(X[i] - X[j], 2) + pow(Y[i] - Y[j], 2))

using namespace std;

void dfs(string matrix[], int components[], int N, int i, int component) {
  if (components[i] != -1) return;
  components[i] = component;
  for (int j = 0; j < N; j++) {
    if (matrix[i][j] == '1') dfs(matrix, components, N, j, component);
  }
}

int main() {
  ifstream fin("cowtour.in");
  int N;
  fin >> N;
  int X[N];
  int Y[N];
  string matrix[N];
  for (int i = 0; i < N; i++) fin >> X[i] >> Y[i];
  for (int i = 0; i < N; i++) fin >> matrix[i];
  fin.close();
  double infinity = numeric_limits<double>::infinity();
  double distance[N][N];
  for (int i = 0; i < N; i++) {
    bool visited[N];
    for (int j = 0; j < N; j++) {
      distance[i][j] = infinity;
      visited[j] = false;
    }
    distance[i][i] = 0;
    priority_queue<pair<double, int> > q;
    q.push(make_pair(0, i));
    while (!q.empty()) {
      pair<double, int> p = q.top();
      q.pop();
      if (p.first == infinity) break;
      visited[p.second] = true;
      for (int j = 0; j < N; j++) {
        if (matrix[p.second][j] == '1') {
          double new_distance = distance[i][p.second] + DISTANCE(p.second, j);
          if (new_distance < distance[i][j]) {
            distance[i][j] = new_distance;
            q.push(make_pair(new_distance, j));
          }
        }
      }
    }
  }
  int components[N];
  int component = 0;
  for (int i = 0; i < N; i++) components[i] = -1;
  for (int i = 0; i < N; i++) {
    if (components[i] == -1) dfs(matrix, components, N, i, component++);
  }
  double diameters[component];
  for (int i = 0; i < component; i++) diameters[i] = 0;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < i; j++) {
      if (components[i] == components[j] &&
          distance[i][j] > diameters[components[i]])
        diameters[components[i]] = distance[i][j];
    }
  }
  double longest_paths[N];
  for (int i = 0; i < N; i++) {
    longest_paths[i] = 0;
    for (int j = 0; j < N; j++) {
      if (distance[i][j] > longest_paths[i] &&
          distance[i][j] < infinity)
        longest_paths[i] = distance[i][j];
    }
  }
  double min = infinity;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < i; j++) {
      if (components[i] != components[j]) {
        double new_diameter = max(max(diameters[components[i]],
                                      diameters[components[j]]),
                                  longest_paths[i] +
                                  DISTANCE(i, j) +
                                  longest_paths[j]);
        if (new_diameter < min) min = new_diameter;
      }
    }
  }
  ofstream fout("cowtour.out");
  fout << fixed << setprecision(PRECISION) << min << endl;
  fout.close();
  return 0;
}

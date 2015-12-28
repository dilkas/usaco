/*
  ID: paulius10
  PROG: comehome
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <limits>
#include <queue>
#include <utility>

#define SIZE 52
#define SOURCE 25

using namespace std;

int char2int(char c) {
  if (c <= 'Z') return c - 'A';
  return c - 'a' + 'Z' - 'A' + 1;
}

int main() {
  int infinity = numeric_limits<int>::max();
  int weight[SIZE][SIZE];
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) weight[i][j] = infinity;
    weight[i][i] = 0;
  }
  ifstream fin("comehome.in");
  int P;
  fin >> P;
  for (int i = 0; i < P; i++) {
    char a, b;
    int distance;
    fin >> a >> b >> distance;
    int p1 = char2int(a);
    int p2 = char2int(b);
    int new_weight = min(weight[p1][p2], distance);
    weight[p1][p2] = new_weight;
    weight[p2][p1] = new_weight;
  }
  fin.close();
  int distance[SIZE];
  bool visited[SIZE];
  for (int i = 0; i < SIZE; i++) {
    distance[i] = infinity;
    visited[i] = false;
  }
  distance[SOURCE] = 0;
  priority_queue<pair<int, int> > q;
  q.push(make_pair(0, SOURCE));
  while (!q.empty()) {
    pair<int, int> p = q.top();
    q.pop();
    visited[p.second] = true;
    for (int i = 0; i < SIZE; i++) {
      if (!visited[i] && weight[p.second][i] < infinity) {
        int new_distance = distance[p.second] + weight[p.second][i];
        if (new_distance < distance[i]) {
          distance[i] = new_distance;
          q.push(make_pair(-new_distance, i));
        }
      }
    }
  }
  int min = infinity;
  char minc;
  for (char i = 'A'; i < 'Z'; i++) {
    int d = distance[char2int(i)];
    if (d > 0 && d < min) {
      min = d;
      minc = i;
    }
  }
  ofstream fout("comehome.out");
  fout << minc << ' ' << min << endl;
  fout.close();
  return 0;
}

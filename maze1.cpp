/*
  ID: paulius10
  PROG: maze1
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <limits>
#include <queue>

#define DIRECTIONS 4
#define DOORS 2

using namespace std;

struct state {
  int i, j, distance;
};

bool operator<(const state& a, const state& b) {
  if (a.distance != b.distance) return a.distance > b.distance;
  if (a.j != b.j) return a.j > b.j;
  return a.i > b.i;
}

int main() {
  ifstream fin("maze1.in");
  int W, H;
  fin >> W >> H;
  W = 2 * W + 1;
  H = 2 * H + 1;
  char maze[H][W];
  for (int i = 0; i < H; i++) {
    fin.get();
    for (int j = 0; j < W; j++) maze[i][j] = fin.get();
  }
  fin.close();
  int distance[DOORS][H][W];
  bool visited[H][W];
  int infinity = numeric_limits<int>::max();
  int deltai[] = {-1, 0, 1, 0};
  int deltaj[] = {0, 1, 0, -1};
  int door = 0;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if ((maze[i][j] == ' ' || maze[i][j] == '\000') &&
          (i == 0 || i == H - 1 || j == 0 || j == W - 1)) {
        int i3 = i;
        int j3 = j;
        if (i == 0) i3++;
        else if (i == H - 1) i3--;
        else if (j == 0) j3++;
        else if (j == W - 1) j3--;
        priority_queue<state> q;
        for (int i2 = 0; i2 < H; i2++) {
          for (int j2 = 0; j2 < W; j2++) {
            distance[door][i2][j2] = infinity;
            visited[i2][j2] = false;
          }
        }
        distance[door][i3][j3] = 0;
        state s;
        s.i = i3;
        s.j = j3;
        s.distance = 0;
        q.push(s);
        while (!q.empty()) {
          state s = q.top();
          q.pop();
          if (s.distance == infinity) break;
          visited[s.i][s.j] = true;
          for (int k = 0; k < DIRECTIONS; k++) {
            int i2 = s.i + deltai[k];
            int j2 = s.j + deltaj[k];
            int reali = i2 + deltai[k];
            int realj = j2 + deltaj[k];
            if (reali >= 0 && reali < H && realj >= 0 && realj < W &&
                (maze[i2][j2] == ' ' || maze[i2][j2] == '\000')) {
              int newdistance = s.distance + 1;
              if (newdistance < distance[door][reali][realj]) {
                distance[door][reali][realj] = newdistance;
                if (!visited[reali][realj]) {
                  state s2;
                  s2.i = reali;
                  s2.j = realj;
                  s2.distance = distance[door][reali][realj];
                  q.push(s2);
                }
              }
            }
          }
        }
        door++;
      }
    }
  }
  int maxd = 0;
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      int mind = min(distance[0][i][j], distance[1][i][j]);
      if (mind > maxd && mind < infinity) maxd = mind;
    }
  }
  ofstream fout("maze1.out");
  fout << maxd + 1 << endl;
  fout.close();
  return 0;
}

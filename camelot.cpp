/*
  ID: paulius10
  PROG: camelot
  LANG: C++
*/

/*
1. Precompute shortest knight distances between every two squares (BFS).
2. For each final meeting location (780):
    2.1. For each knight (780):
        2.1.1. For each knight and king meeting location:
            2.1.1.1. Possibly update the king's shortest distance.
*/

#include <algorithm>
#include <fstream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#define N_MOVES 8

using namespace std;
struct state {
  int r, c, d;
};

int king_distance(int r1, int c1, int r2, int c2) {
  return max(abs(r1 - r2), abs(c1 - c2));
}

int main() {
  int moves[][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                    {1, -2}, {1, 2}, {2, -1}, {2, 1}};
  int infinity = numeric_limits<int>::max();
  ifstream fin("camelot.in");
  int R, C;
  fin >> R >> C;
  vector<pair<int, int> > pos;
  while (fin.good()) {
    char letter = '0';
    int digit = 0;
    fin >> letter >> digit;
    if (letter != '0' && digit != 0)
      pos.push_back(make_pair(digit - 1, (int) (letter - 'A')));
  }
  fin.close();
  int distances[R][C][R][C];
  for (int r1 = 0; r1 < R; r1++) {
    for (int c1 = 0; c1 < C; c1++) {
      for (int r2 = 0; r2 < R; r2++) {
        for (int c2 = 0; c2 < C; c2++)
          distances[r1][c1][r2][c2] = infinity;
      }
    }
  }
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      queue<state> q;
      state initial;
      initial.r = r;
      initial.c = c;
      initial.d = 0;
      q.push(initial);
      distances[r][c][r][c] = 0;
      while (!q.empty()) {
        state s = q.front();
        q.pop();
        for (int i = 0; i < N_MOVES; i++) {
          state next;
          next.r = s.r + moves[i][0];
          next.c = s.c + moves[i][1];
          next.d = s.d + 1;
          if (next.r >= 0 && next.r < R && next.c >= 0 && next.c < C &&
              distances[r][c][next.r][next.c] == infinity) {
            q.push(next);
            distances[r][c][next.r][next.c] = next.d;
          }
        }
      }
    }
  }
  int min_distance = infinity;
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      int k_distance = king_distance(r, c, pos[0].first, pos[0].second);
      int ds[pos.size() - 1];
      int max_diff = 0;
      bool next = false;
      for (int i = 1; i < pos.size(); i++) {
        ds[i - 1] = distances[r][c][pos[i].first][pos[i].second];
        if (ds[i - 1] == infinity) {
          next = true;
          break;
        }
      }
      if (next) continue;
      for (int i = 1; i < pos.size(); i++) {
        for (int tr = max(0, pos[0].first - 2);
             tr <= min(R - 1, pos[0].first + 2); tr++) {
          for (int tc = max(0, pos[0].second - 2);
               tc <= min(C - 1, pos[0].second + 2); tc++) {
            if (distances[pos[i].first][pos[i].second][tr][tc] == infinity ||
                distances[tr][tc][r][c] == infinity) {
              continue;
            }
            int diff = k_distance + ds[i - 1] -
              distances[pos[i].first][pos[i].second][tr][tc] -
              distances[tr][tc][r][c] -
              king_distance(pos[0].first, pos[0].second, tr, tc);
            if (diff > max_diff) max_diff = diff;
          }
        }
      }
      int total_distance = k_distance - max_diff;
      for (int i = 0; i < pos.size() - 1; i++) total_distance += ds[i];
      if (total_distance < min_distance) min_distance = total_distance;
    }
  }
  ofstream fout("camelot.out");
  fout << min_distance << endl;
  fout.close();
  return 0;
}

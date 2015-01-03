/*
  ID: paulius10
  PROG: ttwo
  LANG: C++
*/

#include <fstream>

#define DIRECTIONS 4
#define SIZE 10

using namespace std;

struct state {
  int i, j, d;
  bool operator==(const state& other) {
    return i == other.i && j == other.j;
  }
};

bool good(char grid[SIZE][SIZE], state s) {
  return (s.i >= 0 && s.i < SIZE && s.j >= 0 && s.j < SIZE &&
          grid[s.i][s.j] != '*');
}

state move(char grid[SIZE][SIZE], state s) {
  switch (s.d) {
  case 0:
    s.i--;
    if (good(grid, s)) return s;
    s.i++;
    s.d++;
    break;
  case 1:
    s.j++;
    if (good(grid, s)) return s;
    s.j--;
    s.d++;
    break;
  case 2:
    s.i++;
    if (good(grid, s)) return s;
    s.i--;
    s.d++;
    break;
  case 3:
    s.j--;
    if (good(grid, s)) return s;
    s.j++;
    s.d = 0;
    break;
  }
  return s;
}

int main() {
  ifstream fin("ttwo.in");
  char grid[SIZE][SIZE];
  state cows;
  cows.d = 0;
  state farmer;
  farmer.d = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      fin >> grid[i][j];
      if (grid[i][j] == 'C') {
        cows.i = i;
        cows.j = j;
      } else if (grid[i][j] == 'F') {
        farmer.i = i;
        farmer.j = j;
      }
    }
  }
  fin.close();
  bool visited[SIZE][SIZE][DIRECTIONS][SIZE][SIZE][DIRECTIONS];
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      for (int k = 0; k < DIRECTIONS; k++) {
        for (int l = 0; l < SIZE; l++) {
          for (int m = 0; m < SIZE; m++) {
            for (int n = 0; n < DIRECTIONS; n++)
              visited[i][j][k][l][m][n] = false;
          }
        }
      }
    }
  }
  int i;
  for (i = 1; ; i++) {
    cows = move(grid, cows);
    farmer = move(grid, farmer);
    if (cows == farmer) break;
    if (visited[cows.i][cows.j][cows.d][farmer.i][farmer.j][farmer.d]) {
      i = 0;
      break;
    }
    visited[cows.i][cows.j][cows.d][farmer.i][farmer.j][farmer.d] = true;
  }
  ofstream fout("ttwo.out");
  fout << i << endl;
  fout.close();
  return 0;
}

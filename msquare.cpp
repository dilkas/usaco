/*
  ID: paulius10
  PROG: msquare
  LANG: C++
*/

#include <fstream>
#include <map>
#include <queue>
#include <vector>

#define N_SQUARES 8
#define N_TRANSFORMATIONS 3
#define FIRST_LETTER 'A'

using namespace std;

struct state {
  vector<int> squares;
  string transformations;
};

bool equal(vector<int> a, vector<int> b) {
  for (int i = 0; i < N_SQUARES; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

int main() {
  int transformations[][N_SQUARES] = {{7, 6, 5, 4, 3, 2, 1, 0},
                                      {3, 0, 1, 2, 5, 6, 7, 4},
                                      {0, 6, 1, 3, 4, 2, 5, 7}};
  vector<int> target;
  ifstream fin("msquare.in");
  for (int i = 0; i < N_SQUARES; i++) {
    int square;
    fin >> square;
    target.push_back(square);
  }
  fin.close();
  ofstream fout("msquare.out");
  queue<state> Q;
  map<vector<int>, bool> discovered;
  state start;
  for (int i = 1; i <= N_SQUARES; i++) start.squares.push_back(i);
  Q.push(start);
  discovered[start.squares] = true;
  while (!Q.empty()) {
    state v = Q.front();
    Q.pop();
    if (equal(v.squares, target)) {
      fout << v.transformations.length() << endl << v.transformations << endl;
      fout.close();
      return 0;
    }
    for (int i = 0; i < N_TRANSFORMATIONS; i++) {
      state w;
      for (int j = 0; j < N_SQUARES; j++)
        w.squares.push_back(v.squares[transformations[i][j]]);
      if (!discovered[w.squares]) {
        w.transformations = v.transformations + (char) (FIRST_LETTER + i);
        Q.push(w);
        discovered[w.squares] = true;
      }
    }
  }
  fout.close();
  return 0;
}

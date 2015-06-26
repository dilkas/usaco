/*
  ID: paulius10
  PROG: shuttle
  LANG: C++
*/

#include <fstream>
#include <queue>
#include <vector>
#include <stdlib.h>

using namespace std;

struct state {
  vector<char> puzzle;
  vector<int> moves;
};

void check_and_print(state s, int N) {
  for (int i = 0; i < N; i++) {
    if (s.puzzle[i] != 'B') return;
  }
  if (s.puzzle[N] != ' ') return;
  for (int i = N + 1; i <= 2 * N; i++) {
    if (s.puzzle[i] != 'W') return;
  }
  ofstream fout("shuttle.out");
  for (int i = 0; i < s.moves.size(); i++) {
    if (i % 20 != 0) fout << " ";
    else if (i != 0) fout << endl;
    fout << s.moves[i];
  }
  fout << endl;
  fout.close();
  exit(0);
}

void enqueue(int i, int j, int size, state &s, queue<state> &q) {
  if (j < 0 || j >= size || s.puzzle[j] != ' ') return;
  state next;
  next.puzzle = s.puzzle;
  next.puzzle[j] = s.puzzle[i];
  next.puzzle[i] = s.puzzle[j];
  next.moves = s.moves;
  next.moves.push_back(i + 1);
  q.push(next);
}

int main() {
  ifstream fin("shuttle.in");
  int N;
  fin >> N;
  fin.close();
  int size = 2 * N + 1;
  state initial;
  for (int i = 0; i < N; i++) initial.puzzle.push_back('W');
  initial.puzzle.push_back(' ');
  for (int i = 0; i < N; i++) initial.puzzle.push_back('B');
  queue<state> q;
  q.push(initial);
  while (!q.empty()) {
    state s = q.front();
    q.pop();
    check_and_print(s, N);
    for (int i = 0; i < size; i++) {
      if (s.puzzle[i] == ' ') continue;
      int sign = (s.puzzle[i] == 'W') ? 1 : -1;
      enqueue(i, i + sign * 1, size, s, q);
      enqueue(i, i + sign * 2, size, s, q);
    }
  }
  return 0;
}

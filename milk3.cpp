/*
  ID: paulius10
  PROG: milk3
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <assert.h>

using namespace std;

struct state {
  int a, b, c;
  bool operator<(state s) const {
    if (a != s.a) return a < s.a;
    if (b != s.b) return b < s.b;
    return c < s.c;
  }
};

void magic(int A, int B, int C, int a, int b, int c, bool possibilities[], set<state> states) {
  assert(a <= A);
  assert(b <= B);
  assert(c <= C);
  assert(a >= 0);
  assert(b >= 0);
  assert(c >= 0);
  state s;
  s.a = a;
  s.b = b;
  s.c = c;
  if (states.find(s) != states.end()) return;
  states.insert(s);
  if (a == 0)
    possibilities[c] = true;
  // a -> b
  magic(A, B, C, max(a - B + b, 0), min(b + a, B), c, possibilities, states);
  // a -> c
  magic(A, B, C, max(a - C + c, 0), b, min(c + a, C), possibilities, states);
  // b -> a
  magic(A, B, C, min(a + b, A), max(b - A + a, 0), c, possibilities, states);
  // b -> c
  magic(A, B, C, a, max(b - C + c, 0), min(c + b, C), possibilities, states);
  // c -> a
  magic(A, B, C, min(a + c, A), b, max(c - A + a, 0), possibilities, states);
  // c -> b
  magic(A, B, C, a, min(b + c, B), max(c - B + b, 0), possibilities, states);
}

int main() {
  ifstream fin("milk3.in");
  ofstream fout("milk3.out");
  int A, B, C;
  fin >> A >> B >> C;
  fin.close();
  /*states[A + 1][B + 1][C + 1];
  for (int i = 0; i <= A; i++) {
    for (int j = 0; j <= B; j++) {
      for (int k = 0; k <= C; k++) {
	states[i][j][k] = false;
      }
    }
    }*/
  bool possibilities[C + 1];
  set<state> states;
  for (int i = 0; i <= C; i++) possibilities[i] = false;
  magic(A, B, C, 0, 0, C, possibilities, states);
  bool first = true;
  for (int i = 0; i <= C; i++) {
    if (possibilities[i]) {
      if (first) {
	fout << i;
	first = false;
      } else {
	fout << " " << i;
      }
    }
  }
  fout << endl;
  fout.close();
  return 0;
}

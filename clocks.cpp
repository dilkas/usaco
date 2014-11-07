/*
  ID: paulius10
  PROG: clocks
  LANG: C++
 */

#include <queue>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include <math.h>

using namespace std;

struct state {
  int clocks;
  state *parent;
  short move;
  bool operator<(state other) const {
    return clocks > other.clocks;
  }
};

int magic[9][2] = {{3, 1}, {12, 4}, {48, 16}, {192, 64}, {768, 256}, {3072, 1024}, {12288, 4096}, {49152, 16384}, {196608, 65536}};

void iterate(int &a, short i) {
  if ((a & magic[i][0]) == magic[i][0]) a -= magic[i][0];
  else a += magic[i][1];
}

state* move(state *clocks, int move) {
  state *n = new state;
  (*n).parent = clocks;
  (*n).move = move;
  (*n).clocks = (*clocks).clocks;
  switch (move) {
  case 1:
    iterate((*n).clocks, 0);
    iterate((*n).clocks, 1);
    iterate((*n).clocks, 3);
    iterate((*n).clocks, 4);
    break;
  case 2:
    iterate((*n).clocks, 0);
    iterate((*n).clocks, 1);
    iterate((*n).clocks, 2);
    break;
  case 3:
    iterate((*n).clocks, 1);
    iterate((*n).clocks, 2);
    iterate((*n).clocks, 4);
    iterate((*n).clocks, 5);
    break;
  case 4:
    iterate((*n).clocks, 0);
    iterate((*n).clocks, 3);
    iterate((*n).clocks, 6);
    break;
  case 5:
    iterate((*n).clocks, 1);
    iterate((*n).clocks, 3);
    iterate((*n).clocks, 4);
    iterate((*n).clocks, 5);
    iterate((*n).clocks, 7);
    break;
  case 6:
    iterate((*n).clocks, 2);
    iterate((*n).clocks, 5);
    iterate((*n).clocks, 8);
    break;
  case 7:
    iterate((*n).clocks, 3);
    iterate((*n).clocks, 4);
    iterate((*n).clocks, 6);
    iterate((*n).clocks, 7);
    break;
  case 8:
    iterate((*n).clocks, 6);
    iterate((*n).clocks, 7);
    iterate((*n).clocks, 8);
    break;
  case 9:
    iterate((*n).clocks, 4);
    iterate((*n).clocks, 5);
    iterate((*n).clocks, 7);
    iterate((*n).clocks, 8);
    break;
  }
  return n;
}

int main() {
  ifstream fin("clocks.in");
  ofstream fout("clocks.out");
  set<state> graph;
  state* root = new state;
  (*root).parent = NULL;
  (*root).move = 0;
  (*root).clocks = 0;
  for (int i = 0; i < 9; i++) {
    int t;
    fin >> t;
    if (t == 3) (*root).clocks += magic[i][1];
    else if (t == 6) (*root).clocks += magic[i][0] - magic[i][1];
    else if (t == 9) (*root).clocks += magic[i][0];
  }
  graph.insert(*root);
  queue<state*> q;
  q.push(root);
  while (!q.empty()) {
    state *st = q.front();
    q.pop();
    if ((*st).clocks == 0) {
      vector<short> moves;
      while ((*st).parent != NULL) {
	moves.push_back((*st).move);
	st = (*st).parent;
      }
      bool first = true;
      for (vector<short>::reverse_iterator rit = moves.rbegin(); rit != moves.rend(); rit++) {
	if (first) {
	  fout << *rit;
	  first = false;
	  continue;
	}
	fout << " " << *rit;
      }
      fout << endl;
      return 0;
    }
    for (short i = (*st).move; i < 10; i++) {
      state *temp = move(st, i);
      if (graph.find(*temp) == graph.end()) {
	graph.insert(*temp);
	q.push(temp);
      } else {
	delete temp;
      }
    }
  }
  return 0;
}

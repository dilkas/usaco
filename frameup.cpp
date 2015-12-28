/*
  ID: paulius10
  PROG: frameup
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <limits>

#define NUM_LETTERS 26

using namespace std;

struct Sides {
  int min_i, max_i, min_j, max_j;
};

bool no_in_edges(int j, bool exists[], bool adjacency_matrix[][NUM_LETTERS]) {
  for (int i = 0; i < NUM_LETTERS; i++) {
    if (exists[i] && adjacency_matrix[i][j]) return false;
  }
  return true;
}

void find_orderings(int letters_left, string ordering,
                    bool adjacency_matrix[][NUM_LETTERS], bool exists[],
                    ofstream &fout) {
  if (!letters_left) {
    fout << ordering << endl;
    return;
  }
  for (int i = 0; i < NUM_LETTERS; i++) {
    if (exists[i] && no_in_edges(i, exists, adjacency_matrix)) {
      exists[i] = false;
      find_orderings(letters_left - 1, ordering + (char)((int)'A' + i),
                     adjacency_matrix, exists, fout);
      exists[i] = true;
    }
  }
}

int main() {
  int H, W;
  ifstream fin("frameup.in");
  fin >> H >> W;
  int picture[H][W];
  for (int i = 0; i < H; i++) {
    string line;
    fin >> line;
    for (int j = 0; j < W; j++)
      picture[i][j] = (line[j] == '.') ? -1 : line[j] - 'A';
  }
  fin.close();

  bool exists[NUM_LETTERS];
  Sides sides[NUM_LETTERS];
  for (int i = 0; i < NUM_LETTERS; i++) {
    exists[i] = false;
    sides[i].min_i = sides[i].min_j = numeric_limits<int>::max();
    sides[i].max_i = sides[i].max_j = numeric_limits<int>::min();
  }
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      exists[picture[i][j]] = true;
      sides[picture[i][j]].min_i = min(sides[picture[i][j]].min_i, i);
      sides[picture[i][j]].max_i = max(sides[picture[i][j]].max_i, i);
      sides[picture[i][j]].min_j = min(sides[picture[i][j]].min_j, j);
      sides[picture[i][j]].max_j = max(sides[picture[i][j]].max_j, j);
    }
  }

  bool adjacency_matrix[NUM_LETTERS][NUM_LETTERS];
  for (int i = 0; i < NUM_LETTERS; i++) {
    for (int j = 0; j < NUM_LETTERS; j++) adjacency_matrix[i][j] = false;
  }
  for (int k = 0; k < NUM_LETTERS; k++) {
    if (exists[k]) {
      for (int i = sides[k].min_i; i <= sides[k].max_i; i++) {
        if (picture[i][sides[k].min_j] != k)
          adjacency_matrix[k][picture[i][sides[k].min_j]] = true;
        if (picture[i][sides[k].max_j] != k)
          adjacency_matrix[k][picture[i][sides[k].max_j]] = true;
      }
      for (int j = sides[k].min_j; j <= sides[k].max_j; j++) {
        if (picture[sides[k].min_i][j] != k)
          adjacency_matrix[k][picture[sides[k].min_i][j]] = true;
        if (picture[sides[k].max_i][j] != k)
          adjacency_matrix[k][picture[sides[k].max_i][j]] = true;
      }
    }
  }

  int ordering_length = 0;
  for (int i = 0; i < NUM_LETTERS; i++) {
    if (exists[i]) ordering_length++;
  }

  ofstream fout("frameup.out");
  find_orderings(ordering_length, "", adjacency_matrix, exists, fout);
  fout.close();
  return 0;
}

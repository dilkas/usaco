/*
  ID: paulius10
  PROG: rectbarn
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <set>
#include <stack>

using namespace std;

/*
  Fills the array[] with values representing how many columns to the left/right
  (depending on the parameter values) have heights >= to the current height.
  
  These parameters control the direction of the search. First value is used to
  go from left to right, second value is for the other direction.
  first_column: 0 or C - 1;
  check_column: C or -1;
  step: 1 or -1;
*/
void fill_array(int first_column, int check_column, int step, int C,
                int height[], int array[]) {
  stack<int> s;
  for (int c = first_column; c != check_column; c += step) {
    while (true) {
      if (s.empty()) {
        array[c] = step * c;
        if (step < 0)
          array[c] += C - 1;
        break;
      }
      if (height[s.top()] < height[c]) {
        array[c] = abs(c - s.top()) - 1;
        break;
      }
      s.pop();
    }
    s.push(c);
  }
}

int main() {
  int R, C, P;
  ifstream fin("rectbarn.in");
  fin >> R >> C >> P;
  // we have to use a set, R*C array takes up too much space
  set<pair<int, int> > damaged;
  for (int i = 0; i < P; ++i) {
    int r, c;
    fin >> r >> c;
    damaged.insert(make_pair(r - 1, c - 1));
  }
  fin.close();

  int max_area = 0;
  int *previous_height = NULL;
  for (int r = 0; r < R; ++r) {
    int *height = new int[C], left[C], right[C];
    // calculate the max height of a column with (r, c) as the bottom cell
    if (r == 0)
      for (int c = 0; c < C; ++c)
        height[c] = damaged.find(make_pair(r, c)) == damaged.end();
    else
      for (int c = 0; c < C; ++c)
        height[c] = (damaged.find(make_pair(r, c)) == damaged.end()) ?
          previous_height[c] + 1 : 0;

    fill_array(0, C, 1, C, height, left);
    fill_array(C - 1, -1, -1, C, height, right);
    for (int c = 0; c < C; ++c)
      max_area = max(max_area, height[c] * (left[c] + right[c] + 1));
    delete[] previous_height;
    previous_height = height;
  }
  ofstream fout("rectbarn.out");
  fout << max_area << endl;
  fout.close();
}

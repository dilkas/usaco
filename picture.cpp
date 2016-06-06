/*
  ID: paulius10
  PROG: picture
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

int main() {
  int N;
  ifstream fin("picture.in");
  fin >> N;
  int coordinates[N][4];
  set<int> sorted_coordinates[2];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 4; j++) {
      fin >> coordinates[i][j];
      // separate x and y coordinates
      sorted_coordinates[j % 2].insert(coordinates[i][j]);
    }
  }
  fin.close();
  int X = sorted_coordinates[0].size() - 1,
    Y = sorted_coordinates[1].size() - 1;

  // convert sets to vectors because we need indices, not iterators
  vector<int> original_coordinates[2];
  for (int i = 0; i < 2; i++)
    copy(sorted_coordinates[i].begin(), sorted_coordinates[i].end(),
         back_inserter(original_coordinates[i]));

  // coordinate compression
  for (int i = 0; i < N; i++)
    for (int j = 0; j < 4; j++)
      coordinates[i][j] = lower_bound(original_coordinates[j % 2].begin(),
                                      original_coordinates[j % 2].end(),
                                      coordinates[i][j]) -
        original_coordinates[j % 2].begin();

  // create a compressed representation of the picture
  // true means empty space between (x, y) and (x + 1, y + 1)
  bool picture[X][Y];
  for (int i = 0; i < X; i++)
    for (int j = 0; j < Y; j++)
      picture[i][j] = true;
  for (int i = 0; i < N; i++)
    for (int x = coordinates[i][0]; x < coordinates[i][2]; x++)
      for (int y = coordinates[i][1]; y < coordinates[i][3]; y++)
        picture[x][y] = false;

  int perimeter = 0;
  for (int i = 0; i < X; i++) {
    for (int j = 0; j < Y; j++) {
      if (picture[i][j])
        continue;
      int x_distance = original_coordinates[1][j + 1] -
        original_coordinates[1][j];
      // the x distance is an edge if either the top or the bottom is empty
      if (i == 0 || picture[i - 1][j])
        perimeter += x_distance;
      if (i == X - 1 || picture[i + 1][j])
        perimeter += x_distance;

      int y_distance = original_coordinates[0][i + 1] -
        original_coordinates[0][i];
      // the y distance is an edge if either the left or the right is empty
      if (j == 0 || picture[i][j - 1])
        perimeter += y_distance;
      if (j == Y - 1 || picture[i][j + 1])
        perimeter += y_distance;
    }
  }
  ofstream fout("picture.out");
  fout << perimeter << endl;
  fout.close();
}

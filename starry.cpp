/*
  ID: paulius10
  PROG: starry
  LANG: C++
*/

#include <fstream>
#include <limits>
#include <map>
#include <vector>

#define NUM_ROTATIONS 4
#define NUM_REFLECTIONS 2

using namespace std;
typedef vector<vector<char> > Matrix;

Matrix extract_cluster(char letter, int min_i, int max_i, int min_j, int max_j,
                       Matrix sky_map) {
  Matrix cluster;
  for (int i = min_i; i <= max_i; i++) {
    vector<char> line;
    for (int j = min_j; j <= max_j; j++) {
      if (sky_map[i][j] == letter) {
        line.push_back('1');
      } else {
        line.push_back('0');
      }
    }
    cluster.push_back(line);
  }
  return cluster;
}

Matrix rotate(Matrix cluster) {
  Matrix rotated;
  for (int i = 0; i < cluster[0].size(); i++) {
    vector<char> line;
    for (int j = 0; j < cluster.size(); j++)
      line.push_back(cluster[cluster.size() - j - 1][i]);
    rotated.push_back(line);
  }
  return rotated;
}

Matrix reflect(Matrix cluster) {
  Matrix reflected;
  for (int i = 0; i < cluster.size(); i++) {
    vector<char> line;
    for (int j = 0; j < cluster[0].size(); j++)
      line.push_back(cluster[i][cluster[i].size() - j - 1]);
    reflected.push_back(line);
  }
  return reflected;
}

void rename(char old_letter, char new_letter, int min_i, int max_i, int min_j,
            int max_j, Matrix &sky_map) {
  for (int i = min_i; i <= max_i; i++) {
    for (int j = min_j; j <= max_j; j++) {
      if (sky_map[i][j] == old_letter) sky_map[i][j] = new_letter;
    }
  }
}

bool flood_fill(char new_component, int H, int W, Matrix &component,
                map<Matrix, char> &clusters) {
  int num_visited, min_i, max_i, min_j, max_j;
  min_i = min_j = numeric_limits<int>::max();
  max_i = max_j = numeric_limits<int>::min();
  do {
    num_visited = 0;
    for (int i1 = 0; i1 < H; i1++) {
      for (int j1 = 0; j1 < W; j1++) {
        if (component[i1][j1] == '2') {
          num_visited++;
          component[i1][j1] = new_component;
          min_i = min(min_i, i1);
          max_i = max(max_i, i1);
          min_j = min(min_j, j1);
          max_j = max(max_j, j1);
          for (int i2 = i1 - 1; i2 <= i1 + 1; i2++) {
            for (int j2 = j1 - 1; j2 <= j1 + 1; j2++) {
              if (i2 >= 0 && i2 < H && j2 >= 0 && j2 < W &&
                  component[i2][j2] == '1' && !(i2 == i1 && j2 == j1))
                component[i2][j2] = '2';
            }
          }
        }
      }
    }
  } while (num_visited);
  Matrix cluster = extract_cluster(new_component, min_i, max_i, min_j, max_j,
                                   component);
  for (int i = 0; i < NUM_ROTATIONS; i++, cluster = rotate(cluster)) {
    for (int j = 0; j < NUM_REFLECTIONS; j++, cluster = reflect(cluster)) {
      if (clusters.find(cluster) != clusters.end()) {
        rename(new_component, clusters[cluster], min_i, max_i, min_j, max_j,
               component);
        return false;
      }
    }
  }
  clusters[cluster] = new_component;
  return true;
}

void find_components(int H, int W, Matrix &component) {
  map<Matrix, char> clusters;
  char num_components = 'a';
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (component[i][j] == '1') {
        component[i][j] = '2';
        if (flood_fill(num_components, H, W, component, clusters))
          num_components++;
      }
    }
  }
}

int main() {
  int W, H;
  ifstream fin("starry.in");
  fin >> W >> H;
  Matrix sky_map;
  for (int i = 0; i < H; i++) {
    string l;
    fin >> l;
    vector<char> v(l.begin(), l.end());
    sky_map.push_back(v);
  }
  fin.close();
  find_components(H, W, sky_map);
  ofstream fout("starry.out");
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) fout << sky_map[i][j];
    fout << endl;
  }
  fout.close();
  return 0;
}

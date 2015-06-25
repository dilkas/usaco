/*
  ID: paulius10
  PROG: race3
  LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;

vector<vector<int> > process_input_file() {
  vector<vector<int> > adjacency_list;
  ifstream fin("race3.in");
  while (true) {
    vector<int> list;
    int point;
    while (true) {
      fin >> point;
      if (point < 0) break;
      list.push_back(point);
    }
    if (point == -1) break;
    adjacency_list.push_back(list);
  }
  fin.close();
  return adjacency_list;
}

void flood_fill(int new_component, int component[],
                vector<vector<int> > adjacency_list) {
  int num_visited;
  do {
    num_visited = 0;
    for (int i = 0; i < adjacency_list.size(); i++) {
      if (component[i] == -2) {
        num_visited++;
        component[i] = new_component;
        for (vector<int>::iterator j = adjacency_list[i].begin();
             j != adjacency_list[i].end(); j++) {
          if (component[*j] == -1) component[*j] = -2;
        }
      }
    }
  } while (num_visited != 0);
}

vector<int> find_unavoidable_points(vector<vector<int> > adjacency_list) {
  int size = adjacency_list.size();
  vector<int> unavoidable;
  for (int point = 1; point < size - 1; point++) {
    int num_components = 0, component[size];
    for (int i = 0; i < size; i++) component[i] = -1;
    component[point] = 0;
    for (int i = 0; i < size; i++) {
      if (component[i] == -1) {
        num_components++;
        component[i] = -2;
        flood_fill(num_components, component, adjacency_list);
      }
    }
    if (num_components > 1) unavoidable.push_back(point);
  }
  return unavoidable;
}

void mark_reachable_points(int point, int finish, vector<bool> &visited,
                           vector<vector<int> > adjacency_list) {
  if (visited[point]) return;
  visited[point] = true;
  for (vector<int>::iterator next_point = adjacency_list[point].begin();
       next_point != adjacency_list[point].end(); next_point++) {
    mark_reachable_points(*next_point, finish, visited, adjacency_list);
  }
}

bool no_outgoing_arrows(int splitting_point, vector<int> outgoing,
                        vector<bool> first) {
  for (vector<int>::iterator point = outgoing.begin(); point != outgoing.end();
       point++) {
    if (first[*point] && *point != splitting_point) return false;
  }
  return true;
}

bool no_common_arrows(vector<bool> first, vector<bool> second,
                      vector<vector<int> > adjacency_list) {
  for (int i = 0; i < adjacency_list.size(); i++) {
    for (vector<int>::iterator j = adjacency_list[i].begin();
         j != adjacency_list[i].end(); j++) {
      if (!((first[i] && first[*j]) || (second[i] && second[*j]))) return false;
    }
  }
  return true;
}

bool no_common_points(int splitting_point, vector<bool> first,
                      vector<bool> second) {
  for (int i = 0; i < first.size(); i++) {
    if (first[i] == second[i] && i != splitting_point) return false;
  }
  return true;
}

vector<int> find_splitting_points(vector<int> unavoidable,
                                  vector<vector<int> > adjacency_list) {
  int size = adjacency_list.size();
  vector<int> splitting;
  for (vector<int>::iterator splitting_point = unavoidable.begin();
       splitting_point != unavoidable.end(); splitting_point++) {
    vector<bool> first(size, false), second(size, false);
    first[*splitting_point] = second[size - 1] = true;
    mark_reachable_points(0, *splitting_point, first, adjacency_list);
    mark_reachable_points(*splitting_point, size - 1, second, adjacency_list);
    if (no_outgoing_arrows(*splitting_point, adjacency_list[*splitting_point],
                           first) &&
        no_common_arrows(first, second, adjacency_list) &&
        no_common_points(*splitting_point, first, second)) {
      splitting.push_back(*splitting_point);
    }
  }
  return splitting;
}

void output(ofstream &fout, vector<int> v) {
  fout << v.size();
  for (int i = 0; i < v.size(); i++) fout << " " << v[i];
  fout << endl;
}

int main() {
  vector<vector<int> > adjacency_list = process_input_file();
  vector<int> unavoidable = find_unavoidable_points(adjacency_list);
  vector<int> splitting = find_splitting_points(unavoidable, adjacency_list);
  ofstream fout("race3.out");
  output(fout, unavoidable);
  output(fout, splitting);
  fout.close();
  return 0;
}

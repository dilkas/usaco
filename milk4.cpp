/*
  ID: paulius10
  PROG: milk4
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct State {
  vector<int> indices;
  bool operator<(const State &other) const {
    if (indices.size() != other.indices.size())
      return indices.size() > other.indices.size();
    for (int i = 0; i < indices.size(); i++) {
      if (indices[i] != other.indices[i]) return indices[i] > other.indices[i];
    }
    return false;
  }
};

bool works(vector<int> &indices, int Q, int pail_value[]) {
  if (Q == 0) return true;
  int last_index = *indices.rbegin();
  if (indices.size() == 1) return Q % pail_value[last_index] == 0;
  indices.pop_back();
  for (int i = 0, remaining_q = Q % pail_value[last_index];
       i < pail_value[last_index] && remaining_q < Q; i++,
         remaining_q += pail_value[last_index]) {
    if (works(indices, remaining_q, pail_value)) {
      indices.push_back(last_index);
      return true;
    }
  }
  indices.push_back(last_index);
  return false;
}

int main() {
  int Q, P;
  ifstream fin("milk4.in");
  fin >> Q >> P;
  int pail_value[P];
  for (int i = 0; i < P; i++) fin >> pail_value[i];
  fin.close();
  sort(pail_value, pail_value + P);
  priority_queue<State> queue;
  for (int i = 0; i < P; i++) {
    State initial;
    initial.indices.push_back(i);
    queue.push(initial);
  }
  while (!queue.empty()) {
    State state = queue.top();
    queue.pop();
    if (works(state.indices, Q, pail_value)) {
      ofstream fout("milk4.out");
      fout << state.indices.size();
      for (vector<int>::iterator it = state.indices.begin();
           it != state.indices.end(); it++)
        fout << ' ' << pail_value[*it];
      fout << endl;
      fout.close();
      return 0;
    }
    for (int i = *state.indices.rbegin() + 1; i < P; i++) {
      State next;
      next.indices = state.indices;
      next.indices.push_back(i);
      queue.push(next);
    }
  }
  return 0;
}

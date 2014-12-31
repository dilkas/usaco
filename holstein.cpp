/*
  ID: paulius10
  PROG: holstein
  LANG: C++
*/

#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct state {
  int startingIndex;
  vector<int> remainingVitamins;
  vector<int> usedFeeds;
};

int main() {
  ifstream fin("holstein.in");
  int V;
  fin >> V;
  int vitamins[V];
  for (int i = 0; i < V; i++) fin >> vitamins[i];
  int G;
  fin >> G;
  int feeds[G][V];
  for (int i = 0; i < G; i++) {
    for (int j = 0; j < V; j++) fin >> feeds[i][j];
  }
  fin.close();
  state first;
  first.startingIndex = 0;
  for (int i = 0; i < V; i++) first.remainingVitamins.push_back(vitamins[i]);
  queue<state> q;
  q.push(first);
  while (!q.empty()) {
    state current = q.front();
    q.pop();
    bool ok = true;
    for (int i = 0; i < V; i++) {
      if (current.remainingVitamins[i] > 0) {
        ok = false;
        break;
      }
    }
    if (ok) {
      ofstream fout("holstein.out");
      fout << current.usedFeeds.size() << " " << current.usedFeeds[0];
      for (int i = 1; i < current.usedFeeds.size(); i++)
        fout << " " << current.usedFeeds[i];
      fout << endl;
      fout.close();
      return 0;
    }
    for (int i = current.startingIndex; i < G; i++) {
      state newState;
      newState.startingIndex = i + 1;
      for (int j = 0; j < V; j++) {
        newState.remainingVitamins.push_back(current.remainingVitamins[j] -
                                             feeds[i][j]);
      }
      for (int j = 0; j < current.usedFeeds.size(); j++)
        newState.usedFeeds.push_back(current.usedFeeds[j]);
      newState.usedFeeds.push_back(i + 1);
      q.push(newState);
    }
  }
  return 0;
}

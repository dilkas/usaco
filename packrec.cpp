/*
  ID: paulius10
  PROG: packrec
  LANG: C++
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

vector<vector<int> > deep_copy_without(vector<vector<int> > a, int i) {
  vector<vector<int> > b;
  for (int j = 0; j < a.size(); j++) {
    if (j == i) continue;
    vector<int> t;
    for (vector<int>::iterator it2 = a[j].begin(); it2 != a[j].end(); it2++)
      t.push_back(*it2);
    b.push_back(t);
  }
  return b;
}

vector<vector<vector<int> > > rotations(vector<vector<int> > packages, int i = 0) {
  vector<vector<vector<int> > > v;
  if (i == 4) {
    v.push_back(packages);
    return v;
  }
  for (int j = 0; j < 2; j++) {
    int t = packages[i][0];
    packages[i][0] = packages[i][1];
    packages[i][1] = t;
    vector<vector<vector<int> > > results = rotations(packages, i + 1);
    for (vector<vector<vector<int> > >::iterator it = results.begin(); it != results.end(); it++)
      v.push_back(*it);
  }
  return v;
}

vector<vector<vector<int> > > permutations(vector<vector<int> > packages, vector<vector<int> > p, bool used[], int i = 0) {
  vector<vector<vector<int> > > v;
  if (i == 4) {
    v.push_back(p);
    return v;
  }
  for (int j = 0; j < packages.size(); j++) {
    if (used[j]) continue;
    p.push_back(packages[j]);
    used[j] = true;
    vector<vector<vector<int> > > results = permutations(packages, p, used, i + 1);
    for (vector<vector<vector<int> > >::iterator it2 = results.begin(); it2 != results.end(); it2++)
      v.push_back(*it2);
    p.pop_back();
    used[j] = false;
  }
  return v;
}

void update(int p, int S, int& minS, set<int>& ps) {
  if (minS == -1 || S < minS) {
    minS = S;
    ps.clear();
    ps.insert(p);
  } else if (S == minS) ps.insert(p);
}

int main() {
  ifstream fin("packrec.in");
  ofstream fout("packrec.out");
  vector<vector<int> > packages;
  for (int i = 0; i < 4; i++) {
    vector<int> v;
    int a, b;
    fin >> a >> b;
    v.push_back(a);
    v.push_back(b);
    packages.push_back(v);
  }
  vector<vector<vector<int> > > states;
  vector<vector<vector<int> > > temp = rotations(packages);
  for (vector<vector<vector<int> > >::iterator it = temp.begin(); it != temp.end(); it++) {
    vector<vector<int> > t;
    bool used[] = {false, false, false, false};
    vector<vector<vector<int> > > p = permutations(*it, t, used);
    for (vector<vector<vector<int> > >::iterator it2 = p.begin(); it2 != p.end(); it2++)
      states.push_back(*it2);
  }
  int minS = -1;
  set<int> ps;
  for (vector<vector<vector<int> > >::iterator it = states.begin(); it != states.end(); it++) {
    int x = (*it)[0][0] + (*it)[1][0] + (*it)[2][0] + (*it)[3][0];
    int y = max((*it)[0][1], max((*it)[1][1], max((*it)[2][1], (*it)[3][1])));
    update(min(x, y), x * y, minS, ps);
    x = max((*it)[0][0] + (*it)[1][0] + (*it)[2][0], (*it)[3][0]);
    y = max((*it)[0][1], max((*it)[1][1], (*it)[2][1])) + (*it)[3][1];
    update(min(x, y), x * y, minS, ps);
    x = max((*it)[0][0] + (*it)[1][0], (*it)[3][0]) + (*it)[2][0];
    y = max(max((*it)[0][1], (*it)[1][1]) + (*it)[3][1] ,(*it)[2][1]);
    update(min(x, y), x * y, minS, ps);
    x = (*it)[0][0] + max((*it)[1][0], (*it)[2][0]) + (*it)[3][0];
    y = max((*it)[0][1], max((*it)[1][1] + (*it)[2][1], (*it)[3][1]));
    update(min(x, y), x * y, minS, ps);
    x = max((*it)[0][0], (*it)[1][0]) + (*it)[2][0] + (*it)[3][0];
    y = max((*it)[0][1] + (*it)[1][1], max((*it)[2][1], (*it)[3][1]));
    update(min(x, y), x * y, minS, ps);
    x = max((*it)[0][0] + (*it)[1][0], max((*it)[0][0] + (*it)[2][0], (*it)[3][0] + (*it)[2][0]));
    y = max((*it)[0][1] + (*it)[3][1], max((*it)[1][1] + (*it)[3][1], (*it)[1][1] + (*it)[2][1]));
    update(min(x, y), x * y, minS, ps);
  }
  fout << minS << endl;
  for (set<int>::iterator it = ps.begin(); it != ps.end(); it++)
  fout << *it << " " << minS / (*it) << endl;
  return 0;
}

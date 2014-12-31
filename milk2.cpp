/*
  ID: paulius10
  PROG: milk2
  LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool comp(pair<int, int> a, pair<int, int> b) {
  return a.first <= b.first;
}

int main() {
  ofstream fout ("milk2.out");
  ifstream fin ("milk2.in");
  int N;
  fin >> N;
  vector<pair<int, int> > intervals;
  for (int i = 0; i < N; i++) {
    int a, b;
    fin >> a >> b;
    intervals.push_back(make_pair(a, b));
  }
  sort(intervals.begin(), intervals.end(), comp);
  bool changed = true;
  while (changed) {
    changed = false;
    for (int i = 1; i < intervals.size(); i++) {
      if (intervals[i].first <= intervals[i - 1].second) {
	intervals[i - 1].second = max(intervals[i - 1].second, intervals[i].second);
	for (vector<pair<int, int> >::iterator it = intervals.begin(); it != intervals.end(); it++) {
	  if (*it == intervals[i]) {
	    intervals.erase(it);
	    break;
	  }
	}
	changed = true;
	break;
      }
    }
  }
  int first = 0;
  for (vector<pair<int, int> >::iterator it = intervals.begin(); it != intervals.end(); it++)
    first = max(first, (*it).second - (*it).first);
  int second = 0;
  for (int i = 1; i < intervals.size(); i++) {
    second = max(second, intervals[i].first - intervals[i - 1].second);
  }
  fout << first << " " << second << endl;
  return 0;
}

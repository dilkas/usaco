/*
  ID: paulius10
  PROG: lamps
  LANG: C++
*/

#include <fstream>
#include <set>

using namespace std;

void turn(ifstream &fin, string &requirements, char value) {
  while (true) {
    int index;
    fin >> index;
    if (index == -1) break;
    requirements[index - 1] = value;
  }
}

void change(string &configuration, int i) {
  if (configuration[i] == '1') configuration[i] = '0';
  else configuration[i] = '1';
}

string button(string configuration, int number) {
  switch (number) {
  case 1:
    for (int i = 0; i < configuration.length(); i++) change(configuration, i);
    return configuration;
    break;
  case 2:
    for (int i = 0; i < configuration.length(); i += 2)
      change(configuration, i);
    return configuration;
    break;
  case 3:
    for (int i = 1; i < configuration.length(); i += 2)
      change(configuration, i);
    return configuration;
    break;
  default:
    for (int i = 0; i < configuration.length(); i += 3)
      change(configuration, i);
    return configuration;
  }
}

void dfs(string lamps, int c, int N, int C, string requirements,
         set<string> &solutions, int startFrom) {
  if (c > C) return;
  if (c <= C && c % 2 == C % 2) {
    bool ok = true;
    for (int i = 0; i < N; i++) {
      if (requirements[i] != '2' && lamps[i] != requirements[i]) ok = false;
    }
    if (ok) solutions.insert(lamps);
  }
  for (int b = startFrom; b <= 4; b++) {
    dfs(button(lamps, b), c + 1, N, C, requirements, solutions, b + 1);
  }
}

int main() {
  ifstream fin("lamps.in");
  int N, C;
  fin >> N >> C;
  string requirements;
  for (int i = 0; i < N; i++) requirements += "2";
  turn(fin, requirements, '1');
  turn(fin, requirements, '0');
  fin.close();
  string lamps;
  for (int i = 0; i < N; i++) lamps += "1";
  set<string> solutions;
  dfs(lamps, 0, N, C, requirements, solutions, 1);
  ofstream fout("lamps.out");
  if (solutions.size() == 0) {
    fout << "IMPOSSIBLE" << endl;
    return 0;
  }
  for (set<string>::iterator it = solutions.begin(); it != solutions.end();
       it++) {
    fout << *it << endl;
  }
  fout.close();
  return 0;
}

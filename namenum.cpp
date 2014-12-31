/*
  ID: paulius10
  PROG: namenum
  LANG: C++
 */

#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <set>

using namespace std;

bool filter(string number, vector<string> d, map<char,string> m, string name, set<string> prefixes, ofstream &fout) {
  if (number == ""){
    if (binary_search(d.begin(), d.end(), name))
      fout << name << endl;
    return true;
  }
  if (prefixes.find(name) == prefixes.end()) return false;
  bool ret = false;
  for (int i = 0; i < 3; i++) {
    string newnum;
    if (number.length() == 1) newnum = "";
    else newnum = number.substr(1);
    if (filter(newnum, d, m, name + m[number[0]][i], prefixes, fout)) ret = true;
  }
  return ret;
}

int main() {
  ifstream fin ("namenum.in");
  ifstream dict ("dict.txt");
  ofstream fout ("namenum.out");
  vector<string> d;
  set<string> prefixes;
  while (dict.good()) {
    string s;
    dict >> s;
    d.push_back(s);
    for (int i = 0; i <= s.length(); i++) prefixes.insert(s.substr(0, i));
  }
  string number;
  fin >> number;
  map<char,string> m;
  m['2'] = "ABC";
  m['3'] = "DEF";
  m['4'] = "GHI";
  m['5'] = "JKL";
  m['6'] = "MNO";
  m['7'] = "PRS";
  m['8'] = "TUV";
  m['9'] = "WXY";
  if (!filter(number, d, m, "", prefixes, fout)) fout << "NONE" << endl;
  return 0;
}

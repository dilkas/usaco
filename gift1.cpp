/*
  ID: paulius10
  PROG: gift1
  LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
  ofstream fout ("gift1.out");
  ifstream fin ("gift1.in");
  int NP;
  fin >> NP;
  map<string,int> gift;
  string name;
  string names[NP];
  for (int i = 0; i < NP; i++) {
    fin >> name;
    gift[name] = 0;
    names[i] = name;
  }
  int money, number;
  for (int i = 0; i < NP; i++) {
    fin >> name >> money >> number;
    gift[name] + money;
    for (int j = 0; j < number; j++) {
      string name2;
      fin >> name2;
      gift[name2] += money / number;
      gift[name] -= money / number;
    }
  }
  for (int i = 0; i < NP; i++) {
    fout << names[i] << " " << gift[names[i]] << endl;
  }
  fout.close();
  fin.close();
  return 0;
}

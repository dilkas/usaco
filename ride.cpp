/*
ID: paulius10
PROG: ride
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int ride(string s) {
  int q = 1;
  for (int i = 0; i < s.length(); i++) {
    q *= s[i] - 'A' + 1;
  }
  return q;
}

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string a, b;
    fin >> a >> b;
    if (ride(a) % 47 == ride(b) % 47) {
      fout << "GO" << endl;
    } else {
      fout << "STAY" << endl;
    }
    return 0;
}

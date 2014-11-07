/*
  ID: paulius10
  PROG: runround
  LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;

bool allTouched(bool touched[], int size) {
  for (int i = 0; i < size; i++) {
    if (!touched[i]) return false;
  }
  return true;
}

bool unique(vector<int> digits) {
  bool found[10];
  for (int i = 0; i < 10; i++) found[i] = false;
  for (int i = 0; i < digits.size(); i++) {
    if (!found[digits[i]]) found[digits[i]] = true;
    else return false;
  }
  return true;
}

bool ok(vector<int> digits) {
  if (!unique(digits)) return false;
  int size = digits.size();
  bool touched[size];
  for (int i = 0; i < size; i++) touched[i] = false;
  int index = size - 1;
  do {
    touched[index] = true;
    index = (index - digits[index]) % size;
    if (index < 0) index += size;
  } while(!touched[index]);
  return allTouched(touched, size) && index == size - 1;
}

void next(vector<int> &digits) {
  for (int i = 0; i < digits.size(); i++) {
    digits[i] = (digits[i] + 1) % 10;
    if (digits[i] != 0) return;
  }
  digits.push_back(1);
}

int main() {
  ifstream fin("runround.in");
  int M;
  fin >> M;
  fin.close();
  vector<int> digits;
  while (M > 0) {
    digits.push_back(M % 10);
    M /= 10;
  }
  do {
    next(digits);
  } while (!ok(digits));
  ofstream fout("runround.out");
  for (vector<int>::reverse_iterator it = digits.rbegin(); it != digits.rend(); it++)
    fout << *it;
  fout << endl;
  fout.close();
  return 0;
}

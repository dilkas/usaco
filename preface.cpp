/*
  ID: paulius10
  PROG: preface
  LANG: C++
*/

#include <fstream>

#define NUMBER_OF_NUMERALS 7

using namespace std;

void calculate(int number, int counters[], int values[]) {
  for (int i = NUMBER_OF_NUMERALS - 1; i >= 0; i--) {
    while (number >= values[i]) {
      counters[i]++;
      number -= values[i];
    }
    if (i >= 2 && number >= values[i] - values[i - 2] && i % 2 == 0) {
      counters[i]++;
      counters[i - 2]++;
      number -= values[i] - values[i - 2];
    } else if (i >= 1 && number >= values[i] - values[i - 1] && i % 2 == 1) {
      counters[i]++;
      counters[i - 1]++;
      number -= values[i] - values[i - 1];
    }
  }
}

int main() {
  ifstream fin("preface.in");
  int N;
  fin >> N;
  fin.close();
  int counters[NUMBER_OF_NUMERALS];
  for (int i = 0; i < NUMBER_OF_NUMERALS; i++) {
    counters[i] = 0;
  }
  char names[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
  int values[] = {1, 5, 10, 50, 100, 500, 1000};
  for (int n = 1; n <= N; n++) {
    calculate(n, counters, values);
  }
  ofstream fout("preface.out");
  for (int i = 0; i < NUMBER_OF_NUMERALS; i++) {
    if (counters[i] > 0) {
      fout << names[i] << ' ' << counters[i] << endl;
    }
  }
  fout.close();
  return 0;
}

/*
  ID: paulius10
  PROG: frac1
  LANG: C++
*/

#include <fstream>

using namespace std;

struct fraction {
  int numerator, denominator;
  fraction *previous;
  fraction *next;
};

int main() {
  ifstream fin("frac1.in");
  int N;
  fin >> N;
  fin.close();
  fraction start;
  start.numerator = 0;
  start.denominator = 1;
  fraction end;
  end.numerator = 1;
  end.denominator = 1;
  start.previous = NULL;
  start.next = &end;
  end.previous = &start;
  end.next = NULL;
  bool changesDone = true;
  while (changesDone) {
    changesDone = false;
    for (fraction *current = &start; current != &end; current = current->next)
      {
        int newDenominator = current->denominator + current->next->denominator;
        if (newDenominator <= N) {
          changesDone = true;
          fraction* newFraction = new fraction;
          newFraction->numerator = current->numerator + current->next->numerator;
          newFraction->denominator = newDenominator;
          newFraction->previous = current;
          newFraction->next = current->next;
          current->next->previous = newFraction;
          current->next = newFraction;
        }
      }
  }
  ofstream fout("frac1.out");
  for (fraction *f = &start; f != NULL; f = f->next) {
    fout << f->numerator << "/" << f->denominator << endl;
  }
  fout.close();
  return 0;
}

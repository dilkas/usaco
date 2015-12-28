/*
  ID: paulius10
  PROG: combo
  LANG: C++
*/

#include <fstream>
#include <set>
#include <math.h>

#define NUMBER_OF_DIALS 3
#define NUMBER_OF_COMBINATIONS 2
#define TOLERANCE 2

using namespace std;

struct combination {
  int a, b, c;
};

inline bool operator< (const combination& lhs, const combination& rhs) {
  if (lhs.a != rhs.a) return lhs.a < rhs.a;
  if (lhs.b != rhs.b) return lhs.b < rhs.b;
  return lhs.c < rhs.c;
}


int main() {
  ifstream fin("combo.in");
  int N;
  fin >> N;
  int combinations[NUMBER_OF_COMBINATIONS][NUMBER_OF_DIALS];
  for (int i = 0; i < NUMBER_OF_COMBINATIONS; i++) {
    for (int j = 0; j < NUMBER_OF_DIALS; j++) fin >> combinations[i][j];
  }
  fin.close();

  set<combination> s;
  int combo[NUMBER_OF_DIALS];
  for (int i = 0; i < NUMBER_OF_DIALS; i++)
    combo[i] = -TOLERANCE;
  combo[NUMBER_OF_DIALS - 1]--;
  for (int i = 0; i < pow((2 * TOLERANCE + 1), NUMBER_OF_DIALS); i++) {
    for (int j = NUMBER_OF_DIALS - 1; j >= 0; j--) {
      if (combo[j] < TOLERANCE) {
        combo[j]++;
        for (int k = NUMBER_OF_DIALS - 1; k > j; k--) combo[k] = -TOLERANCE;
        for (int k = 0; k < NUMBER_OF_COMBINATIONS; k++) {
          combination c;
          c.a = (combinations[k][0] + combo[0] + 2 * N) % N;
          c.b = (combinations[k][1] + combo[1] + 2 * N) % N;
          c.c = (combinations[k][2] + combo[2] + 2 * N) % N;
          s.insert(c);
        }
        break;
      }
    }
  }

  ofstream fout("combo.out");
  fout << s.size() << endl;
  fout.close();
  return 0;
}

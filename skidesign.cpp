/*
  ID: paulius10
  PROG: skidesign
  LANG: C++
*/

#include <fstream>
#include <math.h>

#define MAX_ELEVATION 100
#define MAX_DIFFERENCE 17

using namespace std;

int main() {
  ifstream fin("skidesign.in");
  int N;
  fin >> N;
  int hill[N];
  for (int i = 0; i < N; i++) fin >> hill[i];
  fin.close();
  int min_price = -1;
  for (int min = 0; min <= MAX_ELEVATION - MAX_DIFFERENCE; min++) {
    int max = min + MAX_DIFFERENCE;
    int price = 0;
    for (int i = 0; i < N; i++) {
      if (hill[i] < min) price += pow(min - hill[i], 2);
      else if (hill[i] > max) price += pow(hill[i] - max, 2);
    }
    if (price < min_price || min_price == -1) min_price = price;
  }
  ofstream fout("skidesign.out");
  fout << min_price << endl;
  fout.close();
  return 0;
}

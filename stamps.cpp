/*
  ID: paulius10
  LANG: C++
  PROG: stamps
*/

#include <algorithm>
#include <fstream>

using namespace std;

int main() {
  int K, N;
  ifstream fin("stamps.in");
  fin >> K >> N;
  int stamps[N];
  for (int i = 0; i < N; i++) fin >> stamps[i];
  fin.close();

  int maxValue = (*max_element(stamps, stamps + N)) * K;
  int stampsForValue[maxValue + 1];
  stampsForValue[0] = 0;
  int value;
  for (value = 1; value <= maxValue; value++) {
    int minStamps = -1;
    for (int i = 0; i < N; i++) {
      int previousValue = value - stamps[i];
      if (previousValue >= 0) {
	int stamps = stampsForValue[previousValue] + 1;
	if (stamps < minStamps || minStamps == -1) minStamps = stamps;
      }
    }
    if (minStamps == -1 || minStamps > K) break;
    stampsForValue[value] = minStamps;
  }
  ofstream fout("stamps.out");
  fout << value - 1 << endl;
  fout.close();
  return 0;
}

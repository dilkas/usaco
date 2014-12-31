/*
  ID: paulius10
  PROG: milk
  LANG: C++
 */

#include <fstream>
#include <algorithm>

using namespace std;

int minPrice(int P[], int A[], int M) {
  int min = -1;
  for (int i = 0; i < M; i++) {
    if (A[i] > 0 && (min == -1 || P[i] < P[min])) min = i;
  }
  return min;
}

int main() {
  ifstream fin("milk.in");
  ofstream fout("milk.out");
  int N, M;
  fin >> N >> M;
  int P[M];
  int A[M];
  for (int i = 0; i < M; i++) fin >> P[i] >> A[i];
  int price = 0;
  while (N > 0) {
    int i = minPrice(P, A, M);
    int q = min(N, A[i]);
    N -= q;
    A[i] -= q;
    price += q * P[i];
  }
  fout << price << endl;
  return 0;
}

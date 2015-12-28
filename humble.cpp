/*
  ID: paulius10
  PROG: humble
  LANG: C++
*/

#include <fstream>
#include <limits>

using namespace std;

/* For each prime number in S we store the index of the smallest number in
   numbers[] such that their product is greater than the largest number in
   numbers[].
   n - index of the last element in numbers[]
*/
void update_smallest(int smallest[], long long numbers[], long long S[], int K, int n) {
  for (int i = 0; i < K; i++) {
    int j;
    for (j = smallest[i]; ; j++) {
      long long product = S[i] * numbers[j];
      if (product > numbers[n]) break;
    }
    smallest[i] = j;
  }
}

int main() {
  ifstream fin("humble.in");
  int K, N;
  fin >> K >> N;
  long long S[K];
  for (int i = 0; i < N; i++) fin >> S[i];
  fin.close();
  long long numbers[N + 1];
  numbers[0] = 1;
  int smallest[K];
  for (int i = 0; i < K; i++) smallest[i] = 0;
  for (int i = 1; i <= N; i++) {
    long long min_number = numeric_limits<long long>::max();
    for (int k = 0; k < K; k++) {
      if (smallest[k] < 0) continue;
      long long new_number = numbers[smallest[k]] * S[k];
      if (new_number > numbers[i - 1] && new_number < min_number)
        min_number = new_number;
    }
    numbers[i] = min_number;
    update_smallest(smallest, numbers, S, K, i);
  }
  ofstream fout("humble.out");
  fout << numbers[N] << endl;
  fout.close();
  return 0;
}

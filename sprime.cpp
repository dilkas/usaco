/*
  ID: paulius10
  PROG: sprime
  LANG: C++
 */

#include <fstream>
#include <queue>
#include <math.h>

using namespace std;

bool isPrime(int n) {
  for (int d = 2; d * d <= n; d++) {
    if (n % d == 0) return false;
  }
  return true;
}

int main() {
  ifstream fin("sprime.in");
  int N;
  fin >> N;
  fin.close();
  int primeDigits[] = {2, 3, 5, 7};
  queue<int> primes;
  for (int i = 0; i < 4; i++) primes.push(primeDigits[i]);
  ofstream fout("sprime.out");
  while (!primes.empty()) {
    int prime = primes.front();
    primes.pop();
    int digitsCount = (int) log10((double) prime) + 1;
    if (digitsCount > N) break;
    if (digitsCount == N) {
      fout << prime << endl;
    } else {
      for (int digit = 0; digit <= 9; digit++) {
        int newPrime = prime * 10 + digit;
        if (isPrime(newPrime)) primes.push(newPrime);
      }
    }
  }
  fout.close();
  return 0;
}

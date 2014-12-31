/*
  ID: paulius10
  PROG: pprime
  LANG: C++
*/

#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

bool nextPalindrome(vector<int> & palindrome) {
  int size = palindrome.size();
  for (int i = size / 2; i < size; i++) {
    if (palindrome[i] != 9) {
      palindrome[i]++;
      int j = size - i - 1;
      if (i != j) palindrome[j]++;
      for (int k = j + 1; k < i; k++) palindrome[k] = 0;
      return true;
    }
  }
  return false;
}

int vector2int(vector<int> v) {
  int sum = 0;
  int multiplier = 1;
  for (int i = v.size() - 1; i >= 0; i--) {
    sum += v[i] * multiplier;
    multiplier *= 10;
  }
  return sum;
}

bool isPrime(int n) {
  if (n == 1) return false;
  for (int d = 2; d <= sqrt(n); d++) {
    if (n % d == 0) return false;
  }
  return true;
}

int countDigits(int n) {
  return (int) log10((double) n) + 1;
}

vector<int> createPalindrome(int numberOfDigits) {
  vector<int> palindrome;
    palindrome.push_back(1);
  if (numberOfDigits == 1) return palindrome;
  for (int i = 0; i < numberOfDigits - 2; i++) palindrome.push_back(0);
  palindrome.push_back(1);
  return palindrome;
}

int main() {
  ifstream fin("pprime.in");
  int a, b;
  fin >> a >> b;
  fin.close();
  ofstream fout("pprime.out");
  for (int numberOfDigits = countDigits(a); numberOfDigits <= countDigits(b);
       numberOfDigits++) {
    vector<int> v = createPalindrome(numberOfDigits);
    do {
    int number = vector2int(v);
    if (number >= a && number <= b && isPrime(number)) fout << number << endl;
    } while(nextPalindrome(v));
  }
  fout.close();
  return 0;
}

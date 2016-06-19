/*
  ID: paulius10
  PROG: vans
  LANG: C++
*/

#include <fstream>
#include <list>

using namespace std;

// based on a generating function from some paper
const short COEFFICIENTS[] = {2, 2, -2, 1};
const short NUM_COEFFICIENTS = 4;

// unsigned long long is too small
struct Number {
  bool negative;
  list<short> digits;
};

/* Works for 1-digit multipliers. */
Number multiply(short multiplier, Number multiplicand) {
  Number product;
  product.negative = ((multiplier < 0) != multiplicand.negative);
  if (multiplier < 0)
    multiplier = -multiplier;
  short memory = 0;
  for (list<short>::reverse_iterator digit = multiplicand.digits.rbegin();
       digit != multiplicand.digits.rend(); ++digit) {
    short t = multiplier * *digit + memory;
    product.digits.push_front(t % 10);
    memory = t / 10;
  }
  if (memory)
    product.digits.push_front(memory);
  return product;
}

Number add(Number s1, Number s2) {
  // make sure |s1| >= |s2|
  if (s1.digits.size() < s2.digits.size() ||
      (s1.digits.size() == s2.digits.size() &&
       *(s1.digits.begin()) < *(s2.digits.begin())))
    return add(s2, s1);

  Number sum;
  sum.negative = s1.negative;
  short memory = 0;
  list<short>::reverse_iterator digit1 = s1.digits.rbegin(),
    digit2 = s2.digits.rbegin();
  for (; digit2 != s2.digits.rend(); ++digit1, ++digit2) {
    short t = (s1.negative == s2.negative) ? *digit1 + *digit2 + memory :
      *digit1 - *digit2 + memory;
    memory = 0;
    if (t < 0) {
      t += 10;
      --memory;
    }
    sum.digits.push_front(t % 10);
    memory += t / 10;
  }
  for (; digit1 != s1.digits.rend(); ++digit1) {
    short t = *digit1 + memory;
    sum.digits.push_front(t % 10);
    memory = t / 10;
  }
  if (memory)
    sum.digits.push_front(memory);
  return sum;
}

int main() {
  int N;
  ifstream fin("vans.in");
  fin >> N;
  fin.close();
  ofstream fout("vans.out");

  // a case not handled by the main part
  if (N == 1) {
    fout << 0 << endl;
    fout.close();
    return 0;
  }

  Number values[N - 1];
  values[0].negative = false;
  values[0].digits.push_back(1);
  for (int i = 1; i < N - 1; ++i) {
    values[i].negative = false;
    values[i].digits.push_back(0);
    for (int j = 1; j <= NUM_COEFFICIENTS && i - j >= 0; ++j)
      values[i] = add(multiply(COEFFICIENTS[j - 1], values[i - j]), values[i]);
  }

  Number answer = multiply(2, values[N - 2]);
  for (list<short>::iterator digit = answer.digits.begin();
       digit != answer.digits.end(); ++digit)
    fout << *digit;
  fout << endl;
  fout.close();
}

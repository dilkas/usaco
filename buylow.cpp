/*
  ID: paulius10
  PROG: buylow
  LANG: C++
*/

#include <fstream>
#include <map>
#include <vector>

using namespace std;
const int BASE = 10;
struct args {
  int length, index_limit, price_limit;
};

bool operator<(const args& x, const args& y) {
  if (x.length != y.length) return x.length < y.length;
  if (x.index_limit != y.index_limit) return x.index_limit < y.index_limit;
  return x.price_limit < y.price_limit;
}

int get(vector<int> v, int i) {
  return (i < v.size()) ? v[i] : 0;
}

void insert(vector<int> &v, int i, int e) {
  if (i < v.size()) v[i] = e;
  else v.push_back(e);
}

void add(vector<int> &A, vector<int> B) {
  int carry = 0;
  for (int pos = 0; pos < max(A.size(), B.size()); pos++) {
    insert(A, pos, get(A, pos) + get(B, pos) + carry);
    carry = A[pos] / BASE;
    A[pos] %= BASE;
  }
  if (carry != 0) A.push_back(carry);
}

map<args, vector<int> > memo;
vector<int> count(args argv, int lengths[], int prices[]) {
  if (memo.find(argv) != memo.end()) return memo[argv];
  if (argv.length <= 0) {
    vector<int> one(1, 1);
    memo[argv] = one;
    return one;
  }
  map<int, int> price_to_index;
  for (int i = 0; i < argv.index_limit; i++) {
    if (lengths[i] == argv.length && prices[i] > argv.price_limit)
      price_to_index[prices[i]] = i;
  }
  vector<int> sum (1, 0);
  for (map<int, int>::iterator it = price_to_index.begin();
       it != price_to_index.end(); it++) {
    args new_argv;
    new_argv.length = argv.length - 1;
    new_argv.index_limit = it->second;
    new_argv.price_limit = it->first;
    add(sum, count(new_argv, lengths, prices));
  }
  memo[argv] = sum;
  return sum;
}

int main() {
  ifstream fin("buylow.in");
  int N;
  fin >> N;
  int prices[N];
  for (int i = 0; i < N; i++) fin >> prices[i];
  fin.close();
  int lengths[N];
  lengths[0] = 1;
  for (int i = 1; i < N; i++) {
    int m = 0;
    for (int j = 1; j < i; j++) {
      if (prices[i] < prices[j] && lengths[j] > m) m = lengths[j];
    }
    lengths[i] = m + 1;
  }
  int max_length = 0;
  for (int i = 0; i < N; i++) {
    if (lengths[i] > max_length) max_length = lengths[i];
  }
  args initial_argv;
  initial_argv.length = max_length;
  initial_argv.index_limit = N;
  initial_argv.price_limit = 0;
  vector<int> c = count(initial_argv, lengths, prices);
  ofstream fout("buylow.out");
  fout << max_length << " ";
  for (int i = c.size() - 1; i >= 0; i--) fout << c[i];
  fout << endl;
  fout.close();
  return 0;
}

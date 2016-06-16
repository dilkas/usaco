/*
  ID: paulius10
  PROG: twofive
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;
const int EDGE = 5;
const int SIZE = EDGE * EDGE;
const char EMPTY = '_';
const char FIRST_LETTER = 'A';
const char LAST_LETTER = FIRST_LETTER + SIZE - 1;

// the number of ways to complete a partially filled grid with this signature
map<vector<int>, int> completions;

/* Checks if grid[index] is a legal assignment. */
bool possible(int index, vector<char> &grid) {
  // all cells to the left must be less than grid[index]
  for (int i = index - index % EDGE; i < index; ++i)
    if (grid[i] >= grid[index])
      return false;

  // same for cells above
  for (int i = index - EDGE; i >= 0; i -= EDGE)
    if (grid[i] >= grid[index])
      return false;

  // ensure uniqueness
  for (int i = 0; i < index; i++)
    if (grid[i] == grid[index])
      return false;

  return true;
}

/* A partially filled grid which doesn't skip any letters can be represented by
   a vector of EDGE numbers in [0, EDGE] based on the number of characters in
   each row. Permutations don't matter (as long as they are legal), each row is
   filled from left to right, and each row has at most as many letters as the
   row above. */
vector<int> signature(vector<char> &grid) {
  vector<int> t(EDGE, 0);
  for (int i = 0; i < SIZE; ++i)
    if (grid[i] != EMPTY)
      ++t[i / 5];
  return t;
}

/* Recursively generates a vector of all possible signatures. */
void generate_signatures(vector<int> signature,
                         vector<vector<int> > &all_signatures) {
  int size = signature.size();
  if (size == EDGE) {
    all_signatures.push_back(signature);
    return;
  }
  for (int i = 0; i <= signature[size - 1]; ++i) {
    vector<int> next_signature = signature;
    next_signature.push_back(i);
    generate_signatures(next_signature, all_signatures);
  }
}

/* A comparator for signature vectors based on their sums. */
int compare_sums(vector<int> a, vector<int> b) {
  int s1 = 0, s2 = 0;
  for (int i = 0; i < EDGE; i++) {
    s1 += a[i];
    s2 += b[i];
  }
  return s1 > s2;
}

/* Counts the number ways to complete a partially filled grid using memoized
   recursion and the completions map. */
map<vector<char>, int> memo;
int count_completions(vector<char> grid) {
  // memoization
  map<vector<char>, int>::iterator it = memo.find(grid);
  if (it != memo.end())
    return it->second;

  // find the smallest letter that's not in the grid
  set<char> letters;
  for (int i = 0; i < SIZE; ++i)
    if (grid[i] != EMPTY)
      letters.insert(grid[i]);
  char letter = FIRST_LETTER;
  for (; letters.find(letter) != letters.end() && letter <= LAST_LETTER;
       ++letter);

  // if we didn't skip any letters, we can use completions[]
  if (letter >= *(letters.rbegin())) {
    memo[grid] = completions[signature(grid)];
    return memo[grid];
  }

  // recurse on all possible spots to place this letter
  int sum = 0;
  for (int i = 0; i < SIZE; ++i) {
    if (grid[i] == EMPTY) {
      grid[i] = letter;
      if (possible(i, grid))
        sum += count_completions(grid);
      grid[i] = EMPTY;
    }
  }
  return memo[grid] = sum;
}

int main() {
  // generate all possible signatures and sort them (necessary for DP)
  vector<vector<int> > signatures;
  for (int i = 0; i <= EDGE; ++i)
    generate_signatures(vector<int>(1, i), signatures);
  sort(signatures.begin(), signatures.end(), compare_sums);

  // generate the completions map
  completions[signatures[0]] = 1;
  for (int i = 1; i < signatures.size(); ++i) {
    completions[signatures[i]] = 0;
    for (int j = 0; j < EDGE; ++j) {
      if (signatures[i][j] < EDGE && (j == 0 || signatures[i][j] <
                                      signatures[i][j - 1])) {
        // since each successor has a bigger sum, its value is already computed
        vector<int> successor = signatures[i];
        ++successor[j];
        completions[signatures[i]] += completions[successor];
      }
    }
  }

  int skipped = 0; // the number of possible grids that we're skipping
  vector<char> grid(SIZE, EMPTY);
  char mode;
  ifstream fin("twofive.in");
  fin >> mode;
  ofstream fout("twofive.out");
  if (mode == 'N') {
    int M;
    fin >> M;
    for (int i = 0; i < SIZE; ++i) {
      for (grid[i] = FIRST_LETTER; grid[i] <= LAST_LETTER; ++grid[i]) {
        if (possible(i, grid)) {
          int num_ways = count_completions(grid);
          if (skipped + num_ways >= M)
            break;
          skipped += num_ways;
        }
      }
    }
    for (int i = 0; i < 25; ++i)
      fout << grid[i];
  } else {
    string target;
    fin >> target;
    for (int i = 0; i < SIZE; ++i)
      for (grid[i] = 'A'; grid[i] < target[i]; ++grid[i])
        if (possible(i, grid))
          skipped += count_completions(grid);
    fout << skipped + 1;
  }
  fin.close();
  fout << endl;
  fout.close();
}

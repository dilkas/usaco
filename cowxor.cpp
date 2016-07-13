/*
  ID: paulius10
  PROG: cowxor
  LANG: C++
*/

#include <bitset>
#include <fstream>
#include <limits>

using namespace std;
const int NUM_BITS = 21;
int *xor_values; // xor_values[i] is the xor of the first i + 1 numbers


class Trie {
  struct Node {
    Node *zero, *one;
    int lowest_index;

    Node() {
      zero = one = NULL;
      lowest_index = numeric_limits<int>::max();
    }

    void update_index(int index) {
      if (index < lowest_index)
        lowest_index = index;
    }
  } *root;
public:
  Trie() {
    root = new Node();
  }

  void insert(int index) {
    bitset<NUM_BITS> bits(xor_values[index]);
    Node *node = root;
    node->update_index(index);
    for (int i = NUM_BITS - 1; i >= 0; --i) {
      Node *next_node = node->zero, **parent = &node->zero;
      if (bits.test(i)) {
        next_node = node->one;
        parent = &node->one;
      }
      if (next_node == NULL) {
        next_node = new Node();
        *parent = next_node;
      }
      node = next_node;
      node->update_index(index);
    }
  }

  /*
    Finds a number in the trie such that its xor with the given number is
    maximised. It also has to have an index less than or equal to the given
    index.
  */
  int max_xor(int index) {
    bitset<NUM_BITS> bits(xor_values[index]);
    bitset<NUM_BITS> answer;
    Node *node = root;
    for (int i = NUM_BITS - 1; i >= 0; --i) {
      Node *next_node = (bits.test(i)) ? node->zero : node->one;
      // we're trying to choose the opposite bit, but sometimes that's
      // impossible
      if (next_node == NULL || next_node->lowest_index > index)
        next_node = (bits.test(i)) ? node->one : node->zero;
      if (next_node == node->one)
        answer.set(i);
      node = next_node;
    }
    return answer.to_ulong();
  }
};


int main() {
  int N;
  ifstream fin("cowxor.in");
  fin >> N;
  xor_values = new int[N];
  Trie *trie = new Trie();
  fin >> xor_values[0];
  trie->insert(0);
  for (int i = 1; i < N; ++i) {
    fin >> xor_values[i];
    xor_values[i] ^= xor_values[i - 1];
    trie->insert(i);
  }
  fin.close();

  int max_xor = xor_values[0];
  int first_index = 0, last_index = 0;
  for (int i = 0; i < N; ++i) {
    int number = trie->max_xor(i);
    int xor_value = xor_values[i] ^ number;
    if (xor_value > max_xor) {
      max_xor = xor_value;
      last_index = i;
      first_index = i;
      for (; xor_values[first_index] != number; --first_index) {}
    }
  }
  
  ofstream fout("cowxor.out");
  fout << max_xor << " "
       << first_index + ((first_index == last_index) ? 1 : 2) << " "
       << last_index + 1 << endl;
  fout.close();
}

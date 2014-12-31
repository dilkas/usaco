/*
  ID: paulius10
  PROG: wormhole
  LANG: C++
*/

#include <fstream>

using namespace std;

int move(int wanderings[], int pairings[], int position, bool wander,
         int steps) {
  if (steps == 0) return position;
  if (position == -1) return -1;
  if (wander)
    return move(wanderings, pairings, wanderings[position], false, steps - 1);
  else
    return move(wanderings, pairings, pairings[position], true, steps - 1);
}

// http://en.wikipedia.org/wiki/Cycle_detection
bool cycle(int wanderings[], int pairings[], int tortoise) {
  int hare = move(wanderings, pairings, tortoise, true, 2);
  for (int i = 0; tortoise != hare && tortoise != -1 && hare != -1; i++) {
    tortoise = move(wanderings, pairings, tortoise, true, 2);
    hare = move(wanderings, pairings, hare, true, 4);
  }
  return hare == tortoise;
}

int recurse(int wanderings[], int pairings[], int N, int start, int count,
            int cycles) {
  if (count == N / 2) {
    for (int i = 0; i < N; i++) {
      if (cycle(wanderings, pairings, i)) return 1;
    }
    return 0;
  }
  int counter = 0;
  for (int i = start; i < N; i++) {
    if (pairings[i] != -1) continue;
    for (int j = 0; j < i; j++) {
      if (pairings[j] == -1 && i != j) {
        pairings[i] = j;
        pairings[j] = i;
        counter += recurse(wanderings, pairings, N, i + 1, count + 1, cycles);
        pairings[i] = -1;
        pairings[j] = -1;
      }
    }
  }
  return counter;
}

int main() {
  ifstream fin("wormhole.in");
  int N;
  fin >> N;
  int wormholes[N][2];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 2; j++) fin >> wormholes[i][j];
  }
  fin.close();

  int pairings[N], wanderings[N];
  for (int i = 0; i < N; i++) {
    pairings[i] = -1;
    wanderings[i] = -1;
  }
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (wormholes[i][1] == wormholes[j][1]) {
        if (wormholes[i][0] < wormholes[j][0]) {
          if (wanderings[i] == -1 ||
              wormholes[j][0] < wormholes[wanderings[i]][0])
            wanderings[i] = j;
        }
        else if (wanderings[j] == -1 ||
                 wormholes[i][0] < wormholes[wanderings[j]][0])
          wanderings[j] = i;
      }
    }
  }

  ofstream fout("wormhole.out");
  fout << recurse(wanderings, pairings, N, 0, 0, 0) << endl;
  fout.close();
  return 0;
}

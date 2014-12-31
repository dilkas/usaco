/*
  ID: paulius10
  PROG: castle
  LANG: C++
*/

#include <fstream>
#include <vector>
#include <iostream>

#define SIZE 50
#define WEST 1
#define NORTH 2
#define EAST 4
#define SOUTH 8

using namespace std;

void dfs(int i, int j, int castle[][SIZE], int roomNumber[][SIZE],
         vector<int> &rooms) {
  int roomIndex = rooms.size() - 1;
  roomNumber[i][j] = roomIndex;
  rooms[roomIndex]++;
  if (!(castle[i][j] & WEST) && roomNumber[i][j - 1] == -1)
    dfs(i, j - 1, castle, roomNumber, rooms);
  if (!(castle[i][j] & NORTH) && roomNumber[i - 1][j] == -1)
    dfs(i - 1, j, castle, roomNumber, rooms);
  if (!(castle[i][j] & EAST) && roomNumber[i][j + 1] == -1)
    dfs(i, j + 1, castle, roomNumber, rooms);
  if (!(castle[i][j] & SOUTH) && roomNumber[i + 1][j] == -1)
    dfs(i + 1, j, castle, roomNumber, rooms);
}

int main() {
  ifstream fin("castle.in");
  int M, N;
  fin >> M >> N;
  int castle[N][SIZE];
  int roomNumber[N][SIZE];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      fin >> castle[i][j];
      roomNumber[i][j] = -1;
    }
  }
  fin.close();
  vector<int> rooms;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (roomNumber[i][j] == -1) {
        rooms.push_back(0);
        dfs(i, j, castle, roomNumber, rooms);
      }
    }
  }
  ofstream fout("castle.out");
  fout << rooms.size() << endl;
  int max = rooms[0];
  for (int i = 1; i < rooms.size(); i++) {
    if (rooms[i] > max) max = rooms[i];
  }
  fout << max << endl;
  int removalSize = 0;
  int x, y;
  char direction;
  for (int j = 0; j < M; j++) {
    for (int i = N - 1; i >= 0; i--) {
      if (i > 0) {
        int room1 = roomNumber[i][j];
        int room2 = roomNumber[i - 1][j];
        if (room1 != room2) {
          int size = rooms[room1] + rooms[room2];
          if (size > removalSize) {
            removalSize = size;
            x = i;
            y = j;
            direction = 'N';
          }
        }
      }
      if (j < M - 1) {
        int room1 = roomNumber[i][j];
        int room2 = roomNumber[i][j + 1];
        if (room1 != room2) {
          int size = rooms[room1] + rooms[room2];
          if (size > removalSize) {
            removalSize = size;
            x = i;
            y = j;
            direction = 'E';
          }
        }
      }
    }
  }
  fout << removalSize << endl << x + 1 << ' ' << y + 1 << ' ' << direction << endl;
  fout.close();
  return 0;
}

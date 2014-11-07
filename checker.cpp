/*
  ID: paulius10
  PROG: checker
  LANG: C++
*/

#include <fstream>
#include <iostream>

using namespace std;

void placeChecker(int row, int N, int state[], int binary[], int &count,
                  int &columnOK, int &diagonalDownOK, int &diagonalUpOK,
                  ofstream &fout) {
	if (row == N && count++ < 3) {
    fout << state[0];
    for (int i = 1; i < N; i++) {
      fout << " " << state[i];
    }
    fout << endl;
    return;
  }
  int diagonalDownIndex = row + N - 1;
  int diagonalUpIndex = row;
  for (int column = 0; column < N; column++)  {
    if (columnOK & binary[column] &&
        diagonalDownOK & binary[diagonalDownIndex] &&
        diagonalUpOK & binary[diagonalUpIndex]) {
      state[row] = column + 1;
      columnOK &= ~binary[column];
      diagonalDownOK &= ~binary[diagonalDownIndex];
      diagonalUpOK &= ~binary[diagonalUpIndex];
      placeChecker(row + 1, N, state, binary, count, columnOK, diagonalDownOK,
                   diagonalUpOK, fout);
      columnOK |= binary[column];
      diagonalDownOK |= binary[diagonalDownIndex];
      diagonalUpOK |= binary[diagonalUpIndex];
    }
    diagonalDownIndex--;
    diagonalUpIndex++;
  }
}

int main() {
  ifstream fin("checker.in");
  int N;
  fin >> N;
  fin.close();
  int state[N];
  int count = 0;
  int columnOK = -1;
  int diagonalDownOK = -1;
  int diagonalUpOK = -1;
  int binary[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
                  4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
                  1048576, 2097152, 4194304, 8388608, 16777216};
  ofstream fout("checker.out");
  placeChecker(0, N, state, binary, count, columnOK, diagonalDownOK,
               diagonalUpOK, fout);
  fout << count << endl;
  fout.close();
  return 0;
}

/*
  ID: paulius10
  PROG: fc
  LANG: C++
*/

#include <cmath>
#include <fstream>

using namespace std;

struct Vector {
  double x, y;
  Vector operator-(const Vector &a) const {
    Vector difference;
    difference.x = x - a.x;
    difference.y = y - a.y;
    return difference;
  }
};

double zcrossprod(Vector v1, Vector v2) {
  return v1.x * v2.y - v1.y * v2.x;
}

void swap(int i, int j, Vector A[], double angle[]) {
  Vector t = A[i];
  A[i] = A[j];
  A[j] = t;
  double s = angle[i];
  angle[i] = angle[j];
  angle[j] = s;
}

int partition(int lo, int hi, Vector A[], double angle[]) {
  double pivot = angle[hi];
  int i = lo; // place for swapping
  for (int j = lo; j < hi; j++) if (angle[j] <= pivot) swap(i++, j, A, angle);
  swap(i, hi, A, angle);
  return i;
}

void quicksort(int lo, int hi, Vector A[], double angle[]) {
  if (lo < hi) {
    int p = partition(lo, hi, A, angle);
    quicksort(lo, p - 1, A, angle);
    quicksort(p + 1, hi, A, angle);
  }
}

double length(Vector a, Vector b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
  int npoints;
  ifstream fin("fc.in");
  fin >> npoints;
  double x[npoints], y[npoints];
  for (int i = 0; i < npoints; i++) fin >> x[i] >> y[i];
  fin.close();
  double midx = 0, midy = 0;
  for (int i = 0; i < npoints; i++) {
    midx += x[i] / npoints;
    midy += y[i] / npoints;
  }
  double angle[npoints];
  Vector perm[npoints];
  for (int i = 0; i < npoints; i++) {
    angle[i] = atan2(y[i] - midy, x[i] - midx);
    perm[i].x = x[i];
    perm[i].y = y[i];
  }
  quicksort(0, npoints - 1, perm, angle);
  // start making hull
  Vector hull[npoints] = {perm[0], perm[1]};
  int hullpos = 2;
  for (int i = 2; i < npoints - 1; i++) {
    Vector p = perm[i];
    while (hullpos > 1 && zcrossprod(hull[hullpos - 2] - hull[hullpos - 1],
                                     hull[hullpos - 1] - p) < 0)
      hullpos--;
    hull[hullpos++] = p;
  }
  // add last point
  Vector p = perm[npoints - 1];
  while (hullpos > 1 && zcrossprod(hull[hullpos - 2] - hull[hullpos - 1],
                                   hull[hullpos - 1] - p) < 0)
    hullpos--;
  int hullstart = 0;
  bool flag;
  do {
    flag = false;
    if (hullpos - hullstart >= 2 && zcrossprod(p - hull[hullpos - 1],
                                               hull[hullstart] - p) < 0) {
      p = hull[hullpos-- - 1];
      flag = true;
    }
    if (hullpos - hullstart >= 2 && zcrossprod(hull[hullstart] - p,
                                               hull[hullstart + 1] -
                                               hull[hullstart]) < 0) {
      hullstart++;
      flag = true;
    }
  } while (flag);
  hull[hullpos++] = p;
  double sum = length(hull[hullstart], hull[hullpos - 1]);
  for (int i = hullstart + 1; i < hullpos; i++) sum += length(hull[i - 1], hull[i]);
  ofstream fout("fc.out");
  fout.setf(ios::fixed);
  fout.precision(2);
  fout << sum << endl;
  fout.close();
  return 0;
}

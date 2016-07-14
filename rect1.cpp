/*
  ID: paulius10
  PROG: rect1
  LANG: C++
*/

#include <fstream>
#include <list>
#include <map>

using namespace std;
map<int, int> areas;


struct Rectangle {
  int llx, lly, urx, ury, color;
};


void add(int color, int area) {
  map<int, int>::iterator it = areas.find(color);
  if (it == areas.end())
    areas[color] = area;
  else
    it->second += area;
}

int main() {
  int A, B, N;
  ifstream fin("rect1.in");
  fin >> A >> B >> N;
  list<Rectangle> rectangles;
  for (int i = 0; i < N; ++i) {
    Rectangle rectangle;
    fin >> rectangle.llx >> rectangle.lly >> rectangle.urx >> rectangle.ury
        >> rectangle.color;
    for (list<Rectangle>::iterator it = rectangles.begin();
         it != rectangles.end();) {
      // if the rectangles overlap
      if (rectangle.llx < it->urx && rectangle.urx > it->llx &&
          rectangle.lly < it->ury && rectangle.ury > it->lly) {
        // top
        if (it->ury > rectangle.ury)
          rectangles.push_back({max(it->llx, rectangle.llx), rectangle.ury,
                min(it->urx, rectangle.urx), it->ury, it->color});
        
        // left
        if (it->llx < rectangle.llx) {
          Rectangle left = *it;
          left.urx = rectangle.llx;
          rectangles.push_back(left);
        }

        // right
        if (it->urx > rectangle.urx) {
          Rectangle right = *it;
          right.llx = rectangle.urx;
          rectangles.push_back(right);
        }

        // bottom
        if (it->lly < rectangle.lly)
          rectangles.push_back({max(it->llx, rectangle.llx), it->lly,
                min(it->urx, rectangle.urx), rectangle.lly, it->color});
        
        rectangles.erase(it++);
      } else
        ++it;
    }
    rectangles.push_back(rectangle);
  }
  fin.close();

  // sum up the areas
  int sum = 0;
  for (list<Rectangle>::iterator rectangle = rectangles.begin();
       rectangle != rectangles.end(); ++rectangle) {
    int area = (rectangle->urx - rectangle->llx) * (rectangle->ury - rectangle->lly);
    sum += area;
    add(rectangle->color, area);
  }
  add(1, A * B - sum);

  ofstream fout("rect1.out");
  for (map<int, int>::iterator it = areas.begin(); it != areas.end(); ++it)
    fout << it->first << " " << it->second << endl;
  fout.close();
}

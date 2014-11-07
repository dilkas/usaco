/*
  ID: paulius10
  PROG: friday
  LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum Month { JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };
enum Day { SATURDAY, SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY };

int leap(int year) {
  if (year % 100 == 0) {
    return year % 400 == 0;
  }
  return year % 4 == 0;
}

int days(int year, int month) {
  if (month == FEBRUARY) {
    if (leap(year)) return 29;
    else return 28;
  }
  if (month == SEPTEMBER || month == APRIL || month == JUNE || month == NOVEMBER) return 30;
  return 31;
}

int main() {
  ofstream fout ("friday.out");
  ifstream fin ("friday.in");
  int N;
  fin >> N;
  int weekdays[7];
  for (int i = 0; i < 7; i++) weekdays[i] = 0;
  int day = SATURDAY;
  for (int year = 1900; year < 1900 + N; year++) {
    for (int month = JANUARY; month <= DECEMBER; month++) {
      weekdays[day] += 1;
      day = (day + days(year, month)) % 7;
    }
  }
  fout << weekdays[0];
  for (int i = 1; i < 7; i++) fout << " " << weekdays[i];
  fout << endl;
  return 0;
}

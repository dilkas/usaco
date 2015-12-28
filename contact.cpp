/*
  ID: paulius10
  PROG: contact
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

#define PATTERNS_PER_LINE 6

using namespace std;

struct pattern {
  int frequency;
  string pattern;
};

bool comparePatterns(const pattern& lhs, const pattern& rhs) {
  if (lhs.frequency != rhs.frequency) return lhs.frequency > rhs.frequency;
  int l1 = lhs.pattern.length();
  int l2 = rhs.pattern.length();
  if (l1 != l2) return l1 < l2;
  return lhs.pattern < rhs.pattern;
}

int main() {
  int A, B, N;
  ifstream fin("contact.in");
  fin >> A >> B >> N;
  string seq = "";
  while (!fin.eof()) {
    string line;
    fin >> line;
    seq += line;
  }
  fin.close();

  // counting
  map<string, int> observations;
  // for each starting index position
  for (int i = 0; i <= seq.length() - A; i++) {
    // for each valid pattern starting with that index
    for (int len = A; len <= B && i + len <= seq.length(); len++) {
      // mark that pattern as observed
      string pattern = seq.substr(i, len);
      map<string, int>::iterator it = observations.find(pattern);
      if (it != observations.end()) it->second = it->second + 1;
      else observations[pattern] = 1;
    }
  }

  // sorting
  vector<pattern> patterns;
  for (map<string, int>::iterator it = observations.begin();
       it != observations.end(); it++) {
    pattern p;
    p.frequency = it->second;
    p.pattern = it->first;
    patterns.push_back(p);
  }
  sort(patterns.begin(), patterns.end(), &comparePatterns);

  ofstream fout("contact.out");
  int previousFrequency = 0;
  int frequencyCounter = 0;
  int patternCounter = 0;
  for (int i = 0; i < patterns.size(); i++) {
    bool newLine = false;
    if (patterns[i].frequency < previousFrequency || previousFrequency == 0) {
      frequencyCounter++;
      if (frequencyCounter > N) break;
      if (i != 0) fout << endl;
      fout << patterns[i].frequency;
      previousFrequency = patterns[i].frequency;
      newLine = true;
      patternCounter = 0;
    }
    if (patternCounter % PATTERNS_PER_LINE == 0) newLine = true;
    if (newLine) fout << endl << patterns[i].pattern;
    else fout << ' ' << patterns[i].pattern;
    patternCounter++;
  }
  fout << endl;
  fout.close();
  return 0;
}

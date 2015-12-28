/*
  ID: paulius10
  PROG: butter
  LANG: C++
 */

#include <fstream>
#include <queue>

using namespace std;
const int INF = 2000000000;
typedef pair<int, int> PII;

int main() {
  ifstream fin("butter.in");
  int N, P, C;
  fin >> N >> P >> C;
  int cow_to_pasture[N];
  for (int i = 0; i < N; i++) {
    fin >> cow_to_pasture[i];
    cow_to_pasture[i]--;
  }
  vector<vector<PII> > edges(P);
  for (int i = 0; i < C; i++) {
    int pasture1, pasture2, length;
    fin >> pasture1 >> pasture2 >> length;
    pasture1--;
    pasture2--;
    edges[pasture1].push_back(make_pair(length, pasture2));
    edges[pasture2].push_back(make_pair(length, pasture1));
  }
  int min_sum = INF;
  for (int s = 0; s < P; s++) {
    priority_queue<PII, vector<PII>, greater<PII> > Q;
    vector<int> dist(P, INF);
    Q.push(make_pair(0, s));
    dist[s] = 0;
    while (!Q.empty()){
      PII p = Q.top();
      Q.pop();
      int here = p.second;
      for (vector<PII>::iterator it = edges[here].begin();
           it != edges[here].end(); it++) {
        if (dist[here] + it->first < dist[it->second]) {
          dist[it->second] = dist[here] + it->first;
          Q.push(make_pair(dist[it->second], it->second));
        }
      }
    }
    int sum = 0;
    for (int cow = 0; cow < N; cow++) sum += dist[cow_to_pasture[cow]];
    if (sum < min_sum) min_sum = sum;
  }
  ofstream fout("butter.out");
  fout << min_sum << endl;
  fout.close();
  return 0;
}

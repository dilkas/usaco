/*
  ID: paulius10
  PROG: schlnet
  LANG: C++
*/

#include <algorithm>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

void strongconnect(int v, int N, int &index, int &n, int indices[],
                   int lowlink[], bool on_stack[], stack<int> &S,
                   vector<bool> edge[], int scc[]) {
  // set the depth index of v to the smallest unused index
  indices[v] = index;
  lowlink[v] = index++;
  S.push(v);
  on_stack[v] = true;

  // consider successors of v
  for (int w = 0; w < N; w++) {
    if (!edge[v][w]) continue;
    if (indices[w] == -1) {
      // successor w has not yet been visited; recurse on it
      strongconnect(w, N, index, num_sccs, indices, lowlink, on_stack, S,
                    edge, scc);
      if (lowlink[w] < lowlink[v]) lowlink[v] = lowlink[w];
    } else if (on_stack[w] && indices[w] < lowlink[v]) {
      // successor w is in stack S and hence in the current SCC
      lowlink[v] = indices[w];
    }
  }

  // if v is a root node, pop the stack and generate an SCC
  if (lowlink[v] == indices[v]) {
    int w;
    do {
      w = S.top();
      S.pop();
      on_stack[w] = false;
      scc[w] = n;
    } while (w != v);
    n++;
  }
}

/*
  Groups all vertices into strongly connected components (by modifying scc[])
  and returns the total number of SCC's.
*/
int tarjan(int N, vector<bool> edge[], int scc[]) {
  int index = 0, n = 0, indices[N], lowlink[N];
  bool on_stack[N];
  for (int i = 0; i < N; i++) {
    indices[i] = lowlink[i] = -1;
    on_stack[i] = false;
  }
  stack<int> S;
  for (int v = 0; v < N; v++) {
    if (indices[v] == -1)
      strongconnect(v, N, index, n, indices, lowlink, on_stack, S, edge, scc);
  }
  return n;
}

/*
  Returns an uncovered vertex with the smallest in-degree.
*/
int argmin(int in[], bool covered[], int n) {
  int m = -1;
  for (int i = 0; i < n; i++)
    if (!covered[i] && (m == -1 || in[i] < in[m])) m = i;
  return m;
}

/*
  Marks all vertices reachable from i as covered.
*/
void dfs(int i, int n, vector<bool> adjacent[], bool covered[]) {
  covered[i] = true;
  for (int j = 0; j < n; j++) {
    if (adjacent[i][j] && !covered[j]) dfs(j, n, adjacent, covered);
  }
}

int main() {
  int N;
  ifstream fin("schlnet.in");
  fin >> N;
  vector<bool> edge[N];
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) edge[i].push_back(false);
  for (int i = 0; i < N; i++) {
    while (true) {
      int j;
      fin >> j;
      if (j == 0) break;
      edge[i][j - 1] = true;
    }
  }
  fin.close();

  int scc[N], n = tarjan(N, edge, scc);
  ofstream fout("schlnet.out");
  if (n == 1) {
    fout << 1 << endl << 0 << endl;
  } else {
    // construct a new graph with SCC's instead of vertices
    vector<bool> adjacent[n];
    bool covered[n];
    // keep track of in- and out-degrees
    int in[n], out[n];
    for (int i = 0; i < n; i++) {
      in[i] = out[i] = 0;
      covered[i] = false;
      for (int j = 0; j < n; j++) adjacent[i].push_back(false);
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (edge[i][j] && scc[i] != scc[j]) {
          if (!adjacent[scc[i]][scc[j]]) {
            out[scc[i]]++;
            in[scc[j]]++;
            adjacent[scc[i]][scc[j]] = true;
          }
        }
      }
    }

    int c;
    for (c = 0; ; c++) {
      int i = argmin(in, covered, n);
      if (i == -1) break;
      dfs(i, n, adjacent, covered);
    }
    fout << c << endl << max(count(in, in + n, 0), count(out, out + n, 0))
         << endl;
  }
  fout.close();
  return 0;
}

#include <bits/stdc++.h>

using namespace std;
void IS_CUTPOINT(int u);
int n;                 // number of nodes
vector<vector<int>> g; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int u, int pu = -1) {
  visited[u] = true;

  tin[u] = low[u] = timer++;
  int children = 0;

  for (int to : g[u]) {
    if (to == pu)
      continue;
    if (visited[to]) {
      low[u] = min(low[u], tin[to]);
    } else {
      dfs(to, u);
      low[u] = min(low[u], low[to]);
      if (low[to] >= tin[u] && pu != -1)
        IS_CUTPOINT(u);
      ++children;
    }
  }

  if (pu == -1 && children > 1)
    IS_CUTPOINT(u);
}

void find_cutpoints() {
  timer = 0;
  visited.assign(n, false);
  tin.assign(n, -1);
  low.assign(n, -1);

  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      dfs(i);
  }
}
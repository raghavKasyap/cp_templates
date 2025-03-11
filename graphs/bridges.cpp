#include <bits/stdc++.h>

using namespace std;

void IS_BRIDGE(int v, int to); // some function to process the found bridge
int n;                         // number of nodes
vector<vector<int>> g;       // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int u, int pu = -1) {
  visited[u] = true;
  tin[u] = low[u] = timer++;

  bool parent_skipped = false;
  for (auto v : g[u]) {
    if (v == pu && !parent_skipped) {
      parent_skipped = true;
      continue;
    }

    if (visited[v]) {
      low[u] = min(low[u], tin[v]);
    } else {
      dfs(v, u);
      low[u] = min(low[u], low[v]);

      // bridge condition
      if (low[v] > tin[u])
        IS_BRIDGE(u, v);
    }
  }
}

void find_bridges() {
  timer = 0;
  visited.assign(n, false);
  tin.assign(n, -1);
  low.assign(n, -1);
  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      dfs(i);
  }
}
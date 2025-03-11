#include <bits/stdc++.h>

using namespace std;

class DisjointSet {
public:
  vector<int> rank, parent, size;
  DisjointSet(int n) {
    rank.resize(n + 1, 0);
    parent.resize(n + 1, 0);
    size.resize(n + 1, 1);

    for (int i = 1; i < n + 1; i++) {
      parent[i] = i;
    }
  }

  // helper function to find the ultimate parent of node
  int findUparent(int node) {
    if (parent[node] == node)
      return node;

    return parent[node] = findUparent(parent[node]);
  }

  // union by rank function
  // remember this is the rank and not height
  // rank is a upper limit on the height of the tree as
  // after path compression we are not updating the rank
  void unionByRank(int u, int v) {
    int up_u = findUparent(u);
    int up_v = findUparent(v);

    if (up_v != up_u) {
      if (rank[up_u] < rank[up_v]) {
        parent[up_u] = up_v;
      } else if (rank[up_v] < rank[up_u]) {
        parent[up_v] = up_u;
      } else {
        parent[up_u] = up_v;
        rank[up_v] += 1;
      }
    }
  }

  // size shows the size of the tree
  void unionBySize(int u, int v) {
    int up_u = findUparent(u);
    int up_v = findUparent(v);

    if (up_v != up_u) {
      if (size[up_u] < size[up_v]) {
        parent[up_u] = up_v;
        size[up_v] += size[up_u];
      } else {
        parent[up_v] = up_u;
        size[up_u] += size[up_v];
      }
    }
  }
};
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MOD = 1000000007; // 998244353

#define fastIO                                                                 \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);                                                              \
  cout.precision(numeric_limits<double>::max_digits10);
#define ll long long
#define ull unsigned long long
#define ld long double
#define lcm(a, b) (a / __gcd(a, b) * b)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define setbits(n) __builtin_popcountll(n)
#define bitsize(n) (63 - __builtin_clzll(n))
#define yn(a) cout << ((a) ? "YES\n" : "NO\n")
void yes() { cout << "YES" << endl; }
void no() { cout << "NO" << endl; }
void ne() { cout << -1 << endl; }
template <typename T> void log(const vector<T> &vec) {
  for (const auto &val : vec)
    cout << val << ' ';
  cout << '\n';
}
template <typename T> void inp(vector<T> &vec) {
  for (auto &val : vec)
    cin >> val;
}

/*-----------------------------------------------------------------------------*/

/*

O(NlogN) - for preprocessing the tree, and then  
O(logN)  - for each LCA query.
O(NlogN) - space for the up array
*/

int n, L;
vector<vector<int>> adj;

int timer;
vector<int> tin, tout;  // to figure ancestor relationship
vector<vector<int>> up; // find any ancestor in O(logN)

void dfs(int v, int p) {
  tin[v] = ++timer;
  up[v][0] = p;

  // implementation of up is very good
  for (int i = 1; i <= L; ++i)
    up[v][i] = up[up[v][i - 1]][i - 1];

  for (int u : adj[v]) {
    if (u != p)
      dfs(u, v);
  }

  tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
  if (is_ancestor(u, v))
    return u;

  if (is_ancestor(v, u))
    return v;

  for (int i = L; i >= 0; --i) {
    if (!is_ancestor(up[u][i], v))
      u = up[u][i];
  }

  return up[u][0];
}

void preprocess(int root) {
  tin.resize(n);
  tout.resize(n);
  timer = 0;
  L = ceil(log2(n));
  up.assign(n, vector<int>(L + 1));
  dfs(root, root);
}
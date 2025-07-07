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

const int MAXN = 1e6;

/*
  Kruskal's Reconstruction Tree / Reachability Tree
    - used to find the max/min weight edge from u to v
    - generally combined with LCA to kind answers to queries in O(1)
  
  ref - https://mzhang2021.github.io/cp-blog/kruskal/
*/

// id is the next unused id to assign to any new node created
// par is the standard definition of dsu parent
// adj will store the KRT
int id, parent[2 * MAXN];
vector<int> adj[2 * MAXN];

int find(int u) { return parent[u] == u ? u : parent[u] = find(parent[u]); }

void unite(int u, int v) {
  u = find(u), v = find(v);
  if (u == v)
    return;
  parent[u] = parent[v] = parent[id] = id;
  adj[id] = {u, v};
  id++;
}
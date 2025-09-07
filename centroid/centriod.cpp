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

const int N = 1e5 + 5;
int n;
vector<int> centroids;
vector<int> tree[N];
int sz[N], parent[N];

void dfs(int u, int pu = -1) {
  sz[u] = 1;
  parent[u] = pu;
  bool is_centroid = true;

  for (int v : tree[u]) {
    if (v == pu)
      continue;
    dfs(v, u);
    sz[u] += sz[v];
    if (sz[v] > n / 2) {
      is_centroid = false;
    }
  }

  if (pu != -1 && n - sz[u] > n / 2) {
    is_centroid = false;
  }

  if (is_centroid) {
    centroids.push_back(u);
  }
}

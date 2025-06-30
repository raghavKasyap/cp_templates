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
  ref -
  https://cp-algorithms.com/data_structures/segment_tree.html#saving-the-entire-subarrays-in-each-vertex

  Segment Tree
  - Merge Sort Tree -> storing the entire subsegment in sorted order
  - using stl merge aglorithm to build the tree

  - Space complexity - O(nlogn) (non-trivial)
  - Query Processing TC - O(log^2(n))
*/

const int MAXN = 1e6;
int n;
vector<int> tree[4 * MAXN];

void build(int a[], int v, int tl, int tr) {
  if (tl == tr) {
    tree[v] = vector<int>(1, a[tl]);
  } else {
    int tm = (tl + tr) / 2;
    build(a, v * 2, tl, tm);
    build(a, v * 2 + 1, tm + 1, tr);
    merge(tree[v * 2].begin(), tree[v * 2].end(), tree[v * 2 + 1].begin(),
          tree[v * 2 + 1].end(), back_inserter(tree[v]));
  }
}

int query(int v, int tl, int tr, int l, int r, int x) {
  if (l > r)
    return INF;

  if (l == tl && r == tr) {
    vector<int>::iterator pos = lower_bound(tree[v].begin(), tree[v].end(), x);
    if (pos != tree[v].end())
      return *pos;
    return INF;
  }

  int tm = (tl + tr) / 2;
  return min(query(v * 2, tl, tm, l, min(r, tm), x),
             query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x));
}
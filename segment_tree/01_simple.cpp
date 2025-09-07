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
  https://cp-algorithms.com/data_structures/segment_tree.html#simplest-form-of-a-segment-tree

  Segment Tree
  - query the sum of elements in range a[l....r] - o(log(n))
  - handling changing values using assignement (a[i] = x) - o(log(n))
*/

const int MAXN = 1e6;
int n, tree[4 * MAXN];

void build(int a[], int v, int l, int r) {
  if (l == r) {
    tree[v] = a[l];
  } else {
    int tm = (l + r) / 2;
    build(a, v * 2, l, tm);
    build(a, v * 2 + 1, tm + 1, r);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
  }
}

// range query
int sum(int v, int tl, int tr, int l, int r) {
  if (l > r)
    return 0;

  if (l == tl && r == tr) {
    return tree[v];
  }

  int tm = (tl + tr) / 2;
  return sum(v * 2, tl, tm, l, min(r, tm)) +
         sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

// point update
void update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    tree[v] = new_val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      update(v * 2, tl, tm, pos, new_val);
    else
      update(v * 2 + 1, tm + 1, tr, pos, new_val);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
  }
}
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
  https://cp-algorithms.com/data_structures/segment_tree.html#adding-on-segments-querying-for-maximum

  - Modification Query is to add a value x to segment a[l...r] - update()
  - Query to get maximum value in range a[l....r]
*/

const int MAXN = 1e6;
int n, tree[4 * MAXN], a[MAXN];
int lazy[4 * MAXN]; // has the value to be added to children

void build(int a[], int v, int tl, int tr) {
  if (tl == tr) {
    tree[v] = a[tl];
  } else {
    int tm = (tl + tr) / 2;
    build(a, v * 2, tl, tm);
    build(a, v * 2 + 1, tm + 1, tr);
    tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
  }
}

void push(int v) {
  tree[v * 2] += lazy[v];
  lazy[v * 2] += lazy[v];
  tree[v * 2 + 1] += lazy[v];
  lazy[v * 2 + 1] += lazy[v];
  lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int addend) {
  if (l > r)
    return;

  if (l == tl && tr == r) {
    tree[v] += addend;
    lazy[v] += addend;
  } else {
    push(v); // push only when required

    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, min(r, tm), addend);
    update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
    tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
  }
}

int query(int v, int tl, int tr, int l, int r) {
  if (l > r)
    return -INF;

  if (l == tl && tr == r)
    return tree[v];

  push(v);

  // this logic remains exactly the same
  int tm = (tl + tr) / 2;
  return max(query(v * 2, tl, tm, l, min(r, tm)),
             query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}
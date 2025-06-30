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
int n, tree[4 * MAXN];
bool marked[4 * MAXN];

void build(int a[], int v, int tl, int tr) {
  if (tl == tr) {
    tree[v] = a[tl];
  } else {
    int tm = (tl + tr) / 2;
    build(a, v * 2, tl, tm);
    build(a, v * 2 + 1, tm + 1, tr);
    tree[v] = 0;
  }
}

// lazy push function which passes the computation to children
void push(int v) {
  if (marked[v]) {
    tree[v * 2] = tree[v * 2 + 1] = tree[v];
    marked[v * 2] = marked[v * 2 + 1] = true;
    marked[v] = false;
  }
}

void update(int v, int tl, int tr, int l, int r, int new_val) {
  if (l > r)
    return;
  if (l == tl && tr == r) {
    tree[v] = new_val;
    marked[v] = true;
  } else {
    push(v);
    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, min(r, tm), new_val);
    update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, new_val);
  }
}

int get(int v, int tl, int tr, int pos) {
  if (tl == tr) {
    return tree[v];
  }

  push(v);
  int tm = (tl + tr) / 2;
  if (pos <= tm)
    return get(v * 2, tl, tm, pos);
  else
    return get(v * 2 + 1, tm + 1, tr, pos);
}
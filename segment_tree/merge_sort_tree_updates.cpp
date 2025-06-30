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
int n;
multiset<int> tree[4 * MAXN];
int a[MAXN];

void build(int a[], int v, int tl, int tr) {
  if (tl == tr) {
    multiset<int> cur;
    cur.insert(a[tl]);

    tree[v] = cur;
  } else {
    int tm = (tl + tr) / 2;
    build(a, v * 2, tl, tm);
    build(a, v * 2 + 1, tm + 1, tr);
    merge(tree[v * 2].begin(), tree[v * 2].end(), tree[v * 2 + 1].begin(),
          tree[v * 2 + 1].end(), back_inserter(tree[v]));
  }
}

// range query - find the smallest element greater than x
int query(int v, int tl, int tr, int l, int r, int x) {
  if (l > r)
    return INF;

  if (l == tl && r == tr) {
    auto pos = tree[v].lower_bound(x);
    if (pos != tree[v].end())
      return *pos;
    return INF;
  }

  int tm = (tl + tr) / 2;
  return min(query(v * 2, tl, tm, l, min(r, tm), x),
             query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x));
}

// point update
void update(int v, int tl, int tr, int pos, int new_val) {
  tree[v].erase(tree[v].find(a[pos]));
  tree[v].insert(new_val);
  if (tl != tr) {
    int tm = (tl + tr) / 2;
    if (pos <= tm)
      update(v * 2, tl, tm, pos, new_val);
    else
      update(v * 2 + 1, tm + 1, tr, pos, new_val);
  } else {
    a[pos] = new_val;
  }
}
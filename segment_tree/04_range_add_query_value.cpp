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
  https://cp-algorithms.com/data_structures/segment_tree.html#addition-on-segments

  - Modification query should add a number x to all numbers in the segment
    a[l...r] - update()
  - Query for value of any index - get()

  - doesn't contain any lazy propration, the update function just goes through
    and updates each node in the segment tree
  
  - the value stored at each node is initially zero and the new value which
    updates a segment is added to root of subtree containing those elements
  
    - the get function takes care of adding the values from root to i based on
    values at each nodes in the path
*/

const int MAXN = 1e6;
int n, tree[4 * MAXN];

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

// add value to range a[l....r]
void update(int v, int tl, int tr, int l, int r, int add) {
  if (l > r)
    return;

  if (l == tl && r == tr) {
    tree[v] += add;
  } else {
    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, min(r, tm), add);
    update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, add);
  }
}

// get a[i]
int get(int v, int tl, int tr, int pos) {
  if (tl == tr)
    return tree[v];
  int tm = (tl + tr) / 2;
  if (pos <= tm)
    return tree[v] + get(v * 2, tl, tm, pos);
  else
    return tree[v] + get(v * 2 + 1, tm + 1, tr, pos);
}
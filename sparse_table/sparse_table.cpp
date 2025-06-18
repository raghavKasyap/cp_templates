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

const int K = 25;
const int MAXN = 1e6;
ll st[K + 1][MAXN];

// range max query
ll f_max(ll a, ll b) { return max(a, b); }
ll range_max(int l, int r) {
  int len = r - l + 1;
  int x = floor(log2(len));

  return max(st[x][l], st[x][r - (1 << x) + 1]);
}

// range sum query
ll f_sum(ll a, ll b) { return a + b; }
ll range_sum(int l, int r) {
  long long sum = 0;
  for (int i = K; i >= 0; i--) {
    if ((1 << i) <= r - l + 1) {
      sum += st[i][l];
      l += 1 << i;
    }
  }
}

// range min query
ll f_mn(ll a, ll b) { return min(a, b); }
ll range_max(int l, int r) {
  int len = r - l + 1;
  int x = floor(log2(len));

  return min(st[x][l], st[x][r - (1 << x) + 1]);
}

// API for using sparse table

auto f = f_max;         // combining method
auto range = range_max; // range method

void precompute(vector<ll> &a) {
  int n = a.size();
  copy(all(a), st[0]);

  for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= n; j++)
      st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#define lcm(a, b) (a / __gcd(a, b) * b)
#define all(x) (x).begin(), (x).end()

/****************** Debug Setup Start ******************/
#ifndef ONLINE_JUDGE
#define debug(x)                                                               \
  cerr << #x << " ";                                                           \
  _print(x);                                                                   \
  cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) { cerr << t; }
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(lld t) { cerr << t; }
void _print(double t) { cerr << t; }
void _print(ull t) { cerr << t; }

template <class T, class V> void _print(pair<T, V> p);
template <class T> void _print(vector<T> v);
template <class T> void _print(set<T> v);
template <class T, class V> void _print(map<T, V> v);
template <class T> void _print(multiset<T> v);

template <class T, class V> void _print(pair<T, V> p) {
  cerr << "{";
  _print(p.first);
  cerr << ",";
  _print(p.second);
  cerr << "}";
}
template <class T> void _print(vector<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(set<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T> void _print(multiset<T> v) {
  cerr << "[ ";
  for (T i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}
template <class T, class V> void _print(map<T, V> v) {
  cerr << "[ ";
  for (auto i : v) {
    _print(i);
    cerr << " ";
  }
  cerr << "]";
}

ll binpow(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = res * a;

    a = a * a;
    b = b >> 1;
  }
  return res;
}

ll modpow(ll a, ll b, ll mod) {
  a %= mod;
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = (res * (a % mod)) % mod;

    a = (a * a) % mod;
    b = b >> 1;
  }

  return res;
}

/****************** Input **********************/
void inp(vector<int> &a) {
  int n = a.size();
  for (int i = 0; i < n; i++)
    cin >> a[i];
}
void inp(vector<ll> &a) {
  int n = a.size();
  for (int i = 0; i < n; i++)
    cin >> a[i];
}
void inp(vector<vector<int>> &a) {
  int n = a.size();
  int m = a[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      cin >> a[i][j];
  }
}
void inp(vector<vector<ll>> &a) {
  int n = a.size();
  int m = a[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      cin >> a[i][j];
  }
}

/****************** Output *******************/
void yes() { cout << "YES" << endl; }
void no() { cout << "NO" << endl; }
void ne() { cout << -1 << endl; }
#define yn(a) cout << ((a) ? "YES\n" : "NO\n")

void log(vector<int> &a) {
  for (auto &x : a)
    cout << x << " ";
  cout << endl;
}
void log(vector<ll> &a) {
  for (auto &x : a)
    cout << x << " ";
  cout << endl;
}
void log(vector<vector<int>> &a) {
  int n = a.size();
  int m = a[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      cout << a[i][j] << " ";
    cout << endl;
  }
}
void log(vector<vector<ll>> &a) {
  int n = a.size();
  int m = a[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      cout << a[i][j] << " ";
    cout << endl;
  }
}

/****************** Solve Problem *******************/

void solve() {}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int t;
  // t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}

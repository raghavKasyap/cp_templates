#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MOD = 1000000007;

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
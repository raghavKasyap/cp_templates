#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MOD = 1000000007;

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
template <typename T> void log(const std::vector<T> &vec) {
  for (const auto &val : vec)
    std::cout << val << ' ';
  std::cout << '\n';
}

/*-----------------------------------------------------------------------------*/

void solve() {}

int main() {
  fastIO;

  int t;
  // t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}

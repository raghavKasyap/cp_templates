#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const ll MOD = 1e9 + 7;

// modular multiplication of 2 numbers a, b
// here we have broken down multiplication to log(a) additions
ll mod_mul(ll a, ll b, ll mod = MOD) {
  ll res = 0;

  while (a > 0) {
    if (a % 2)
      res = (res + b % mod) % mod;

    b = (2 * b) % mod;
    a = a >> 1;
  }

  return res;
}

int main() {
  ll a = 2, b = 3;
  cout << mod_mul(a, b, 5) << endl;
}
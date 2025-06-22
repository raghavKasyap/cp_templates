#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int N = 2e6 + 5;

// o(n) space and time
ll factorial[N];
ll inv_factorial[N];

ll binary_exponentiation(ll a, ll b, ll mod) {
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

ll mod_inverse(ll a, ll mod = 1e7 + 9) {
  return binary_exponentiation(a, mod - 2, mod);
}

// n! / (n - r)! * r!
ll nCr(ll n, ll r, int p) {
  ll ans = inv_factorial[r];
  for (int i = 1; i <= r; i++) {
    ans = (ans * (n - i + 1)) % p;
  }
  return ans;
}

// n! / (n - r)!
ll nPr(ll n, ll r, ll mod = 1e7 + 9) {
  ll ans = 1;
  for (int i = 1; i <= r; i++) {
    ans = (ans * (n - i + 1)) % mod;
  }
  return ans;
}

// prepopulate first
void fill_factorial_array(int n, ll mod = 1e7 + 9) {
  factorial[0] = 1;
  for (int i = 1; i <= n; i++)
    factorial[i] = (factorial[i - 1] * i) % mod;

  inv_factorial[n] = mod_inverse(factorial[n], mod);

  for (int i = n - 1; i >= 0; i--)
    inv_factorial[i] = inv_factorial[i + 1] * (i + 1) % mod;
}
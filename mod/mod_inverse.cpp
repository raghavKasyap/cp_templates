#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll x1, y1;
  ll d = extended_gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

// returns a ^ -1
ll mod_inverse(ll a, ll mod = 1e7 + 9) {
  ll x0, y0;
  extended_gcd(a, mod, x0, y0);
  return x0;
}

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

// this will work only if mod is prime
ll mod_inverse_fermat_little(ll a, ll mod = 1e7 + 9) {
  return binary_exponentiation(a, mod - 2, mod);
}

// write main function to check the above implementations
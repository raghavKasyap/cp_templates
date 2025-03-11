#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

ll binary_exponentiation(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = res * a;

    a = a * a;
    b = b >> 1;
  }
  return res;
}

ll modulus_binary_exponentiation(ll a, ll b, ll mod) {
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
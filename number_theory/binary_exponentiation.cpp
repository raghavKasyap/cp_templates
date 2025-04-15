#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int MOD;

// binary exponentiation
ll pow(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = res * a;

    a = a * a;
    b = b >> 1;
  }
  return res;
}

// modulus binary exponentiation
ll powm(ll a, ll b) {
  a %= MOD;
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = (res * (a % MOD)) % MOD;

    a = (a * a) % MOD;
    b = b >> 1;
  }

  return res;
}
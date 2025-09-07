#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct mint {
  ll x;
  static ll MOD;

  mint(ll x = 0) { this->x = ((x % MOD) + MOD) % MOD; }

  mint &operator+=(const mint a) {
    if ((x += a.x) >= MOD)
      x -= MOD;
    return *this;
  }

  mint &operator-=(const mint a) {
    if ((x += MOD - a.x) >= MOD)
      x -= MOD;
    return *this;
  }

  mint &operator*=(const mint a) {
    (x *= a.x) %= MOD;
    return *this;
  }

  mint operator+(const mint a) const {
    mint res(*this);
    return res += a;
  }

  mint operator-(const mint a) const {
    mint res(*this);
    return res -= a;
  }

  mint operator*(const mint a) const {
    mint res(*this);
    return res *= a;
  }

  friend mint powmod(mint a, int b) {
    mint res = 1;
    while (b > 0) {
      if (b & 1) {
        res *= a;
      }
      a *= a, b >>= 1;
    }
    return res;
  }

  int val() const { return x; }

  mint inv() const { return powmod(*this, MOD - 2); }

  mint &operator/=(const mint a) { return (*this) *= a.inv(); }

  mint operator/(const mint a) const {
    mint res(*this);
    return res /= a;
  }

  friend std::istream &operator>>(std::istream &is, mint &a) {
    int v;
    is >> v;
    a = mint(v);
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const mint &a) {
    return os << a.val();
  }

  friend bool operator==(mint lhs, mint rhs) { return lhs.val() == rhs.val(); }

  friend bool operator!=(mint lhs, mint rhs) { return lhs.val() != rhs.val(); }
};
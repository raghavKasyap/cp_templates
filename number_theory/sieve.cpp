#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

vector<bool> sieve(int n) {
  int n;
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i] && (long long)i * i <= n) {
      for (int j = i * i; j <= n; j += i)
        is_prime[j] = false;
    }
  }

  return is_prime;
}

// Note: this sieve is O(n), but the constant factor is worse than the O(n log
// log n) sieve due to the multiplication.
vector<int> smallest_factor;
vector<bool> prime;
vector<int> primes;

void linear_seive(int maximum) {
  maximum = max(maximum, 1);
  smallest_factor.assign(maximum + 1, 0);
  prime.assign(maximum + 1, true);
  prime[0] = prime[1] = false;
  primes = {};

  for (int i = 2; i <= maximum; i++) {
    if (prime[i]) {
      smallest_factor[i] = i;
      primes.push_back(i);
    }

    for (int p : primes) {
      if (p > smallest_factor[i] || int64_t(i) * p > maximum)
        break;

      prime[i * p] = false;
      smallest_factor[i * p] = p;
    }
  }
}
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct FenwickTree {
  vector<ll> bit; // binary indexed tree
  int n;

  FenwickTree(int n) {
    this->n = n;
    bit.assign(n, 0);
  }

  // O(nlogn) construction
  // FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
  //   for (size_t i = 0; i < a.size(); i++)
  //     add(i, a[i]);
  // }

  // linear construction
  // comes from the fact that i -> i | (i + 1)
  FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
    for (int i = 0; i < n; i++) {
      bit[i] += a[i];
      int r = i | (i + 1);
      if (r < n)
        bit[r] += bit[i];
    }
  }

  ll sum(int r) {
    int ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret += bit[r];
    return ret;
  }

  ll sum(int l, int r) { return sum(r) - sum(l - 1); }

  // here delta is the change
  void add(int idx, int delta) {
    for (; idx < n; idx = idx | (idx + 1))
      bit[idx] += delta;
  }
};

struct FenwickTreeMin {
  vector<int> bit;
  int n;
  const int INF = (int)1e9;

  FenwickTreeMin(int n) {
    this->n = n;
    bit.assign(n, INF);
  }

  FenwickTreeMin(vector<int> a) : FenwickTreeMin(a.size()) {
    for (size_t i = 0; i < a.size(); i++)
      update(i, a[i]);
  }

  int getmin(int r) {
    int ret = INF;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret = min(ret, bit[r]);
    return ret;
  }

  void update(int idx, int val) {
    for (; idx < n; idx = idx | (idx + 1))
      bit[idx] = min(bit[idx], val);
  }
};

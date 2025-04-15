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

struct FenwickTreeOneBasedIndexing {
  vector<int> bit; // binary indexed tree
  int n;

  FenwickTreeOneBasedIndexing(int n) {
    this->n = n + 1;
    bit.assign(n + 1, 0);
  }

  FenwickTreeOneBasedIndexing(vector<int> a)
      : FenwickTreeOneBasedIndexing(a.size()) {
    for (size_t i = 0; i < a.size(); i++)
      add(i, a[i]);
  }

  int sum(int idx) {
    int ret = 0;
    for (++idx; idx > 0; idx -= idx & -idx)
      ret += bit[idx];
    return ret;
  }

  int sum(int l, int r) { return sum(r) - sum(l - 1); }

  void add(int idx, int delta) {
    for (++idx; idx < n; idx += idx & -idx)
      bit[idx] += delta;
  }
};

// https://cp-algorithms.com/data_structures/fenwick.html#3-range-update-and-range-query
struct FenwickTreeRangeUpdateRangeQuery {
  // all indices are 1 based.
  vector<ll> b1;
  vector<ll> b2;
  int n;

  FenwickTreeRangeUpdateRangeQuery(int n) {
    this->n = n + 1;
    b1.assign(n + 1, 0);
    b2.assign(n + 1, 0);
  }

  FenwickTreeRangeUpdateRangeQuery(vector<int> a)
      : FenwickTreeRangeUpdateRangeQuery(a.size()) {
    for (size_t i = 1; i <= a.size(); i++) {
      range_add(i, i + 1, a[i - 1]);
    }
  }

  void range_add(int l, int r, ll x) {
    add(b1, l, x);
    add(b1, r + 1, -x);
    add(b2, l, x * (l - 1));
    add(b2, r + 1, -x * r);
  }

  void add(vector<ll> &bit, int idx, int delta) {
    for (; idx < n; idx += idx & -idx)
      bit[idx] += delta;
  }

  ll sum(vector<ll> &bit, int idx) {
    ll ret = 0;
    for (; idx > 0; idx -= idx & -idx)
      ret += bit[idx];
    return ret;
  }

  ll point_query(int idx) { return sum(b1, idx); }

  ll prefix_sum(int idx) { return sum(b1, idx) * idx - sum(b2, idx); }

  ll range_sum(int l, int r) { return prefix_sum(r) - prefix_sum(l - 1); }
};
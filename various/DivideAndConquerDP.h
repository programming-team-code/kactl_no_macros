/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: Codeforces
 * Description: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal)
 * optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Time: O((N + (hi-lo)) \log N)
 * Status: tested on http://codeforces.com/contest/321/problem/E
 */
struct DP {  // Modify at will:
  int lo(int ind) { return 0; }
  int hi(int ind) { return ind; }
  int64_t f(int ind, int k) { return dp[ind][k]; }
  void store(int ind, int k, int64_t v) { res[ind] = pair<int, int>(k, v); }
  void rec(int L, int R, int LO, int HI) {
    if (L >= R) return;
    int mid = (L + R) >> 1;
    pair<int64_t, int> best(LLONG_MAX, LO);
    for (int k = max(LO, lo(mid)); k < (min(HI, hi(mid))); k++)
      best = min(best, make_pair(f(mid, k), k));
    store(mid, best.second, best.first);
    rec(L, mid, LO, best.second + 1);
    rec(mid + 1, R, best.second, HI);
  }
  void solve(int L, int R) { rec(L, R, INT_MIN, INT_MAX); }
};

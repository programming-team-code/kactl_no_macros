/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: Wikipedia
 * Description: Recovers any $n$-order linear recurrence
 * relation from the first $2n$ terms of the recurrence.
 * Useful for guessing linear recurrences after
 * brute-forcing the first terms. Should work on any field,
 * but numerical stability for floats is not guaranteed.
 * Output will have size $\le n$.
 * Usage: berlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}
 * Time: O(N^2)
 * Status: bruteforce-tested mod 5 for n <= 5 and all s
 */
/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
const int64_t mod = 1000000007; // faster if const
int64_t modpow(int64_t b, int64_t e) {
  int64_t ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
vector<int64_t> berlekampMassey(vector<int64_t> s) {
  int n = (int)(s).size(), L = 0, m = 0;
  vector<int64_t> C(n), B(n), T;
  C[0] = B[0] = 1;
  int64_t b = 1;
  for (int i = 0; i < (n); i++) {
    ++m;
    int64_t d = s[i] % mod;
    for (int j = 1; j < (L + 1); j++)
      d = (d + C[j] * s[i - j]) % mod;
    if (!d) continue;
    T = C;
    int64_t coef = d * modpow(b, mod - 2) % mod;
    for (int j = m; j < (n); j++)
      C[j] = (C[j] - coef * B[j - m]) % mod;
    if (2 * L > i) continue;
    L = i + 1 - L;
    B = T;
    b = d;
    m = 0;
  }
  C.resize(L + 1);
  C.erase(C.begin());
  for (int64_t& x : C) x = (mod - x) % mod;
  return C;
}

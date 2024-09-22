/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source:
 * http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Tonelli-Shanks algorithm for modular square
 * roots. Finds $x$ s.t. $x^2 = a \pmod p$ ($-x$ gives the
 * other solution). Time: O(\log^2 p) worst case, O(\log p)
 * for most $p$ Status: Tested for all a,p <= 10000
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
int64_t sqrt(int64_t a, int64_t p) {
  a %= p;
  if (a < 0) a += p;
  if (a == 0) return 0;
  assert(
    modpow(a, (p - 1) / 2, p) == 1); // else no solution
  if (p % 4 == 3) return modpow(a, (p + 1) / 4, p);
  // a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
  int64_t s = p - 1, n = 2;
  int r = 0, m;
  while (s % 2 == 0) ++r, s /= 2;
  /// find a non-square mod p
  while (modpow(n, (p - 1) / 2, p) != p - 1) ++n;
  int64_t x = modpow(a, (s + 1) / 2, p);
  int64_t b = modpow(a, s, p), g = modpow(n, s, p);
  for (;; r = m) {
    int64_t t = b;
    for (m = 0; m < r && t != 1; ++m) t = t * t % p;
    if (m == 0) return x;
    int64_t gs = modpow(g, 1LL << (r - m - 1), p);
    g = gs * gs % p;
    x = x * gs % p;
    b = b * g % p;
  }
}

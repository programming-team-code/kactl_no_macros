/**
 * Author: chilli, c1729, Simon Lindholm
 * Date: 2019-03-28
 * License: CC0
 * Source: Wikipedia, https://miller-rabin.appspot.com/
 * Description: Deterministic Miller-Rabin primality test.
 * Guaranteed to work for numbers up to $7 \cdot 10^{18}$;
 * for larger numbers, use Python and extend A randomly.
 * Time: 7 times the complexity of $a^b \mod c$.
 * Status: Stress-tested
 */
/**
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Date: 2019-04-24
 * License: CC0
 * Source:
 * https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod
 * c$) for $0 \le a, b \le c \le 7.2\cdot 10^{18}$. Time:
 * O(1) for \texttt{modmul}, O(\log b) for \texttt{modpow}
 * Status: stress-tested, proven correct
 * Details:
 * This runs ~2x faster than the naive (__int128_t)a * b %
 * M. A proof of correctness is in doc/modmul-proof.tex. An
 * earlier version of the proof, from when the code used a
 * * b / (long double)M, is in doc/modmul-proof.md. The
 * proof assumes that long doubles are implemented as x87
 * 80-bit floats; if they are 64-bit, as on e.g. MSVC, the
 * implementation is only valid for $0 \le a, b \le c <
 * 2^{52} \approx 4.5 \cdot 10^{15}$.
 */
typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
  int64_t ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (int64_t)M);
}
ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}
bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull A[] = {2, 325, 9375, 28178, 450775, 9780504,
    1795265022},
      s = __builtin_ctzll(n - 1), d = n >> s;
  for (ull a : A) { // ^ count trailing zeroes
    ull p = modpow(a % n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--)
      p = modmul(p, p, n);
    if (p != n - 1 && i != s) return 0;
  }
  return 1;
}

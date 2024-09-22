/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: Chinese Remainder Theorem.
 *
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv
 * a \pmod m$, $x\equiv b \pmod n$. If $|a| < m$ and $|b| <
 * n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$. Assumes
 * $mn < 2^{62}$. Time: $\log(n)$ Status: Works
 */
/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds two integers $x$ and $y$, such that
 * $ax+by=\gcd(a,b)$. If you just need gcd, use the built
 * in \texttt{\_\_gcd} instead. If $a$ and $b$ are coprime,
 * then $x$ is the inverse of $a \pmod{b}$.
 */
int64_t euclid(int64_t a, int64_t b, int64_t &x,
  int64_t &y) {
  if (!b) return x = 1, y = 0, a;
  int64_t d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}
int64_t crt(int64_t a, int64_t m, int64_t b, int64_t n) {
  if (n > m) swap(a, b), swap(m, n);
  int64_t x, y, g = euclid(m, n, x, y);
  assert((a - b) % g == 0); // else no solution
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}

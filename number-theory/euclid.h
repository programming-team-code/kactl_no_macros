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

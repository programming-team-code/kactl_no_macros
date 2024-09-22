/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need
 * to set {\tt mod} to some number first and then you can
 * use the structure.
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
const int64_t mod = 17; // change to something else
struct Mod {
  int64_t x;
  Mod(int64_t xx): x(xx) {}
  Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
  Mod operator-(Mod b) {
    return Mod((x - b.x + mod) % mod);
  }
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) { return *this * invert(b); }
  Mod invert(Mod a) {
    int64_t x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(int64_t e) {
    if (!e) return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
};

/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Fast integration using an adaptive
 Simpson's rule.
 * Usage:
        double sphereVolume = quad(-1, 1, [](double x) {
        return quad(-1, 1, [\&](double y) {
        return quad(-1, 1, [\&](double z) {
        return x*x + y*y + z*z < 1; });});});
 * Status: mostly untested
 */
typedef double d;
template<class F> d rec(F& f, d a, d b, d eps, d S) {
  d c = (a + b) / 2;
  d S1 = (f(a) + 4 * f((a + c) / 2) + f(c)) * (c - a) / 6,
    S2 = (f(c) + 4 * f((c + b) / 2) + f(b)) * (b - c) / 6,
    T = S1 + S2;
  if (abs(T - S) <= 15 * eps || b - a < 1e-10)
    return T + (T - S) / 15;
  return rec(f, a, c, eps / 2, S1) +
    rec(f, c, b, eps / 2, S2);
}
template<class F> d quad(d a, d b, F f, d eps = 1e-8) {
  return rec(f, a, b, eps,
    (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6);
}

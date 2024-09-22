/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-07
 * License: Boost Software License
 * Source:
 * https://github.com/AlCash07/ACTL/blob/master/include/actl/geometry/algorithm/intersect/line_convex_polygon.hpp
 * Description: Line-convex polygon intersection. The
 * polygon must be ccw and have no collinear points.
 * lineHull(line, poly) returns a pair describing the
 * intersection of a line with the polygon:
 *  \begin{itemize*}
 *    \item $(-1, -1)$ if no collision,
 *    \item $(i, -1)$ if touching the corner $i$,
 *    \item $(i, i)$ if along side $(i, i+1)$,
 *    \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j,
 * j+1)$. \end{itemize*} In the last case, if a corner $i$
 * is crossed, this is treated as happening on side $(i,
 * i+1)$. The points are returned in the same order as the
 * line hits the polygon. \texttt{extrVertex} returns the
 * point of a hull with the max projection onto a line.
 * Time: O(\log n)
 * Status: stress-tested
 */
/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
template<class T> int sgn(T x) {
  return (x > 0) - (x < 0);
}
template<class T> struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0): x(x), y(y) {}
  bool operator<(P p) const {
    return tie(x, y) < tie(p.x, p.y);
  }
  bool operator==(P p) const {
    return tie(x, y) == tie(p.x, p.y);
  }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const {
    return (a - *this).cross(b - *this);
  }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const {
    return *this / dist();
  } // makes dist()=1
  P perp() const {
    return P(-y, x);
  } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the
  // origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a),
      x * sin(a) + y * cos(a));
  }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};
template<class P> int extrVertex(vector<P>& poly, P dir) {
  int n = (int)(poly).size(), lo = 0, hi = n;
  if (sgn(dir.perp().cross(
        poly[(0 + 1) % n] - poly[(0) % n])) >= 0 &&
    sgn(dir.perp().cross(
      poly[(0) % n] - poly[(0 - 1 + n) % n])) < 0)
    return 0;
  while (lo + 1 < hi) {
    int m = (lo + hi) / 2;
    if (sgn(dir.perp().cross(
          poly[(m + 1) % n] - poly[(m) % n])) >= 0 &&
      sgn(dir.perp().cross(
        poly[(m) % n] - poly[(m - 1 + n) % n])) < 0)
      return m;
    int ls = sgn(dir.perp().cross(
          poly[(lo + 1) % n] - poly[(lo) % n])),
        ms = sgn(dir.perp().cross(
          poly[(m + 1) % n] - poly[(m) % n]));
    (ls < ms ||
          (ls == ms &&
            ls ==
              sgn(dir.perp().cross(
                poly[(lo) % n] - poly[(m) % n])))
        ? hi
        : lo) = m;
  }
  return lo;
}
template<class P>
array<int, 2> lineHull(P a, P b, vector<P>& poly) {
  int endA = extrVertex(poly, (a - b).perp());
  int endB = extrVertex(poly, (b - a).perp());
  if (sgn(a.cross(poly[endA], b)) < 0 ||
    sgn(a.cross(poly[endB], b)) > 0)
    return {-1, -1};
  array<int, 2> res;
  for (int i = 0; i < (2); i++) {
    int lo = endB, hi = endA, n = (int)(poly).size();
    while ((lo + 1) % n != hi) {
      int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
      (sgn(a.cross(poly[m], b)) ==
            sgn(a.cross(poly[endB], b))
          ? lo
          : hi) = m;
    }
    res[i] = (lo + !sgn(a.cross(poly[hi], b))) % n;
    swap(endA, endB);
  }
  if (res[0] == res[1]) return {res[0], -1};
  if (!sgn(a.cross(poly[res[0]], b)) &&
    !sgn(a.cross(poly[res[1]], b)))
    switch ((res[0] - res[1] + (int)(poly).size() + 1) %
      (int)(poly).size()) {
    case 0: return {res[0], res[0]};
    case 2: return {res[1], res[1]};
    }
  return res;
}

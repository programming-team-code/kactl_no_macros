/**
 * Author: black_horse2014, chilli
 * Date: 2019-10-29
 * License: Unknown
 * Source: https://codeforces.com/gym/101673/submission/50481926
 * Description: Calculates the area of the union of $n$ polygons (not necessarily
 * convex). The points within each polygon must be given in CCW order.
 * (Epsilon checks may optionally be added to sideOf/sgn, but shouldn't be needed.)
 * Time: $O(N^2)$, where $N$ is the total number of points
 * Status: stress-tested, Submitted on ECNA 2017 Problem A
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
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); }  // makes dist()=1
  P perp() const { return P(-y, x); }  // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};
/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description: Returns where $p$ is as seen from $s$ towards $e$. 1/0/-1 $\Leftrightarrow$ left/on line/right.
 * If the optional argument $eps$ is given 0 is returned if $p$ is within distance $eps$ from the line.
 * P is supposed to be Point<T> where T is e.g. double or long long.
 * It uses products in intermediate steps so watch out for overflow if using int or long long.
 * Usage:
 * 	bool left = sideOf(p1,p2,q)==1;
 * Status: tested
 */
template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
template <class P>
int sideOf(const P& s, const P& e, const P& p, double eps) {
  auto a = (e - s).cross(p - s);
  double l = (e - s).dist() * eps;
  return (a > l) - (a < -l);
}
typedef Point<double> P;
double rat(P a, P b) { return sgn(b.x) ? a.x / b.x : a.y / b.y; }
double polyUnion(vector<vector<P>>& poly) {
  double ret = 0;
  for (int i = 0; i < ((int)(poly).size()); i++)
    for (int v = 0; v < ((int)(poly[i]).size()); v++) {
      P A = poly[i][v], B = poly[i][(v + 1) % (int)(poly[i]).size()];
      vector<pair<double, int>> segs = {{0, 0}, {1, 0}};
      for (int j = 0; j < ((int)(poly).size()); j++)
        if (i != j) {
          for (int u = 0; u < ((int)(poly[j]).size()); u++) {
            P C = poly[j][u], D = poly[j][(u + 1) % (int)(poly[j]).size()];
            int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
            if (sc != sd) {
              double sa = C.cross(D, A), sb = C.cross(D, B);
              if (min(sc, sd) < 0)
                segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
            } else if (!sc && !sd && j < i && sgn((B - A).dot(D - C)) > 0) {
              segs.emplace_back(rat(C - A, B - A), 1);
              segs.emplace_back(rat(D - A, B - A), -1);
            }
          }
        }
      sort(begin(segs), end(segs));
      for (auto& s : segs) s.first = min(max(s.first, 0.0), 1.0);
      double sum = 0;
      int cnt = segs[0].second;
      for (int j = 1; j < ((int)(segs).size()); j++) {
        if (!cnt) sum += segs[j].first - segs[j - 1].first;
        cnt += segs[j].second;
      }
      ret += A.cross(B) * sum;
    }
  return ret / 2;
}

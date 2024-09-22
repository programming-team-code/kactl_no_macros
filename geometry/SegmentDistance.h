/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\begin{minipage}{75mm}
}
Returns the shortest distance between point p and the line
segment from point s to e. \end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Usage:
 * 	Point<double> a, b(2,2), p(1,1);
 * 	bool onSegment = segDist(a,b,p) < 1e-10;
 * Status: tested
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
typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
  if (s == e) return (p - s).dist();
  auto d = (e - s).dist2(),
       t = min(d, max(.0, (p - s).dot(e - s)));
  return ((p - s) * d - (e - s) * t).dist() / d;
}

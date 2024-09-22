/**
 * Author: Mattias de Zalenski
 * Date: Unknown
 * Source: Geometry in C
 * Description: Computes the Delaunay triangulation of a
 * set of points. Each circumcircle contains none of the
 * input points. If any three points are collinear or any
 * four are on the same circle, behavior is undefined.
 * Time: O(n^2)
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
/**
 * Author: Johan Sannemo
 * Date: 2017-04-18
 * Source: derived from
 * https://gist.github.com/msg555/4963794 by Mark Gordon
 * Description: Computes all faces of the 3-dimension hull
 * of a point set. *No four points must be coplanar*, or
 * else random results will be returned. All faces will
 * point outwards. Time: O(n^2) Status: tested on SPOJ CH3D
 */
/**
 * Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Class to handle points in 3D space.
 * 	T can be e.g. double or long long.
 * Usage:
 * Status: tested, except for phi and theta
 */
template<class T> struct Point3D {
  typedef Point3D P;
  typedef const P& R;
  T x, y, z;
  explicit Point3D(T x = 0, T y = 0, T z = 0):
    x(x), y(y), z(z) {}
  bool operator<(R p) const {
    return tie(x, y, z) < tie(p.x, p.y, p.z);
  }
  bool operator==(R p) const {
    return tie(x, y, z) == tie(p.x, p.y, p.z);
  }
  P operator+(R p) const {
    return P(x + p.x, y + p.y, z + p.z);
  }
  P operator-(R p) const {
    return P(x - p.x, y - p.y, z - p.z);
  }
  P operator*(T d) const { return P(x * d, y * d, z * d); }
  P operator/(T d) const { return P(x / d, y / d, z / d); }
  T dot(R p) const { return x * p.x + y * p.y + z * p.z; }
  P cross(R p) const {
    return P(y * p.z - z * p.y, z * p.x - x * p.z,
      x * p.y - y * p.x);
  }
  T dist2() const { return x * x + y * y + z * z; }
  double dist() const { return sqrt((double)dist2()); }
  // Azimuthal angle (longitude) to x-axis in interval
  // [-pi, pi]
  double phi() const { return atan2(y, x); }
  // Zenith angle (latitude) to the z-axis in interval [0,
  // pi]
  double theta() const {
    return atan2(sqrt(x * x + y * y), z);
  }
  P unit() const {
    return *this / (T)dist();
  } // makes dist()=1
  // returns unit vector normal to *this and p
  P normal(P p) const { return cross(p).unit(); }
  // returns point rotated 'angle' radians ccw around axis
  P rotate(double angle, P axis) const {
    double s = sin(angle), c = cos(angle);
    P u = axis.unit();
    return u * dot(u) * (1 - c) + (*this) * c -
      cross(u) * s;
  }
};
typedef Point3D<double> P3;
struct PR {
  void ins(int x) { (a == -1 ? a : b) = x; }
  void rem(int x) { (a == x ? a : b) = -1; }
  int cnt() { return (a != -1) + (b != -1); }
  int a, b;
};
struct F {
  P3 q;
  int a, b, c;
};
vector<F> hull3d(const vector<P3>& A) {
  assert((int)(A).size() >= 4);
  vector<vector<PR>> E((int)(A).size(),
    vector<PR>((int)(A).size(), {-1, -1}));
  vector<F> FS;
  auto mf = [&](int i, int j, int k, int l) {
    P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
    if (q.dot(A[l]) > q.dot(A[i])) q = q * -1;
    F f{q, i, j, k};
    E[f.a][f.b].ins(k);
    E[f.a][f.c].ins(j);
    E[f.b][f.c].ins(i);
    FS.push_back(f);
  };
  for (int i = 0; i < (4); i++)
    for (int j = i + 1; j < (4); j++)
      for (int k = j + 1; k < (4); k++)
        mf(i, j, k, 6 - i - j - k);
  for (int i = 4; i < ((int)(A).size()); i++) {
    for (int j = 0; j < ((int)(FS).size()); j++) {
      F f = FS[j];
      if (f.q.dot(A[i]) > f.q.dot(A[f.a])) {
        E[f.a][f.b].rem(f.c);
        E[f.a][f.c].rem(f.b);
        E[f.b][f.c].rem(f.a);
        swap(FS[j--], FS.back());
        FS.pop_back();
      }
    }
    int nw = (int)(FS).size();
    for (int j = 0; j < (nw); j++) {
      F f = FS[j];
      if (E[f.a][f.b].cnt() != 2) mf(f.a, f.b, i, f.c);
      ;
      if (E[f.a][f.c].cnt() != 2) mf(f.a, f.c, i, f.b);
      ;
      if (E[f.b][f.c].cnt() != 2) mf(f.b, f.c, i, f.a);
      ;
    }
  }
  for (F& it : FS)
    if ((A[it.b] - A[it.a])
          .cross(A[it.c] - A[it.a])
          .dot(it.q) <= 0)
      swap(it.c, it.b);
  return FS;
};
template<class P, class F>
void delaunay(vector<P>& ps, F trifun) {
  if ((int)(ps).size() == 3) {
    int d = (ps[0].cross(ps[1], ps[2]) < 0);
    trifun(0, 1 + d, 2 - d);
  }
  vector<P3> p3;
  for (P p : ps) p3.emplace_back(p.x, p.y, p.dist2());
  if ((int)(ps).size() > 3)
    for (auto t : hull3d(p3))
      if ((p3[t.b] - p3[t.a])
            .cross(p3[t.c] - p3[t.a])
            .dot(P3(0, 0, 1)) < 0)
        trifun(t.a, t.c, t.b);
}

/**
 * Author: Philippe Legault
 * Date: 2016
 * License: MIT
 * Source: https://github.com/Bathlamos/delaunay-triangulation/
 * Description: Fast Delaunay triangulation.
 * Each circumcircle contains none of the input points.
 * There must be no duplicate points.
 * If all points are on a line, no triangles will be returned.
 * Should work for doubles as well, though there may be precision issues in 'circ'.
 * Returns triangles in order \{t[0][0], t[0][1], t[0][2], t[1][0], \dots\}, all counter-clockwise.
 * Time: O(n \log n)
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
typedef Point<int64_t> P;
typedef struct Quad* Q;
typedef __int128_t lll;  // (can be ll if coords are < 2e4)
P arb(LLONG_MAX, LLONG_MAX);  // not equal to any other point
struct Quad {
  Q rot, o;
  P p = arb;
  bool mark;
  P& F() { return r()->p; }
  Q& r() { return rot->rot; }
  Q prev() { return rot->o->rot; }
  Q next() { return r()->prev(); }
}* H;
bool circ(P p, P a, P b, P c) {  // is p in the circumcircle?
  lll p2 = p.dist2(), A = a.dist2() - p2,
      B = b.dist2() - p2, C = c.dist2() - p2;
  return p.cross(a, b) * C + p.cross(b, c) * A + p.cross(c, a) * B > 0;
}
Q makeEdge(P orig, P dest) {
  Q r = H ? H : new Quad{new Quad{new Quad{new Quad{0}}}};
  H = r->o;
  r->r()->r() = r;
  for (int i = 0; i < (4); i++) r = r->rot, r->p = arb, r->o = i & 1 ? r : r->r();
  r->p = orig;
  r->F() = dest;
  return r;
}
void splice(Q a, Q b) {
  swap(a->o->rot->o, b->o->rot->o);
  swap(a->o, b->o);
}
Q connect(Q a, Q b) {
  Q q = makeEdge(a->F(), b->p);
  splice(q, a->next());
  splice(q->r(), b);
  return q;
}
pair<Q, Q> rec(const vector<P>& s) {
  if ((int)(s).size() <= 3) {
    Q a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.back());
    if ((int)(s).size() == 2) return {a, a->r()};
    splice(a->r(), b);
    auto side = s[0].cross(s[1], s[2]);
    Q c = side ? connect(b, a) : 0;
    return {side < 0 ? c->r() : a, side < 0 ? c : b->r()};
  }
  Q A, B, ra, rb;
  int half = (int)(s).size() / 2;
  tie(ra, A) = rec({begin(s), end(s) - half});
  tie(B, rb) = rec({(int)(s).size() - half + begin(s), end(s)});
  while ((B->p.cross(A->F(), A->p) < 0 && (A = A->next())) ||
         (A->p.cross(B->F(), B->p) > 0 && (B = B->r()->o)))
    ;
  Q base = connect(B->r(), A);
  if (A->p == ra->p) ra = base->r();
  if (B->p == rb->p) rb = base;
  for (;;) {
    Q LC = base->r()->o;
    if ((LC->F().cross(base->F(), base->p) > 0))
      while (circ(LC->o->F(), base->F(), base->p, LC->F())) {
        Q t = LC->o;
        splice(LC, LC->prev());
        splice(LC->r(), LC->r()->prev());
        LC->o = H;
        H = LC;
        LC = t;
      };
    Q RC = base->prev();
    if ((RC->F().cross(base->F(), base->p) > 0))
      while (circ(RC->prev()->F(), base->F(), base->p, RC->F())) {
        Q t = RC->prev();
        splice(RC, RC->prev());
        splice(RC->r(), RC->r()->prev());
        RC->o = H;
        H = RC;
        RC = t;
      };
    if (!(LC->F().cross(base->F(), base->p) > 0) && !(RC->F().cross(base->F(), base->p) > 0)) break;
    if (!(LC->F().cross(base->F(), base->p) > 0) || ((RC->F().cross(base->F(), base->p) > 0) && circ(RC->F(), RC->p, LC->F(), LC->p)))
      base = connect(RC, base->r());
    else
      base = connect(base->r(), LC->r());
  }
  return {ra, rb};
}
vector<P> triangulate(vector<P> pts) {
  sort(begin(pts), end(pts));
  assert(unique(begin(pts), end(pts)) == pts.end());
  if ((int)(pts).size() < 2) return {};
  Q e = rec(pts).first;
  vector<Q> q = {e};
  int qi = 0;
  while (e->o->F().cross(e->F(), e->p) < 0) e = e->o;
  {
    Q c = e;
    do {
      c->mark = 1;
      pts.push_back(c->p);
      q.push_back(c->r());
      c = c->next();
    } while (c != e);
  };
  pts.clear();
  while (qi < (int)(q).size())
    if (!(e = q[qi++])->mark) {
      Q c = e;
      do {
        c->mark = 1;
        pts.push_back(c->p);
        q.push_back(c->r());
        c = c->next();
      } while (c != e);
    };
  return pts;
}

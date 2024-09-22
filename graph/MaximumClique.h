/**
 * Author: chilli, SJTU, Janez Konc
 * Date: 2019-05-10
 * License: GPL3+
 * Source:
 * https://en.wikipedia.org/wiki/MaxCliqueDyn_maximum_clique_algorithm,
 * https://gitlab.com/janezkonc/mcqd/blob/master/mcqd.h
 * Description: Quickly finds a maximum clique of a graph
 * (given as symmetric bitset matrix; self-edges not
 * allowed). Can be used to find a maximum independent set
 * by finding a clique of the complement graph. Time: Runs
 * in about 1s for n=155 and worst case random graphs
 * (p=.90). Runs faster for sparse graphs. Status:
 * stress-tested
 */
typedef vector<bitset<200>> vb;
struct Maxclique {
  double limit = 0.025, pk = 0;
  struct Vertex {
    int i, d = 0;
  };
  typedef vector<Vertex> vv;
  vb e;
  vv V;
  vector<vector<int>> C;
  vector<int> qmax, q, S, old;
  void init(vv& r) {
    for (auto& v : r) v.d = 0;
    for (auto& v : r)
      for (auto j : r) v.d += e[v.i][j.i];
    sort(begin(r), end(r),
      [](auto a, auto b) { return a.d > b.d; });
    int mxD = r[0].d;
    for (int i = 0; i < ((int)(r).size()); i++)
      r[i].d = min(i, mxD) + 1;
  }
  void expand(vv& R, int lev = 1) {
    S[lev] += S[lev - 1] - old[lev];
    old[lev] = S[lev - 1];
    while ((int)(R).size()) {
      if (
        (int)(q).size() + R.back().d <= (int)(qmax).size())
        return;
      q.push_back(R.back().i);
      vv T;
      for (auto v : R)
        if (e[R.back().i][v.i]) T.push_back({v.i});
      if ((int)(T).size()) {
        if (S[lev]++ / ++pk < limit) init(T);
        int j = 0, mxk = 1,
            mnk = max(
              (int)(qmax).size() - (int)(q).size() + 1, 1);
        C[1].clear(), C[2].clear();
        for (auto v : T) {
          int k = 1;
          auto f = [&](int i) { return e[v.i][i]; };
          while (any_of(begin(C[k]), end(C[k]), f)) k++;
          if (k > mxk) mxk = k, C[mxk + 1].clear();
          if (k < mnk) T[j++].i = v.i;
          C[k].push_back(v.i);
        }
        if (j > 0) T[j - 1].d = 0;
        for (int k = mnk; k < (mxk + 1); k++)
          for (int i : C[k]) T[j].i = i, T[j++].d = k;
        expand(T, lev + 1);
      } else if ((int)(q).size() > (int)(qmax).size())
        qmax = q;
      q.pop_back(), R.pop_back();
    }
  }
  vector<int> maxClique() {
    init(V), expand(V);
    return qmax;
  }
  Maxclique(vb conn):
    e(conn), C((int)(e).size() + 1), S((int)(C).size()),
    old(S) {
    for (int i = 0; i < ((int)(e).size()); i++)
      V.push_back({i});
  }
};

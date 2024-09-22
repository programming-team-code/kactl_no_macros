/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and
 * increases single elements a[i,j]. Requires that the
 * elements to be updated are known in advance (call
 * fakeUpdate() before init()). Time: $O(\log^2 N)$. (Use
 * persistent segment trees for $O(\log N)$.) Status:
 * stress-tested
 */
/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... +
 * a[pos - 1], and updates single elements a[i], taking the
 * difference between the old and new value. Time: Both
 * operations are $O(\log N)$. Status: Stress-tested
 */
struct FT {
  vector<int64_t> s;
  FT(int n): s(n) {}
  void update(int pos, int64_t dif) { // a[pos] += dif
    for (; pos < (int)(s).size(); pos |= pos + 1)
      s[pos] += dif;
  }
  int64_t query(int pos) { // sum of values in [0, pos)
    int64_t res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
  int lower_bound(
    int64_t sum) { // min pos st sum of [0, pos] >= sum
    // Returns n if no sum is >= sum, or -1 if empty sum
    // is.
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1)
      if (pos + pw <= (int)(s).size() &&
        s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    return pos;
  }
};
struct FT2 {
  vector<vector<int>> ys;
  vector<FT> ft;
  FT2(int limx): ys(limx) {}
  void fakeUpdate(int x, int y) {
    for (; x < (int)(ys).size(); x |= x + 1)
      ys[x].push_back(y);
  }
  void init() {
    for (vector<int>& v : ys)
      sort(begin(v), end(v)),
        ft.emplace_back((int)(v).size());
  }
  int ind(int x, int y) {
    return (int)(lower_bound(begin(ys[x]), end(ys[x]), y) -
      ys[x].begin());
  }
  void update(int x, int y, int64_t dif) {
    for (; x < (int)(ys).size(); x |= x + 1)
      ft[x].update(ind(x, y), dif);
  }
  int64_t query(int x, int y) {
    int64_t sum = 0;
    for (; x; x &= x - 1)
      sum += ft[x - 1].query(ind(x - 1, y));
    return sum;
  }
};

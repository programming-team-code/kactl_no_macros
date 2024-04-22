/**
 * Author: Simon Lindholm
 * Date: 2016-12-09
 * License: CC0
 * Source: http://www.mimuw.edu.pl/~mucha/pub/mucha_sankowski_focs04.pdf
 * Description: Matching for general graphs.
 * Fails with probability $N / mod$.
 * Time: O(N^3)
 * Status: not very well tested
 */
/**
 * Author: Simon Lindholm
 * Date: 2016-12-08
 * Source: The regular matrix inverse code
 * Description: Invert matrix $A$ modulo a prime.
 * Returns rank; result is stored in $A$ unless singular (rank < n).
 * For prime powers, repeatedly set $A^{-1} = A^{-1} (2I - AA^{-1})\  (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(n^3)
 * Status: Slightly tested
 */
/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
const int64_t mod = 1000000007;  // faster if const
int64_t modpow(int64_t b, int64_t e) {
  int64_t ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
int matInv(vector<vector<int64_t>>& A) {
  int n = (int)(A).size();
  vector<int> col(n);
  vector<vector<int64_t>> tmp(n, vector<int64_t>(n));
  for (int i = 0; i < (n); i++) tmp[i][i] = 1, col[i] = i;
  for (int i = 0; i < (n); i++) {
    int r = i, c = i;
    for (int j = i; j < (n); j++)
      for (int k = i; k < (n); k++)
        if (A[j][k]) {
          r = j;
          c = k;
          goto found;
        }
    return i;
  found:
    A[i].swap(A[r]);
    tmp[i].swap(tmp[r]);
    for (int j = 0; j < (n); j++)
      swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
    swap(col[i], col[c]);
    int64_t v = modpow(A[i][i], mod - 2);
    for (int j = i + 1; j < (n); j++) {
      int64_t f = A[j][i] * v % mod;
      A[j][i] = 0;
      for (int k = i + 1; k < (n); k++) A[j][k] = (A[j][k] - f * A[i][k]) % mod;
      for (int k = 0; k < (n); k++) tmp[j][k] = (tmp[j][k] - f * tmp[i][k]) % mod;
    }
    for (int j = i + 1; j < (n); j++) A[i][j] = A[i][j] * v % mod;
    for (int j = 0; j < (n); j++) tmp[i][j] = tmp[i][j] * v % mod;
    A[i][i] = 1;
  }
  for (int i = n - 1; i > 0; --i)
    for (int j = 0; j < (i); j++) {
      int64_t v = A[j][i];
      for (int k = 0; k < (n); k++) tmp[j][k] = (tmp[j][k] - v * tmp[i][k]) % mod;
    }
  for (int i = 0; i < (n); i++)
    for (int j = 0; j < (n); j++)
      A[col[i]][col[j]] = tmp[i][j] % mod + (tmp[i][j] < 0) * mod;
  return n;
}
vector<pair<int, int>> generalMatching(int N, vector<pair<int, int>>& ed) {
  vector<vector<int64_t>> mat(N, vector<int64_t>(N)), A;
  for (pair<int, int> pa : ed) {
    int a = pa.first, b = pa.second, r = rand() % mod;
    mat[a][b] = r, mat[b][a] = (mod - r) % mod;
  }
  int r = matInv(A = mat), M = 2 * N - r, fi, fj;
  assert(r % 2 == 0);
  if (M != N) do {
      mat.resize(M, vector<int64_t>(M));
      for (int i = 0; i < (N); i++) {
        mat[i].resize(M);
        for (int j = N; j < (M); j++) {
          int r = rand() % mod;
          mat[i][j] = r, mat[j][i] = (mod - r) % mod;
        }
      }
    } while (matInv(A = mat) != M);
  vector<int> has(M, 1);
  vector<pair<int, int>> ret;
  for (int it = 0; it < (M / 2); it++) {
    for (int i = 0; i < (M); i++)
      if (has[i])
        for (int j = i + 1; j < (M); j++)
          if (A[i][j] && mat[i][j]) {
            fi = i;
            fj = j;
            goto done;
          }
    assert(0);
  done:
    if (fj < N) ret.emplace_back(fi, fj);
    has[fi] = has[fj] = 0;
    for (int sw = 0; sw < (2); sw++) {
      int64_t a = modpow(A[fi][fj], mod - 2);
      for (int i = 0; i < (M); i++)
        if (has[i] && A[i][fj]) {
          int64_t b = A[i][fj] * a % mod;
          for (int j = 0; j < (M); j++) A[i][j] = (A[i][j] - A[fi][j] * b) % mod;
        }
      swap(fi, fj);
    }
  }
  return ret;
}

/**
 * Author: chilli
 * License: CC0
 * Description: z[i] computes the length of the longest
 * common prefix of s[i:] and s, except z[0] = 0. (abacaba
 * -> 0010301) Time: O(n) Status: stress-tested
 */
vector<int> Z(const string& S) {
  vector<int> z((int)(S).size());
  int l = -1, r = -1;
  for (int i = 1; i < ((int)(S).size()); i++) {
    z[i] = i >= r ? 0 : min(r - i, z[i - l]);
    while (
      i + z[i] < (int)(S).size() && S[i + z[i]] == S[z[i]])
      z[i]++;
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}

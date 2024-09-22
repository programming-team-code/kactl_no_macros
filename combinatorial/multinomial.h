/**
 * Author: Mattias de Zalenski, Fredrik Niemelä, Per
 * Austrin, Simon Lindholm Date: 2002-09-26 Source: Max
 * Bennedich Description: Computes $\displaystyle
 * \binom{k_1 + \dots + k_n}{k_1, k_2, \dots, k_n} =
 * \frac{(\sum k_i)!}{k_1!k_2!...k_n!}$. Status: Tested on
 * kattis:lexicography
 */
int64_t multinomial(vector<int>& v) {
  int64_t c = 1, m = v.empty() ? 1 : v[0];
  for (int i = 1; i < ((int)(v).size()); i++)
    for (int j = 0; j < (v[i]); j++) c = c * ++m / (j + 1);
  return c;
}

/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * Description: Pre-computation of modular inverses.
 * Assumes LIM $\le$ mod and that mod is a prime. Status:
 * Works
 */
// const ll mod = 1000000007, LIM = 200000; ///include-line
int64_t* inv = new int64_t[LIM] - 1;
inv[1] = 1;
for (int i = 2; i < (LIM); i++)
  inv[i] = mod - (mod / i) * inv[mod % i] % mod;

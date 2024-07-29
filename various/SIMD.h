/**
 * Author: Simon Lindholm
 * Date: 2015-03-18
 * License: CC0
 * Source: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
 * Description: Cheat sheet of SSE/AVX intrinsics, for doing arithmetic on several numbers at once.
 * Can provide a constant factor improvement of about 4, orthogonal to loop unrolling.
 * Operations follow the pattern \texttt{"\_mm(256)?\_name\_(si(128|256)|epi(8|16|32|64)|pd|ps)"}. Not all are described here;
 * grep for \texttt{\_mm\_} in \texttt{/usr/lib/gcc/{*}/4.9/include/} for more.
 * If AVX is unsupported, try 128-bit operations, "emmintrin.h" and \#define \texttt{\_\_SSE\_\_} and \texttt{\_\_MMX\_\_} before including it.
 * For aligned memory use \texttt{\_mm\_malloc(size, 32)} or \texttt{int buf[N] alignas(32)}, but prefer loadu/storeu.
 */
#pragma GCC target("avx2")  // or sse4.1

the following errors occurred when running [remove_macros.sh](remove_macros.sh) (so the resulting files might not have been converted correctly):

```
./kactl/content/data-structures/HashMap.h:12:45: error: no include path in which to search for bits/extc++.h
   12 | #include <bits/extc++.h> /** keep-include */

./kactl/content/data-structures/OrderStatisticTree.h:13:45: error: no include path in which to search for bits/extc++.h
   13 | #include <bits/extc++.h> /** keep-include */

./kactl/content/strings/Hashing-codeforces.h:57:22: error: no include path in which to search for sys/time.h
   57 | #include <sys/time.h>

./kactl/content/various/SIMD.h:16:10: fatal error: immintrin.h: No such file or directory
   16 | #include "immintrin.h" /** keep-include */
```

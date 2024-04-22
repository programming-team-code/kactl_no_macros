/**
 * Author: Simon Lindholm
 * Date: 2015-03-19
 * License: CC0
 * Source: me
 * Description:
 */
int i = from;
while (i & 3 && i < to) {
  ...;
  ++i;
}  // for alignment, if needed
while (i + 4 <= to) {
  {
    ...;
    ++i;
  }
  {
    ...;
    ++i;
  }
  {
    ...;
    ++i;
  }
  {
    ...;
    ++i;
  }
}
while (i < to) {
  ...;
  ++i;
}

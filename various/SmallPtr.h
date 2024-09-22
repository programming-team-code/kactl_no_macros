/**
 * Author: Simon Lindholm
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: A 32-bit pointer that points into
 * BumpAllocator memory. Status: tested
 */
/**
 * Author: Simon Lindholm
 * Date: 2015-09-12
 * License: CC0
 * Source: me
 * Description: When you need to dynamically allocate many
 * objects and don't care about freeing them. "new X"
 * otherwise has an overhead of something like 0.05us + 16
 * bytes per allocation. Status: tested
 */
// Either globally or in a single class:
static char buf[450 << 20];
void* operator new(size_t s) {
  static size_t i = sizeof buf;
  assert(s < i);
  return (void*)&buf[i -= s];
}
void operator delete(void*) {}
template<class T> struct ptr {
  unsigned ind;
  ptr(T* p = 0): ind(p ? unsigned((char*)p - buf) : 0) {
    assert(ind < sizeof buf);
  }
  T& operator*() const { return *(T*)(buf + ind); }
  T* operator->() const { return &**this; }
  T& operator[](int a) const { return (&**this)[a]; }
  explicit operator bool() const { return ind; }
};

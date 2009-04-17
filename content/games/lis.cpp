/* KTH ACM Contest Template Library
 *
 * Graph/Longest path/Longest Increasing Subsequence
 *
 * Credit:
 *   By Per Austrin
 */

template <class It> // change this function if necessary
inline bool it_less(It i, It j) { return *i < *j; }

// NB! output cannot overlap input!
template <class It, class OutIt>
OutIt lis(It begin, It end, OutIt res) {
  int n = end - begin, i = 0;
  It idxs[n], back[n], *idxend = idxs;
  for (It it = begin; it != end; ++it, ++i) {
    // upper_bound if non-decreasing rather than increasing.
    It *b = lower_bound(idxs, idxend, *it, it_less);
    if (b == idxend) ++idxend;
    *b = it;
    back[i] = (b == idxs) ? end : *--b;
  } // length is idxend - idxs
  It it = idxend[-1]; OIt ans = res += idxend - idxs;
  while (it != end) *--ans = *it, it = back[it-begin];
  return res;
}

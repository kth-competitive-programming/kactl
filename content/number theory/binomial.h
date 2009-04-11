/**
 * Author:
 * Date:
 * Source: tinyKACTL
 * Description:
 */
#pragma once

template<class T>
T choose(int n, int k) {
  k >?= n-k;

  T c = 1;
  for(int i = 1; i <= n-k; ++i)
    c *= k+i, c /= i;

  return c;
}

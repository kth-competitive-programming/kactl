/**
 * Author: Per Austrin
 * Date: 2003-09-23
 * License: CC0
 * Description: Permutations to/from integers. The bijection is order preserving.
 * Time: O(n^2)
 */
#pragma once

int factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040}; // etc.
template <class Z, class It> 
void perm_to_int(Z& val, It begin, It end) { 
	int x = 0, n = 0; 
	for (It i = begin; i != end; ++i, ++n) 
		if (*i < *begin) ++x; 
	if (n > 2) perm_to_int<Z>(val, ++begin, end); 
	else val = 0;
	val += factorial[n-1]*x; 
} 
/* range [begin, end) does not have to be sorted. */ 
template <class Z, class It> 
void int_to_perm(Z val, It begin, It end) {
	Z fac = factorial[end - begin - 1]; 
	// Note that the division result will fit in an integer!
	int x = val / fac; 
	nth_element(begin, begin + x, end); 
	swap(*begin, *(begin + x));
	if (end - begin > 2) int_to_perm(val % fac, ++begin, end);
}

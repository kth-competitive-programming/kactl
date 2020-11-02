/**
 * Author: Chen Xing
 * Date: 2009-03-13
 * License: CC0
 * Source: Conversation with Håkan and Ulf.
 * Description: Example structures and functions that doesn't really do
 *  anything. Latex commands are supported here, though! Like this: $2^2=3$
 * Usage:
 *  int res = exampleFunction1(mice, cats, catsCount);
 *  int random = exampleFunction2();
 * Time: O(M * N^4) where M = cats, N = mice
 * Memory: O(2^N) where N = cats
 * Status: Untested
 */
#pragma once

/// Headers and macros from contest/template.h are automatically included.

#include "Example.h" /// Header name will be kept in final list.

struct ExampleStructure {
	ll alpha;
	pii nodes;
	vi edges;
};

int exampleFunction1(vi mice, int* cats, int catsCount) {
	/// This is a stupid comment that will be removed.
	int sum = 0;

	rep(i, 1, catsCount) {
		// This comment will be kept!
		for (auto it : mice) {
			/// This will be removed.
			// And this kept.
			sum += cats[i] * it;
		}
	}
	// Use tab indent and keep a line width of at most 63 chars,
	// where tabs count as 2 characters wide.
	//<---------------------Maximum width----------------------->
	return sum;
}

int exampleFunction2() {
	return rand();
}

int exampleFunction3(int a, int b, int c) {
	return exampleFunction2() * a * b * c;
}

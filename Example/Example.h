/**
Provides: ExampleStructure1, ExampleStructure2, exampleFunction1,
	exampleFunction2, exampleFunction3
Author: Chen Xing
Date: 2009-03-13
Source: Conversation with Håkan and Ulf.
Description: Example structures and functions that doesn't really do
	anything. Latex commands are supported here, though! Like this: $2^2=3$
Time: O(M * N^4) where M = cats, N = mice
Memory: O(2^N) where N = cats
Status: Unknown
Changes:
	2009-03-21 - Minor modifications by Ulf.
*/
#pragma once

#include <iostream> /// Header name will be removed from final list...
#include "Global.h" /// ...since it exists in Global.h
#include "Example.h" /// Header name will be kept in final list.

class ExampleStructure1
{
	ll alpha;
	pii nodes;
	vi edges;
};

class ExampleStructure2
{
	int a;
	int b;
	int c;
};

int exampleFunction1(vi mice, int* cats, int catsCount) {
	/// This is a stupid comment that will be removed.
	int sum = 0;

	rep(i, 1, catsCount) {
		// This comment will be kept!
		trav(it, mice) {
			/// This will be removed.
			// And this kept.
			sum += cats[i] * (*it);
		}
	}
	//Use tab indent and keep the lines shorter than 64 characters
	//where tabs are 2 characters wide.
	//<----------------------Maximum width----------------------->
	return sum;
}

int exampleFunction2() {
	return rand();
}

int exampleFunction3(int a, int b, int c) {
	return exampleFunction2() * a * b * c;
}

// This file should be included in all test files
// as it contains the same inclusions and definitions
// as the contest template file.
#pragma once

#ifdef __INTEL_COMPILER
#	define typeof(x) auto
#endif

#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <bitset>
#include <algorithm>
using namespace std;

#define rep(i, a, b) for(int i = (a); i < int(b); ++i)
#define trav(it, v) for(__typeof((v).begin()) it = (v).begin(); \
                        it != (v).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

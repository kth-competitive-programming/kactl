/**
 * Author: FHVirus
 * Date: 2023-08-06
 * License: CC0
 * Source: modified from ZCKevin's Code
 * Description: Debug tool.
 */
#pragma once
#ifdef NONTOI
#define debug(args...) LKJ("\033[1;32m["#args"]\033[0m", args)
template<class I> void LKJ(I&&x){ cerr << x << endl; }
template<class I, class...T> void LKJ(I&&x, T&&...t)
{ cerr << x << ", ", LKJ(t...); }
template<class I> void print(I a, I b)
{ while(a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) ((void)0)
#define print(...) ((void)0)
#endif

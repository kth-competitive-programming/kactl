/**
 * Author: Håkan Terelius
 * Date: 2009-02-08
 * Source: tinyKACTL
 *	Concrete Mathematics, Chapter 1.3
 * Description: $n$ people numberd 1..$n$ are standing in a circle
 *  and we eliminate every $k$:th person until there is only one left.
 *  The problem is to find who survives, i.e. the index of that person.
 * 
 *  josephus2 solves this problem when $k=2$.
 *  The next[] array in the simulation has to be as large as $n$.
 * Time: O(k \log n), O(\log n), O(k*n)
 */
#pragma once

int josephus(int n, int k) {
  int d=1;
  while(d<=(k-1)*n) d=(k*d+k-2)/(k-1);
  return k*n+1-d;
}

int josephus2(int n) {
  int d=1;
  while(d<<1<=n) d<<=1;
  return 2*(n&~d)+1;
}

int josephus_simulation(int n, int k) {
	int next[10000], current = 0;
	for(int i=0;i<n;++i) next[i]=(i+1)%n;
	while(n>1) {
		const int steps = (k-2)%(n--);
		for(int i=0;i<steps;++i) current=next[current];
		current = next[current] = next[next[current]];
	}
	return current+1;
}

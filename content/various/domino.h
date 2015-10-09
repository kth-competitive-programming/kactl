/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * Source: http://www.math.uni-bielefeld.de/~sillke/PUZZLES/domino
 * Description: The number of ways to tile
 * an $M \times N$ rectangle with $1 \times 2$ dominos is $2^{M \cdot N/2}$ times the product of
 * $\left( \cos^2\left(\frac{m\pi}{M+1}\right) + \cos^2\left(\frac{n\pi}{N+1}\right) \right) ^ {1/4}$
 * over all $m$,$n$ in the range $0<m<M+1$, $0<n<N+1$.
 * 
 * Time: O(N \cdot M)
 */
#pragma once
#include <cmath>

ll dominoTiling(int N, int M) {
	if(N==0 || M==0) return 1;
	if((N%2 && M%2) || N==0 || M==0) return 0;
	double prod=1;
	for(int m=1;m<=M;m++)
		for(int n=1;n<=N;n++)
			prod*=pow(cos((m*M_PI)/(M+1))*cos((m*M_PI)/(M+1))+
				cos((n*M_PI)/(N+1))*cos((n*M_PI)/(N+1)),0.25);
	return (ll)round(double(1LL<<((M*N)/2))*prod);
}

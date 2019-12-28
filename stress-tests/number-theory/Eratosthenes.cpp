#include "../utilities/template.h"

struct prime_sieve {
	typedef unsigned char uchar;
	typedef unsigned int uint;
	static const int pregen = 3*5*7*11*13;
	uint n, sqrtn;
	uchar *isprime;
	int *prime, primes; // prime[i] is i:th prime

	bool is_prime(int n) { // primality check
		if(n%2==0 || n<=2) return n==2;
		return isprime[(n-3)>>4] & 1 << ((n-3) >> 1&7);
	}

	prime_sieve(int _n) : n(_n), sqrtn((int)ceil(sqrt(1.0*n))) {
		int n0 = max(n>>4, (uint)pregen) + 1;
		prime = new int[max(2775, (int)(1.12*n/log(1.0*n)))];
		prime[0]=2; prime[1]=3; prime[2]=5;
		prime[3]=7; prime[4]=11; prime[5]=13;
		primes=6;
		isprime = new uchar[n0];
		memset(isprime, 255, n0);

		for(int j=1,p=prime[j];j<6;p=prime[++j])
			for(int i=(p*p-3)>>4,s=(p*p-3)>>1&7;
				i<=pregen; i+= (s+=p)>>3, s&=7)
					isprime[i] &= (uchar)~(1<<s);
		for(int d=pregen, b=pregen+1; b<n0; b+=d,d<<=1)
			memcpy(isprime+b,isprime+1,(n0<b+d)?n0-b:d);
		for(uint p=17,i=0,s=7; p<n; p+=2, i+= ++s>>3, s&=7)
			if(isprime[i]&1<<s) {
				prime[primes++] = p;
				if(p<sqrtn) {
					int ii=i, ss=s+(p-1)*p/2;
					for(uint pp=p*p; pp<n; pp+=p<<1, ss+=p) {
						ii += ss>>3;
						ss &=7;
						isprime[ii] &= (uchar)~(1<<ss);
}	}		}	}	};


#include "../../content/number-theory/eratosthenes.h"

int main(int argc, char** argv) {
	ll s = 0, s2 = 0;
	prime_sieve ps(MAX_PR);
	rep(i,0,ps.primes) s += ps.prime[i];
	vi r = eratosthenes_sieve(MAX_PR);
	trav(x, r) s2 += x;
	cout << s << ' ' << s2 << endl;
	assert(s==s2);
	cout<<"Tests passed!"<<endl;
}

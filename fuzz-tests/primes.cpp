#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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

const int MAX_PR = 100000000;

#if 1

bitset<MAX_PR/2> isprime;
vi eratosthenes_sieve(int lim) {
	isprime.set();
	for (int i = 3; i*i < lim; i += 2) if (isprime[i >> 1])
		for (int j = i*i; j < lim; j += 2*i) isprime[j >> 1] = 0;
	vi pr;
	if (lim >= 2) pr.push_back(2);
	for (int i = 3; i < lim; i += 2)
		if (isprime[i>>1]) pr.push_back(i);
	return pr;
}

#else

bitset<MAX_PR> isprime;
vi eratosthenes_sieve(int lim) {
	isprime.set(); isprime[0] = isprime[1] = 0;
	for (int i = 4; i < lim; i += 2) isprime[i] = 0;
	for (int i = 3; i*i < lim; i += 2) if (isprime[i])
		for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
	vi pr;
	rep(i,2,lim) if (isprime[i]) pr.push_back(i);
	return pr;
}

#endif

int main(int argc, char** argv) {
	ll s = 0, s2 = 0;
	prime_sieve ps(MAX_PR);
	rep(i,0,ps.primes) s += ps.prime[i];
	vi r = eratosthenes_sieve(MAX_PR);
	trav(x, r) s2 += x;
	cout << s << ' ' << s2 << endl;
}

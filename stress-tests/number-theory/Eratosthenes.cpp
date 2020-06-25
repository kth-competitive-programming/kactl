#include "../utilities/template.h"

vi prime_sieve(int _n)  {
	vi pr;
	vector<char> sieve(_n);
	for (int i=2; i<_n; i++) {
		if (sieve[i]) continue;
		// cout<<i<<endl;
		pr.push_back(i);
		for (int j= i; j<_n; j+=i)
			sieve[j] = true;
	}
	return pr;
}


namespace dynamic {
vi eratosthenes(int LIM) {
	const int S = round(sqrt(LIM)), R = LIM / 2;
	vi pr({2}), sieve(S + 1); pr.reserve(LIM / (int)log(LIM));
	vector<array<int, 2>> cp;
	for (int i = 3; i <= S; i += 2) if (!sieve[i]) {
		cp.push_back({i, i * i / 2});
		for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
	}
	for (int L = 1; L <= R; L += S) {
		vector<bool> block(S);
		// array<bool, S> block{};
		for (auto &[p, idx] : cp)
			for (int i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
		rep(i,0,min(S, R - L))
			if (!block[i]) pr.push_back((L + i) * 2 + 1);
	}
	return pr;
}
}
#include "../../content/number-theory/FastEratosthenes.h"


int main() {
	vi pr1 = prime_sieve(LIM);
	vi pr2 = eratosthenes();
	assert(pr1 == pr2);

	for (int lim=121; lim<1000; lim++) {
		vi pr = prime_sieve(lim);
		vi r = dynamic::eratosthenes(lim);
		assert(pr == r);
	}
	cout<<"Tests passed!"<<endl;
}

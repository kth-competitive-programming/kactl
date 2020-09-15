#include "../utilities/template.h"

namespace dynamic {
vi eratosthenes(int LIM) {
	const int S = (int)round(sqrt(LIM)), R = LIM / 2;
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
#include "../../content/number-theory/Eratosthenes.h"


int main() {
	vi pr1 = eratosthenesSieve(LIM);
	vi pr2 = eratosthenes();
	assert(pr1 == pr2);

	for (int lim=121; lim<1000; lim++) {
		vi pr = eratosthenesSieve(lim);
		vi r = dynamic::eratosthenes(lim);
		assert(pr == r);
	}
	cout<<"Tests passed!"<<endl;
}

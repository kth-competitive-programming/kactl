#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/various/CoordCompression.h"

int main() {
	rep(it,0,20000) {
		int n = randRange(0, 30);
		vi values(n);
		rep(i,0,n) values[i] = randRange(-10, 10);

		Compressor<int> comp(values);
		set<int> distinct(all(values));
		assert(comp.size() == sz(distinct));
		assert(comp.sorted == vi(all(distinct)));

		rep(i,0,n) {
			int rank = comp.rank(values[i]);
			assert(0 <= rank && rank < comp.size());
			assert(comp.sorted[rank] == values[i]);
		}
		// ranks must order exactly the way the values do
		rep(i,0,n) rep(j,0,n) {
			int a = comp.rank(values[i]), b = comp.rank(values[j]);
			assert((values[i] < values[j]) == (a < b));
			assert((values[i] == values[j]) == (a == b));
		}
		// an absent value takes the rank of the next larger one
		rep(value,-12,12) {
			int rank = comp.rank(value);
			assert(rank == comp.size() || comp.sorted[rank] >= value);
			assert(rank == 0 || comp.sorted[rank-1] < value);
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}

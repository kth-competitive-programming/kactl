#include "../utilities/template.h"
#include <valarray>

#include "../../content/numerical/FastFourierTransform.h"

const double eps = 1e-8;
int main() {
	int n = 8;
	vector<C> a(n);
	rep(i,0,n) a[i] = C(rand() % 10 - 5, rand() % 10 - 5);
	auto aorig = a;
	fft(a);
	rep(k,0,n) {
		C sum{};
		rep(x,0,n) {
			sum += aorig[x] * polar(1.0, 2 * M_PI * k * x / n);
		}
		assert(norm(sum - a[k]) < 1e-6);
	}

	vd A(4), B(6);
	for(auto &x: A) x = rand() / (RAND_MAX + 1.0) * 10 - 5;
	for(auto &x: B) x = rand() / (RAND_MAX + 1.0) * 10 - 5;
	vd C = conv(A, B);
	rep(i,0,sz(A) + sz(B) - 1) {
		double sum = 0;
		rep(j,0,sz(A)) if (i - j >= 0 && i - j < sz(B)) {
			sum += A[j] * B[i - j];
		}
		assert(abs(sum - C[i]) < eps);
	}
	cout<<"Tests passed!"<<endl;
}

#include "../UnitTest.h"
#include "../../content/numerical/tridiagonal.h"
#include "../../content/data-structures/Matrix.h"
#include <fstream>
#include <sstream>

class test_tridiagonal :
	public UnitTest
{
public:
	test_tridiagonal() : UnitTest("test_tridiagonal") { }

	virtual ~test_tridiagonal() { }

	virtual void run(int subcase) {
		int n = subcase+1;
		vector<double> diag(n), sup(n-1), sub(n-1), b(n);
		Matrix<double> M(n,n,0), X(n,1,0);
		rep(i,0,n) {
			diag[i] = rand()%100;
			M(i,i) = diag[i];
			X(i,0) = rand()%100;
		}
		rep(i,0,n-1) {
			sup[i] = rand()%100;
			sub[i] = rand()%100;
			M(i,i+1) = sup[i];
			M(i+1,i) = sub[i];
		}
		Matrix<double> B = M*X;
		rep(i,0,n) b[i] = B(i,0);
		vector<double> x = tridiagonal(diag,sup,sub,b);
		rep(i,0,n) {
			if (abs(x[i] - X(i,0)) > 1e-10) {
				stringstream ss;
				ss << "M=" << M << "X=" << X << "B=" << B << "\nx=";
				rep(i,0,n) ss << x[i] << " ";
				ss << endl;
				fail(ss.str());
			}
		}
	}

	virtual int getCount() const {
		return 10;
	}
};

KACTL_AUTOREGISTER_TEST(test_tridiagonal);

#include "../UnitTest.h"
#include "../../content/number-theory/factor.h"
#include <algorithm>

class test_factor :
	public UnitTest
{
public:
	test_factor():
		UnitTest("test_factor")
	{
		init(54);
		num.push_back(1053189095765561);
		add(32452867, 32452883);

		num.push_back(1053191627091371);
		add(32452909, 32452919);

		num.push_back(1053203310172787);
		add(32453087, 32453101);

		num.push_back(2497960516119197);
		add(49979599, 49979603);

		num.push_back(9999977800010557);
		add(99999847, 99999931);

		num.push_back(9999990000002419);
		add(99999941, 99999959);

		num.push_back(9999996000000319);
		add(99999971, 99999989);

		num.push_back(143899958269);
		add(1439, 99999971);
	}

	virtual ~test_factor()
	{
	}

public:
	void add(ull a, ull b)
	{
		vector<ull> f(1, a);
		f.push_back(b);
		factors.push_back(f);
	}
	virtual void run(int subcase)
	{
		if (subcase < (int)num.size())
		{
			vector<ull> f = factor(num[subcase]);
			sort(f.begin(), f.end());
			check(f, factors[subcase]);
		}
	}

	virtual int getCount() const
	{
		return num.size();
	}

private:
	vector<ull> num;
	vector<vector<ull> > factors;
};

KACTL_AUTOREGISTER_TEST(test_factor);

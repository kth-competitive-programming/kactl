#include "../UnitTest.h"

class test_knuthMorrisPratt :
	public UnitTest
{
public:
	test_knuthMorrisPratt():
		UnitTest("test_knuthMorrisPratt")
	{
	}

	virtual ~test_knuthMorrisPratt()
	{
	}

public:
	virtual void run(int subcase)
	{
	}

	virtual int getCount() const
	{
		return 10;
	}
};

KACTL_AUTOREGISTER_TEST(test_knuthMorrisPratt);

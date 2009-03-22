#include "../UnitTest.h"

class test_lineDist :
	public UnitTest
{
public:
	test_lineDist():
		UnitTest("test_lineDist")
	{
	}

	virtual ~test_lineDist()
	{
	}

public:
	virtual void run(int subcase)
	{
	}

	virtual int getCount() const
	{
		return 1;
	}
};

KACTL_AUTOREGISTER_TEST(test_lineDist);

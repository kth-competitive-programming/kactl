#include "../UnitTest.h"
#include "../../content/strings/suffixArray.h"
#include <fstream>
#include <sstream>

class test_SA :
	public UnitTest
{
public:
	test_SA():
		UnitTest("test_SuffixArray")
	{
		ifstream in("SA.in");
		ifstream out("SA.out");

		int m;
		in >> m;
		inputString.resize(m);
		outputArray.resize(m);

		rep(i,0,m)
			in >> inputString[i];

		rep(i,0,m)
		{
			outputArray[i] = vector<ll>(inputString[i].size()+1);
			rep(j,0,inputString[i].size()+1)
				out >> outputArray[i][j];
		}
	}

	virtual ~test_SA()
	{
	}

public:
	virtual void run(int subcase)
	{
		if(subcase < (int)inputString.size())
		{
			vector<ll> have = SuffixArray(inputString[subcase]).a;
			check(have, outputArray[subcase]);
		}
	}

	virtual int getCount() const
	{
		return inputString.size();
	}

private:
	vector<string> inputString;
	vector<vector<ll> > outputArray;
};

KACTL_AUTOREGISTER_TEST(test_SA);

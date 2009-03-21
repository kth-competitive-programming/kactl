#pragma once

#include "../Global.h"
#include "UnitTestManager.h"

class UnitTestFailed
{
};

class UnitTest
{
public:
	UnitTest(const string& testName):
	  m_name(testName)
	{
		UnitTestManager::getInstance()->registerTest(this);
	}

	virtual ~UnitTest()
	{
	}

public:
	virtual bool run(int subcase) = 0;

	virtual bool getCount() const
	{
		return 1;
	}

protected:
	template<class T>
	void check(const T& have, const T& want, const string& message = "")
	{
		if(have == want)
			return;

		UnitTestManager* unitTestManager = UnitTestManager::getInstance();
		ostringstream haveStream;
		ostringstream wantStream;

		haveStream << have;
		wantStream << want;

		unitTestManager->reportCheckFailure(have, want, message);

		throw UnitTestFailed();
	}

	void fail(const string& message)
	{
		UnitTestManager* unitTestManager = UnitTestManager::getInstance();
		
		unitTestManager->reportFailure(message);

		throw UnitTestFailed();
	}

public:
	string getName()
	{
		return m_name;
	}

protected:
	string m_name;
};

#ifdef KACTL_UNIT_TEST_STANDALONE
#	include "UnitTestManager.cpp"
#endif

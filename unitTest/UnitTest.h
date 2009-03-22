#pragma once

#include "../global.h"
#include "UnitTestManager.h"

#define KACTL_AUTOREGISTER_TEST(x) x* g__KACTL__temp__##x = new x()

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
	virtual void run(int subcase) = 0;

	virtual int getCount() const
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

		unitTestManager->reportCheckFailure(haveStream.str(), wantStream.str(), message);

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

#ifndef KACTL_UNITTEST_BATCH
#	include "UnitTestManager.cpp"
#endif

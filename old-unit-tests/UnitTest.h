#pragma once

#include "global.h"
#include "UnitTestManager.h"
#include <sstream>

class UnitTestFailed
{
};

class UnitTest
{
public:
	UnitTest(const string& testName):
		m_name(testName)
	{
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

		unitTestManager->reportCheckFailure(convertToString(have), convertToString(want), message);

		throw UnitTestFailed();
	}

	void fail(const string& message)
	{
		UnitTestManager* unitTestManager = UnitTestManager::getInstance();

		unitTestManager->reportFailure(message);

		throw UnitTestFailed();
	}

private:
	template<class T>
	string convertToString(const T& data)
	{
		ostringstream oss;

		oss.precision(20);
		oss << data;

		return oss.str();
	}

	template<class T>
	string convertToString(const vector<T>& data)
	{
		ostringstream oss;

		oss << "{ ";
		for(auto &it: data)
			oss << convertToString(it) << " ";
		oss << "}";

		return oss.str();
	}

public:
	string getName()
	{
		return m_name;
	}

protected:
	string m_name;
};

#define KACTL_AUTOREGISTER_TEST(x) UnitTestWrapper* g__KACTL__temp__##x = new UnitTestWrapper(new x())
#include "UnitTestWrapper.h"

#ifndef KACTL_UNITTEST_BATCH
#	include "UnitTestManager.cpp"
#endif

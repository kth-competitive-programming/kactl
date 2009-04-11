#pragma once

#include "global.h"
#include "UnitTest.h"
#include "UnitTestManager.h"

class UnitTestWrapper
{
public:
	UnitTestWrapper(UnitTest* unitTest):
		m_unitTest(unitTest)
	{
		UnitTestManager::getInstance()->registerWrapper(this);
	}

	~UnitTestWrapper()
	{
		if(m_unitTest != NULL)
			delete m_unitTest;
	}

public:
	UnitTest* getUnitTest()
	{
		return m_unitTest;
	}

private:
	UnitTest* m_unitTest;
};

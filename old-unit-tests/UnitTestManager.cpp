#include "global.h"
#include "UnitTestManager.h"
#include "UnitTest.h"
#include "UnitTestWrapper.h"
#include <cstdio>

//#include <direct.h>

UnitTestManager::UnitTestManager():
	m_successCount(0),
	m_failureCount(0)
{
}

UnitTestManager::~UnitTestManager()
{
	for(auto &it: m_unitTestWrappers)
		delete it.second;

	m_unitTestWrappers.clear();
}

UnitTestManager* UnitTestManager::getInstance()
{
	static UnitTestManager s_unitTestManager;

	return &s_unitTestManager;
}

void UnitTestManager::reportCheckFailure(const string& have,
										 const string& want,
										 const string& message)
{
	fprintf(stderr, "FAILED\n");
	fprintf(stderr, "\tWanted:   \"%s\"\n", want.c_str());
	fprintf(stderr, "\tReturned: \"%s\"\n", have.c_str());
	if(!message.empty())
		fprintf(stderr, "\tMessage: %s\n", message.c_str());
	fflush(stderr);
}


void UnitTestManager::reportFailure(const string& message)
{
	fprintf(stderr, "FAILED\n");
	if(!message.empty())
		fprintf(stderr, "\tMessage: %s\n", message.c_str());
	fflush(stderr);
}

void UnitTestManager::registerWrapper(UnitTestWrapper* unitTestWrapper)
{
	if(unitTestWrapper == NULL || unitTestWrapper->getUnitTest() == NULL)
		return;

	m_unitTestWrappers.insert(make_pair(unitTestWrapper->getUnitTest()->getName(), unitTestWrapper));
}

void UnitTestManager::runAll()
{
	for(auto &it: m_unitTestWrappers)
		runTest(it.second);
}

void UnitTestManager::runTest(const string& name)
{
	map<string, UnitTestWrapper*>::iterator it = m_unitTestWrappers.find(name);

	if(it == m_unitTestWrappers.end())
	{
		fprintf(stderr, "ERROR: Couldn't find test \"%s\"!", name.c_str());
		fflush(stderr);
		return;
	}

	runTest(it->second);
}

void
UnitTestManager::printStatistics() const
{
	fprintf(stderr, "\nStatistics:\n");
	fprintf(stderr, "\tSuccesses: %d\n", m_successCount);
	fprintf(stderr, "\tFailures:  %d\n", m_failureCount);
	fprintf(stderr, "\tTotal:     %d\n", m_successCount + m_failureCount);
	fflush(stderr);
}

void UnitTestManager::runTest(UnitTestWrapper* unitTestWrapper)
{
	UnitTest* unitTest = unitTestWrapper->getUnitTest();
	int count = unitTest->getCount();
	string name = unitTest->getName();

	rep(i, 0, count)
	{
		fprintf(stderr, "Running test \"%s\" <%d, %d>... ",
			name.c_str(), i, unitTest->getCount());
		fflush(stderr);

		try
		{
			unitTest->run(i);

			m_successCount++;
			fprintf(stderr, "OK\n");
			fflush(stderr);
		}
		catch(const UnitTestFailed&)
		{
			m_failureCount++;
		}
		catch(const exception& e)
		{
			m_failureCount++;
			fprintf(stderr, "FAILED\n");
			fprintf(stderr, "\tException: %s\n", e.what());
			fflush(stderr);
		}
		catch(...)
		{
			m_failureCount++;
			fprintf(stderr, "FAILED\n");
			fprintf(stderr, "\tUnknown exception caught!\n");
			fflush(stderr);
		}
	}
}

int main(int argc, char** argv)
{
	if(argc >= 2)
	{
		rep(i, 1, argc)
			UnitTestManager::getInstance()->runTest(argv[i]);
	}
	else
	{
		UnitTestManager::getInstance()->runAll();
	}

	UnitTestManager::getInstance()->printStatistics();

	return 0;
}

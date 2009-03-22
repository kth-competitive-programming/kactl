#include "../Global.h"
#include "UnitTestManager.h"
#include "UnitTest.h"

UnitTestManager::UnitTestManager()
{

}

UnitTestManager::~UnitTestManager()
{
	trav(it, m_unitTests)
		delete (it->second);

	m_unitTests.clear();
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
}


void UnitTestManager::reportFailure(const string& message)
{
	fprintf(stderr, "FAILED\n");
	if(!message.empty())
		fprintf(stderr, "\tMessage: %s\n", message.c_str());
}

void UnitTestManager::registerTest(UnitTest* unitTest)
{
	if(unitTest == NULL)
		return;

	m_unitTests.insert(make_pair(unitTest->getName(), unitTest));
}

void UnitTestManager::runAll()
{
	trav(it, m_unitTests)
		runTest(it->second);
}

void UnitTestManager::runTest(const string& name)
{
	map<string, UnitTest*>::iterator it = m_unitTests.find(name);

	if(it == m_unitTests.end())
	{
		fprintf(stderr, "ERROR: Couldn't find test \"%s\"!", name.c_str());
		return;
	}

	runTest(it->second);
}

void UnitTestManager::runTest(UnitTest* unitTest)
{
	int count = unitTest->getCount();
	string name = unitTest->getName();

	rep(i, 0, count)
	{
		fprintf(stderr, "Running test \"%s\" <%d, %d>... ",
			name.c_str(), i, unitTest->getCount());
		
		try
		{
			unitTest->run(i);

			fprintf(stderr, "OK\n");
		}
		catch(const UnitTestFailed&)
		{
			
		}
		catch(const exception& e)
		{
			fprintf(stderr, "FAILED\n");
			fprintf(stderr, "\tException: %s\n", e.what());
		}
		catch(...)
		{
			fprintf(stderr, "FAILED\n");
			fprintf(stderr, "\tUnknown exception caught!\n");
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

	return 0;
}

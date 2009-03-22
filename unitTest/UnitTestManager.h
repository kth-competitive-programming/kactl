#pragma once

class UnitTest;

class UnitTestManager
{
	friend class UnitTest;

private:
	UnitTestManager();
	~UnitTestManager();

public:
	// Retrieves singleton instance.
	static UnitTestManager* getInstance();

protected:
	// Reports a "check" failure.
	void reportCheckFailure(const string& have,
	                        const string& want,
	                        const string& message = "");

	// Reports a failure.
	void reportFailure(const string& message = "");

protected:
	// Registers a test.
	void registerTest(UnitTest* unitTest);

public:
	// Runs all tests.
	void runAll();

	// Runs a specific test.
	void runTest(const string& name);

private:
	// Runs a specific test.
	void runTest(UnitTest* unitTest);

private:
	// Maps test names to test objects.
	map<string, UnitTest*> m_unitTests;
};

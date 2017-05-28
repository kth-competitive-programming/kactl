#pragma once

class UnitTest;
class UnitTestWrapper;

class UnitTestManager
{
	friend class UnitTest;
	friend class UnitTestWrapper;

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
	// Registers a test wrapper.
	void registerWrapper(UnitTestWrapper* unitTestWrapper);

public:
	// Runs all tests.
	void runAll();

	// Runs a specific test.
	void runTest(const string& name);

	// Print statistics.
	void printStatistics() const;

private:
	// Runs a specific test.
	void runTest(UnitTestWrapper* unitTestWrapper);

private:
	// Maps test names to test wrapper objects.
	map<string, UnitTestWrapper*> m_unitTestWrappers;

	// Statistics.
	int m_successCount;
	int m_failureCount;
};

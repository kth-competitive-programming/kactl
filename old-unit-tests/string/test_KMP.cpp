#include "../UnitTest.h"
#include "../../string/KMP.h"
#include "../../string/KMP_findAll.h"
#include <fstream>
#include <sstream>

class test_KMP :
	public UnitTest
{
public:
	test_KMP():
		UnitTest("test_KMP")
	{
		ifstream in("KMP.in");
		ifstream out("KMP.out");

		m_ioCount = 0;

		in >> m_ioCount;
		m_inputWord.resize(m_ioCount);
		m_inputText.resize(m_ioCount);
		m_output.resize(m_ioCount);

		rep(i, 0, m_ioCount)
			in >> m_inputWord[i] >> m_inputText[i];

		rep(i, 0, m_ioCount)
		{
			int count = 0;
			out >> count;
			m_output[i].resize(count);
			rep(j, 0, count)
				out >> m_output[i][j];
		}
	}

	virtual ~test_KMP()
	{
	}

public:
	virtual void run(int subcase)
	{
		if(subcase < m_ioCount)
		{
			const string& word = m_inputWord[subcase];
			const string& text = m_inputText[subcase];
			const vector<int>& want = m_output[subcase];
			vector<int> have = KMP_findAll(KMP<char>(word.begin(), word.end()), text.begin(), text.end());

			check(have, want);
		}
	}

	virtual int getCount() const
	{
		return m_ioCount;
	}

private:
	vector<string> m_inputWord;
	vector<string> m_inputText;
	vector<vector<int> > m_output;
	int m_ioCount;
};

KACTL_AUTOREGISTER_TEST(test_KMP);

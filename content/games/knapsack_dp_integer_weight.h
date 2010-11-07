/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: N/A
 * Description: N/A
 * Status: Working
 */
#pragma once

template<typename ValueType, int MaxCapacity, int MaxObjectCount> class KnapsackIndicesSingleDpIntegerWeight {
public:
	vector<size_t> solve(int capacity, const vector<pair<int, ValueType> >& objects) {
		if(objects.empty()) return vector<size_t>();
		assert(capacity <= MaxCapacity);
		assert(objects.size() <= MaxObjectCount);
		for(int i = 0; i <= capacity; ++i) m_dpCache[i] = 0;
		memset(m_dpCacheShouldMove, 0, sizeof(unsigned int) * (((capacity + 1) * objects.size()) / 32 + 1));

		for(size_t i = 0; i < objects.size(); ++i){
			const pair<int, ValueType>& curObject = objects[i];
			const size_t shouldMovePosOffset = i * (capacity + 1);
			for(int j = capacity - curObject.first; j >= 0; --j) {
				int k = j + curObject.first;
				ValueType newValue = curObject.second + m_dpCache[j];
				if(newValue > m_dpCache[k]) {
					m_dpCache[k] = newValue;
					size_t shouldMovePos = shouldMovePosOffset + k;
					m_dpCacheShouldMove[shouldMovePos >> 5] |= (1U << (shouldMovePos & 31));
				}
			}
		}

		vector<size_t> answer;
		int capacityLeft = capacity;
		size_t putObject = objects.size();
		do {
			--putObject;
			size_t shouldMovePos = putObject * (capacity + 1) + capacityLeft;
			while(putObject > 0 && !(m_dpCacheShouldMove[shouldMovePos >> 5] & (1U << (shouldMovePos & 31)))) {
				--putObject;
				shouldMovePos -= (capacity + 1);
			}
			if(!(m_dpCacheShouldMove[shouldMovePos >> 5] & (1U << (shouldMovePos & 31)))) break;
			answer.push_back(putObject);
			capacityLeft -= objects[putObject].first;
		} while(putObject != 0);
		reverse(answer.begin(), answer.end());
		return answer;
	}

private:
	ValueType m_dpCache[MaxCapacity + 1];
	unsigned int m_dpCacheShouldMove[(MaxCapacity + 1) * MaxObjectCount / 32 + 1];
};

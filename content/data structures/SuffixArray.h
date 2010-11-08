/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: http://en.wikipedia.org/wiki/Suffix_array
 * Description: N/A
 * Memory: O(N) where N is the length of word.
 */
#pragma once

template<typename CharacterType> class SuffixArray {
private:
	class PrefixCompare {
	public:
		PrefixCompare(SuffixArray* owner, size_t lastPrefixLength, vector<size_t>* lastSuffixBucket) : owner(owner), lastPrefixLength(lastPrefixLength), lastSuffixBucket(lastSuffixBucket) {}

		/* Compare the first 2 * lastPrefixLength characters of two suffixes. Complexity O(1) */
		bool operator()(size_t first, size_t second) const {
			if(first == second) return false;
			if(lastPrefixLength == 0)
				return (owner->m_word[first] < owner->m_word[second]);
			if(first + lastPrefixLength >= owner->m_word.size())
				return (second + lastPrefixLength < owner->m_word.size());
			if(second + lastPrefixLength >= owner->m_word.size())
				return false;
			return ((*lastSuffixBucket)[first + lastPrefixLength] < (*lastSuffixBucket)[second + lastPrefixLength]);
		}

		SuffixArray* owner; // Object owner.
		size_t lastPrefixLength; // Prefix length from the last pass.
		vector<size_t>* lastSuffixBucket; // Bucket that suffix belongs to from the last pass.
	};

public:
	/* Construct suffix array from word. Complexity O(N log(N)^2) where N is the length of word. Memory O(N) where N is the length of word. */
	template<typename IteratorType>	SuffixArray(IteratorType begin, IteratorType end) {	set(begin, end); }

	/* Set word to use for suffix array. Complexity O(N log(N)^2) where N is the length of word. Memory O(N) where N is the length of word. */
	template<typename IteratorType>	void set(IteratorType begin, IteratorType end) {
		m_word.clear(); m_suffixes.clear();
		m_word.insert(m_word.end(), begin, end);
		m_suffixes.resize(m_word.size());
		for(size_t i = 0; i<m_word.size(); ++i) m_suffixes[i]=i;
		if(m_word.size() <= 1) return;
		size_t lastPrefixLength = 0, uniqueBucketCount = 1;
		vector<size_t> lastSuffixBucket, newLastSuffixBucket;
		lastSuffixBucket.resize(m_word.size(), 0);
		newLastSuffixBucket.resize(m_word.size(), 0);

		while(uniqueBucketCount < m_word.size()) {
			PrefixCompare compare(this, lastPrefixLength, &lastSuffixBucket);
			uniqueBucketCount = 0;
			for(size_t begin = 0, end = 0; begin < m_word.size(); begin = end) {
				for(end = begin + 1; end < m_word.size(); ++end)
					if(lastSuffixBucket[m_suffixes[begin]] != lastSuffixBucket[m_suffixes[end]])
						break;
				if(end > begin + 1)
					sort(m_suffixes.begin() + begin, m_suffixes.begin() + end, compare);
				while(begin < end) {
					size_t bucketFirst = begin;
					newLastSuffixBucket[m_suffixes[begin]] = uniqueBucketCount;
					for(++begin; begin < end; ++begin) {
						if(compare(m_suffixes[bucketFirst], m_suffixes[begin]) || compare(m_suffixes[begin], m_suffixes[bucketFirst]))
							break;
						newLastSuffixBucket[m_suffixes[begin]] = uniqueBucketCount;
					}
					++uniqueBucketCount;
				}
			}
			lastSuffixBucket.swap(newLastSuffixBucket);
			if(lastPrefixLength == 0) lastPrefixLength = 1;
			else lastPrefixLength <<= 1;
		}
	}

	/* Get the beginning of the i-th suffix. Complexity O(1). */
	size_t getSuffix(size_t i) const { return m_suffixes[i]; }

	vector<CharacterType> m_word; // Word to gather suffixes from.
	vector<size_t> m_suffixes; // Beginning of the i-th suffix.
};

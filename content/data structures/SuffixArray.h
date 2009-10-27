/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: http://en.wikipedia.org/wiki/Suffix_array
 * Description: N/A
 */
#pragma once

/*! \brief Suffix array.
	\author Chen Xing (chen@starworm.com)
	\date 2009-23-09
	\memory O(N) where N is the length of word.
	\see http://en.wikipedia.org/wiki/Suffix_array
	\tparam CharacterType Character type.
*/
template<typename CharacterType>
class SuffixArray
{
private:
	/*! \brief Prefix comparator.
	*/
	class PrefixCompare
	{
	public:
		/*! \brief Construct prefix comparator.
			\param[in] owner Object owner.
			\param[in] lastPrefixLength Prefix length from the last pass.
			\param[in] lastSuffixBucket Bucket that suffix belongs to from the last pass.
		*/
		PrefixCompare(SuffixArray* owner,
					  size_t lastPrefixLength,
					  vector<size_t>* lastSuffixBucket) :
			m_owner(owner),
			m_lastPrefixLength(lastPrefixLength),
			m_lastSuffixBucket(lastSuffixBucket)
		{
			
		}

	public:
		/*! \brief Compare the first 2 * \a m_lastPrefixLength characters of two suffixes.
			\complexity O(1)
			\param[in] first Beginning of the first suffix.
			\param[in] second Beginning of the second suffix.
			\return Comparison result.
			\retval false First suffix should be ordered before second suffix.
			\retval true First suffix should not be ordered before second suffix.
		*/
		bool
		operator()(size_t first,
				   size_t second) const
		{
			if(first == second)
				return false;

			if(m_lastPrefixLength == 0)
				return (m_owner->m_word[first] < m_owner->m_word[second]);

			if(first + m_lastPrefixLength >= m_owner->m_word.size())
				return (second + m_lastPrefixLength < m_owner->m_word.size());

			if(second + m_lastPrefixLength >= m_owner->m_word.size())
				return false;

			return ((*m_lastSuffixBucket)[first + m_lastPrefixLength] <
					(*m_lastSuffixBucket)[second + m_lastPrefixLength]);
		}

	public:
		SuffixArray* m_owner; //!< Object owner.
		size_t m_lastPrefixLength; //!< Prefix length from the last pass.
		vector<size_t>* m_lastSuffixBucket; //!< Bucket that suffix belongs to from the last pass.
	};

public:
	/*! \brief Construct suffix array from word.
		\complexity O(N * log(N) * log(N)) where N is the length of word.
		\memory O(N) where N is the length of word.
		\tparam Iterator Word character iterator type.
		\param[in] begin Beginning of word.
		\param[in] end End of word.
		\return Reference to \a this object.
	*/
	template<typename IteratorType>
	SuffixArray(IteratorType begin,
				IteratorType end)
	{
		set(begin, end);
	}

	/*! \brief Set word to use for suffix array.
		\complexity O(N * log(N) * log(N)) where N is the length of word.
		\memory O(N) where N is the length of word.
		\tparam Iterator Word character iterator type.
		\param[in] begin Beginning of word.
		\param[in] end End of word.
		\return Reference to \a this object.
	*/
	template<typename IteratorType>
	void
	set(IteratorType begin,
		IteratorType end)
	{
		m_word.clear();
		m_suffixes.clear();
		
		m_word.insert(m_word.end(), begin, end);
		
		m_suffixes.resize(m_word.size());
		for(size_t i = 0; i < m_word.size(); ++i)
			m_suffixes[i] = i;

		if(m_word.size() <= 1)
			return;

		size_t lastPrefixLength = 0;
		size_t uniqueBucketCount = 1;
		vector<size_t> lastSuffixBucket;
		vector<size_t> newLastSuffixBucket;

		lastSuffixBucket.resize(m_word.size(), 0);
		newLastSuffixBucket.resize(m_word.size(), 0);

		while(uniqueBucketCount < m_word.size())
		{
			PrefixCompare compare(this, lastPrefixLength, &lastSuffixBucket);

			uniqueBucketCount = 0;

			for(size_t begin = 0, end = 0; begin < m_word.size(); begin = end)
			{
				for(end = begin + 1; end < m_word.size(); ++end)
				{
					if(lastSuffixBucket[m_suffixes[begin]] != lastSuffixBucket[m_suffixes[end]])
						break;
				}

				if(end > begin + 1)
					sort(m_suffixes.begin() + begin, m_suffixes.begin() + end, compare);
				
				while(begin < end)
				{
					size_t bucketFirst = begin;
					newLastSuffixBucket[m_suffixes[begin]] = uniqueBucketCount;

					for(++begin; begin < end; ++begin)
					{
						if(compare(m_suffixes[bucketFirst], m_suffixes[begin]) || compare(m_suffixes[begin], m_suffixes[bucketFirst]))
							break;

						newLastSuffixBucket[m_suffixes[begin]] = uniqueBucketCount;
					}

					++uniqueBucketCount;
				}
			}

			lastSuffixBucket.swap(newLastSuffixBucket);

			if(lastPrefixLength == 0)
				lastPrefixLength = 1;
			else
				lastPrefixLength <<= 1;
		}
	}

	/*! \brief Get the beginning of the i-th suffix.
		\complexity O(1)
		\param[in] i Order of suffix.
		\return Beginning of the i-th suffix.
	*/
	size_t
	getSuffix(size_t i) const
	{
		return m_suffixes[i];
	}

public:
	vector<CharacterType> m_word; //!< Word to gather suffixes from.
	vector<size_t> m_suffixes; //!< Beginning of the i-th suffix.
};

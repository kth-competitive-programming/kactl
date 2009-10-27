/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: N/A
 * Description: N/A
 * Status: Working
 */
#pragma once

template<typename IteratorType>
struct DereferenceLess :
	binary_function<IteratorType, IteratorType, bool>
{
	bool
	operator()(const IteratorType& first,
			   const IteratorType& second) const
	{
		return (*first) < (*second);
	}
};

template<typename IteratorType>
struct DereferenceGreater :
	binary_function<IteratorType, IteratorType, bool>
{
	bool
	operator()(const IteratorType& first,
			   const IteratorType& second) const
	{
		return (*first) > (*second);
	}
};

/*! \brief Compute indices for the longest increasing subsequence in specified input sequence.
	\author Chen Xing (chen@starworm.com)
	\date 2009-09-24
	\complexity O(log(N) * N) where N is the length of input sequence.
	\memory O(N) where N is the length of input sequence.
	\tparam ElementType Input sequence element type.
	\tparam IteratorType Input sequence random-access iterator type.
	\param[in] begin Beginning of input sequence.
	\param[in] end End of input sequence.
	\return Indices of an earliest longest increasing subsequence.
*/
template<typename ElementType,
		 typename IteratorType>
vector<size_t> lis(IteratorType begin,
				   IteratorType end)
{
	if(begin == end)
		return vector<size_t>();

	vector<IteratorType> lowestWithLength;
	vector<IteratorType> lisPrevious;

	lisPrevious.reserve(end - begin);
	lowestWithLength.push_back(end);

	for(size_t i = 0; begin + i != end; ++i)
	{
		IteratorType current = begin + i;

		typename vector<IteratorType>::iterator it = lower_bound(lowestWithLength.begin() + 1, lowestWithLength.end(), current, DereferenceLess<IteratorType>());

		lisPrevious.push_back(*(it - 1));
		if(it == lowestWithLength.end())
			lowestWithLength.push_back(current);
		else if(*(*it) > *current)
			*it = current;
	}

	IteratorType lisLast = lowestWithLength.back();
	size_t lisLength = lowestWithLength.size() - 1;
	lowestWithLength.clear();

	vector<size_t> lisIndex;
	lisIndex.resize(lisLength);

	while(lisLength > 0)
	{
		--lisLength;
		lisIndex[lisLength] = lisLast - begin;
		lisLast = lisPrevious[lisLast - begin];
	}

	return lisIndex;
}

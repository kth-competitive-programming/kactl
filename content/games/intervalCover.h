/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: N/A
 * Description: Calculate the minimum number of intervals required to cover a specified interval. Returns indices of intervals forming the smallest set necessary to cover specified interval.
 * Time: O(N * log(N)) where N is the number of intervals.
 * Memory: O(N) where N is the number of intervals.
 * Status: Working
 */
#pragma once

template<typename IteratorType> struct DereferenceLess : binary_function<IteratorType, IteratorType, bool> {
	bool operator()(const IteratorType& first, const IteratorType& second) const {
		return (*first) < (*second);
	}
};

template<typename CoordinateType> vector<size_t> intervalCover(pair<CoordinateType, CoordinateType> toCover, const vector<pair<CoordinateType, CoordinateType> >& intervals) {
	vector<const pair<CoordinateType, CoordinateType>*> sortedIntervals;
	vector<size_t> answer;
	const CoordinateType* nextCover = &(toCover.first);
	sortedIntervals.reserve(intervals.size());
	for(size_t i = 0; i < intervals.size(); ++i)
		sortedIntervals.push_back(&intervals[i]);
	sort(sortedIntervals.begin(), sortedIntervals.end(), DereferenceLess<const pair<CoordinateType, CoordinateType>*>());
	size_t scan = 0;
	while(answer.empty() || *nextCover < toCover.second) {
		size_t bestCandidate = (size_t)-1;
		while(scan < sortedIntervals.size() && sortedIntervals[scan]->first <= *nextCover) {
			if(bestCandidate == (size_t)-1 || sortedIntervals[scan]->second > intervals[bestCandidate].second)
				bestCandidate = sortedIntervals[scan] - &intervals[0];
			++scan;
		}
		if(bestCandidate == (size_t)-1) return vector<size_t>();
		answer.push_back(bestCandidate);
		nextCover = &intervals[bestCandidate].second;
	}
	return answer;
}

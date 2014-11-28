/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * Source: N/A
 * Description: Calculate the minimum number of intervals required to cover a specified interval. Returns indices of intervals forming the smallest set necessary to cover specified interval.
 * Time: O(N * log(N)) where N is the number of intervals.
 * Memory: O(N) where N is the number of is.
 * Status: Working
 */
#pragma once

#include <vector>
using namespace std;

template<typename It> struct Cmp {                                                                        
    bool operator()(const It& first, const It& second) const {
        return (*first) < (*second);
    }   
};

template<typename C> vi intervalCover(pair<C, C> toCover, vector<pair<C, C> >& is) {
    vector<typeof(is.begin())> sorted;
    vi answer;
    C nextCover = toCover.first;
    sorted.reserve(is.size());
    rep(i,0,is.size()) sorted.push_back(is.begin() + i); 
    sort(sorted.begin(), sorted.end(), Cmp<typeof(is.begin())>());
    int scan = 0;
    while(answer.empty() || nextCover < toCover.second) {
        int best = 1<<29;
        while(scan < sorted.size() && sorted[scan]->first <= nextCover ) { 
            if(best == (1<<29) || sorted[scan]->second > is[best].second)
                best = sorted[scan] - is.begin();
            ++scan;
        }   
        if(best == (1<<29)) return vi();
        answer.push_back(best);
        nextCover = is[best].second;
    }   
    return answer;
}

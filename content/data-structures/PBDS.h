/**
 * Author:
 * Description: A set (not multiset!) with support for finding the n'th element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
int main() {
    ordered_set<int> X;
    for (int i=1; i<10; i+=2) X.insert(i); // 1 3 5 7 9
    cout << *X.find_by_order(2) << endl; // 5
    cout << X.order_of_key(6) << endl; // 3
    cout << X.order_of_key(7) << endl; // 3
    X.erase(3);
}

/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * Source: https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/
 * Description: Priority queue with support for $O(1)$ decrease-key.
 */
#include <cassert>
using namespace std;

#include <ext/pb_ds/priority_queue.hpp> /** keep-include */

typedef __gnu_pbds::priority_queue<int, greater<int>> pq;
pq p; p.push(1); p.push(2);
pq::point_iterator it = p.push(3);
p.modify(it, 0); // => t.top() == 0

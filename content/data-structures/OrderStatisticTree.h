/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: $\text{order of key}(x) \to numelements < x$, $\text{find by order}(k) \to k^{th} \text{ largest element}$ (0-indexed)
 * ExtDesc: O(\log N)
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

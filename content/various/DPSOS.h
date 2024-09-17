/**
 * Author: Maskrio
 * License: -
 * Source: -
 * Description: Sum over subsert
 * Time: O(N \times 2^N)
 * Status: -
 */
#pragma once

for(int i=0;i<n;i++) ans[ar[i]]++;
for(int d=0;d<m;d++) {
    for(int i=0;i<(1<<m);i++) {
        if((i&(1<<d))) ans[i] += ans[i^(1<<d)];
    }
}
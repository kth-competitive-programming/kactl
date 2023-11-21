/**
 * Author:
 * Description: Calculate length-L DeBruijn sequence.
 * Usage: Returns 1-base index. K is the number of alphabet, N is the length of different substring, L is the return length $(0 <= L <= K^N)$. vector<int> seq = de_bruijn(K, N, L);
 * Time: O(L), $N = L = 10^5, K = 10$ in 12ms.
 */
#pragma once

vector<int> de_bruijn(int K, int N, int L) {
    vector<int> ans, tmp;
    function<void(int)> dfs = [&](int T) {
        if((int)ans.size() >= L) return;
        if((int)tmp.size() == N) {
            if(N%T == 0)
                for(int i = 0; i < T && (int)ans.size() < L; i++)
                    ans.push_back(tmp[i]);
        } else {
            int k = ((int)tmp.size()-T >= 0 ? tmp[(int)tmp.size()-T] : 1);
            tmp.push_back(k);
            dfs(T);
            tmp.pop_back();
            for(int i = k+1; i <= K; i++) {
                tmp.push_back(i);
                dfs((int)tmp.size());
                tmp.pop_back();
            }
        }
    };
    dfs(1);
    return ans;
}

/**
 * Author: Julio
 * Source: Jhozzel
 * Description: Common sparse table, allows non-idempotent ops (0-based)
 * Time: O(NlogN) O(1) per query
 * Status: tested
 */
struct node {
    // something, overload +op, constructor...
};

struct DisjointST {
    vector<node> dp[32];

    DisjointST() {}
    DisjointST(vector<int> &arr){
        int i, c, h, l, n = (int)arr.size();
        vector<node> a(n);
        for (int i = 0; i < n; i++) a[i] = node(arr[i]);
        for (h = 0; h <= __lg(n); h++){
            dp[h].resize(n + 1);
            for (c = l = 1 << h; c < n + l; c += (l << 1)){
                for (i = c + 1; i <= min(n, c + l); i++){
                    dp[h][i] = dp[h][i - 1] + a[i - 1];
                }
                for (i = min(n, c) - 1; i >= c - l; i--){
                    dp[h][i] = a[i] + dp[h][i + 1];
                }
            }
        }
    }

    node query(int l, int r){ // [l, r]
        int h = __lg(l ^ (r + 1));
        return dp[h][l] + dp[h][r + 1];
    }
}; 
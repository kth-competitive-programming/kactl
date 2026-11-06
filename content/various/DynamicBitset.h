/**
 * Author: Julio
 * Source: some codeforces coment
 * Description: Allows different bitset sizes (compile time)
 * Time: O(log n)
 * Status: tested
 */
template <int len = 1>
void solve(int n) {
    if (n > len) {
        solve<std::min(len*2, MAXLEN)>(n);
        return;
    }
    // solution using bitset<len>
}
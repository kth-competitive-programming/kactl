#include "../utilities/template.h"
#include "../../content/strings/PalindromicTree.h"


int main() {
  rep(alpha, 2, 27) {
    rep(t, 0, 10000) {
      int n = 1 + rand() % 30;
      string s(n, 0);
      rep(i, 0, n) {
        s[i] = char(rand() % alpha);
      }
      PalinTree tree(s);
      map<string, int> mp;
      vector<vi> dp(n+1, vi(n+1));
      rep(i, 0, n+1) dp[0][i] = 1;
      rep(l, 1, n + 1) rep(i, 0, n - l + 1) {
        dp[l][i] = l<= 1 || (dp[l-2][i + 1] && s[i] == s[i + l - 1]);
        if (dp[l][i])
          ++mp[s.substr(i, l)];
      }
      rep(i, 2, tree.n) {
        string sub = s.substr(tree.pos[i], tree.len[i]);
        int cnt = mp.find(sub)->second;
        assert(cnt == tree.freq[i]);
        mp.erase(sub);
      }
      assert(mp.empty());
    }
  }
  cout << "Test passed!\n";
}

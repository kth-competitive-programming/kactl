/**
 * Author: whqkrkt04
 * Description: 1 x y: Move SxSx+1...Sy to front of string. $(0 \leq x \leq y < N)$
 * 2 x y: Move SxSx+1...Sy to back of string. $(0 \leq x \leq y < N)$
 * 3 x: Print Sx. $(0 \leq x < N)$
 * cf. rope.erase(index, count) : erase [index, index+count)
 * Time:
 */

#include <ext/rope>
using namespace __gnu_cxx;
int main() {
    string s; cin >> s;
    rope<char> R;
    R.append(s.c_str());
    int q; cin >> q;
    while(q--) {
        int t, x, y; cin >> t;
        switch(t) {
            case 1:
                cin >> x >> y; y++;
                R = R.substr(x, y-x) + R.substr(0, x) + R.substr(y, s.size());
                break;
            case 2:
                cin >> x >> y; y++;
                R = R.substr(0, x) + R.substr(y, s.size()) + R.substr(x, y-x);
                break;
            default:
                cin >> x;
                cout << R[x] << "\n";
        }
    }
}

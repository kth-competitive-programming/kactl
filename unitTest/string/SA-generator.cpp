//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <queue>
#include <bitset>
#include <utility>
#include <list>
#include <numeric>
#include <fstream>

#include <cstdio>
#include <cmath>
#include <cctype>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<string, int> pii;
typedef vector<int> vi;
int main()
{
    int n = 4;
    cout << n << endl;
    ofstream out("SA.out");
    rep(j,0,n)
    {
        int m = rand() % 80000 + 20;
        string s;
        rep(i,0,m)
            s += 'a' + rand() % 2;
        cout << s << endl;
        vector<pii> a;
        rep(i,0,m+1)
            a.push_back(pii(s.substr(i), i));
        sort(a.begin(), a.end());

        rep(i,0,a.size())
            out << a[i].second << " ";
        out << endl;
    }
}

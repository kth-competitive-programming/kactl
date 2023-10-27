#include <bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(v) v.begin(), v.end()
#define sz(x) ((int) (x).size())
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vp = vector<pii>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vb = vector<bool>;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p){return os << '(' << p.fi << ", " << p.se << ')';}
template<typename C, typename T = typename enable_if<!is_same<C, string>::value, typename C::value_type>::type>
ostream& operator<<(ostream &os, const C &v){string sep; for(const T &x : v) os << sep << x, sep = " "; return os;}
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values){
    cout << "[Debug]\n\t" << vars << " = ";
    string d = "[";
    (..., (cout << d << values, d = "] ["));
    cout << "]\n";
}
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    return 0;
}

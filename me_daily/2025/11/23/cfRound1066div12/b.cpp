#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define Rof(i, n) for (int i = (n) - 1; i >= 0; --i)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define EACH(x, v) for (auto& x : (v))
#define pb push_back
#define fi first
#define se second
#define V vector
#define SORT(v) sort(ALL(v))

using umpii = unordered_map<int, int>;
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vs = vector<string>;

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

int main() {
    int t; cin>>t;
    while(t--) {
        int n,x,y; cin>>n>>x>>y; string s; cin>>s;
        long long a = llabs(x), b = llabs(y);
        int c8 = 0;
        for(char ch: s) if(ch=='8') ++c8;
        int c4 = n - c8;
        long long lim1 = c4 + 2LL*c8;
        long long limInf = n;
        bool ok = (a + b <= lim1) && (max(a,b) <= limInf);
        cout << (ok ? "YES" : "NO") << '\n';
    }   
    return 0;
}
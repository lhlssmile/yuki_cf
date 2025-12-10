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
ll qpow(ll x, ll y) {
    ll r = 1;
    while(y) {
        if(y&1) r = r * x % mod;
        x = x * x % mod;y>>=1;
    }
    return r;
}

ll solve(const vi& a) {
    int n = a.size();
    for(int i = 1; i < n; i++) {
        if(a[i] <= a[0]) return 0;
    }
    static ll fac[100005];
    fac[0] = 1;
    for(int i = 1; i < n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    return fac[n - 1]; // (n-1)!
}

int main() {
    int n;cin>>n;vi complexity(n);For(i,n)cin>>complexity[i];
    cout<<solve(complexity)<<"\n";

    return 0;
}
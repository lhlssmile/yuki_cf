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
    int t;cin>>t;while(t--) {
        int n, k, q; cin >> n >> k >> q;
        V<pii> c1, c2;
        For(i, q) {
            int op,l,r;cin>>op>>l>>r;
            if(op==1) c1.pb({l,r}); else c2.pb({l,r});
        }
        vi inC1(n+1), inC2(n+1);
        EACH(x, c1) FOR(i, x.fi, x.se+1) inC1[i]=1;
        EACH(x, c2) FOR(i, x.fi, x.se+1) inC2[i]=1;
        vi a(n+1, k+1);
        vi P;
        FOR(i,1,n+1) if(!inC1[i]) P.pb(i);
        For(idx, (int)P.size()) a[P[idx]] = idx % k;
        EACH(seg, c1) {
            int l = seg.fi, r = seg.se;
            int pos = -1;
            FOR(i,l,r+1) if(!inC2[i]) { pos = i; break; }
            if(pos!=-1) a[pos] = k;
        }
        FOR(i,1,n+1) {
            if(i>1) cout<<" ";
            cout<<a[i];
        }
        cout<<"\n";
    }
}
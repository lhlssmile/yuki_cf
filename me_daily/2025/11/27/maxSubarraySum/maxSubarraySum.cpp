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
    int n,k;cin>>n>>k;vi a(n);For(i,n)cin>>a[i];
    //可选不同起点，可以变长。 -> dp..麻烦,prefix?sliding windows?
    const ll INF = 1LL << 60;
    vll prefix(n+1,0);For(i,n) prefix[i+1]=prefix[i]+a[i];
    //哈希表怎么工作呢? len(sub_ai)%k==0&&maximum_sum(sub_ai) 哈希表存sum,idx?
    vll min_pref(k,LLONG_MAX/2);
    min_pref[0]=0;
    ll ans = -INF;
    For(i, n) {
        ll cur_sum = prefix[i+1];
        int r_mod=(i+1)%k;
        if(min_pref[r_mod]!=LLONG_MAX/2){
            ans = max(ans,cur_sum-min_pref[r_mod]);
        }
        min_pref[r_mod] = min(min_pref[r_mod],cur_sum);
    }
    cout<<ans<<"\n";
    return 0;
}

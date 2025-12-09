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
    int n;cin>>n;vi nums(n);For(i,n)cin>>nums[i];
    const int MAX_VAL = 200010;
    vi right(n,0);vi freq_right(MAX_VAL,0);
    Rof(j, n) {
        int target = nums[j]<<1;
        if(target<MAX_VAL) right[j]=freq_right[target];
        if(nums[j]<MAX_VAL) freq_right[nums[j]]++;
    }
    ll ans = 0;vi freq_left(MAX_VAL,0);
    For(j, n) {
        int target = nums[j]<<1;
        ll left_cnt = 0;if(target<MAX_VAL) left_cnt = freq_left[target];
        ll contrib = (left_cnt * right[j])%mod;
        ans = (ans + contrib)%mod;
        if(nums[j]<MAX_VAL)freq_left[nums[j]]++;
    }
    cout <<ans<<"\n";
    return 0;
}


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
    int n,k;cin>>n>>k;vll a(n);For(i,n)cin>>a[i];
    deque<int> maxq,minq;
    vll f(n+1,0),prefix(n+1,0);f[0] = prefix[0] = 1;
    int l = 0;For(r, n) {
        //找最大最小?扩右 ?什么时候移动左?
        while(!maxq.empty() && a[maxq.back()] <= a[r]) maxq.pop_back();
        while(!minq.empty() && a[minq.back()] >= a[r]) minq.pop_back();
        maxq.pb(r),minq.pb(r);
        while(a[maxq.front()] - a[minq.front()] > k) {
            if(maxq.front() == l) maxq.pop_front();
            if(minq.front() == l) minq.pop_front();l++;
        }
        //前缀和算dp[r+1]
        f[r + 1] = (prefix[r] - (l == 0 ? 0 : prefix[l - 1]) + mod) % mod;
        prefix[r+1] = (prefix[r]+f[r+1])%mod;
    }
    cout<< f[n];
    return 0;
}
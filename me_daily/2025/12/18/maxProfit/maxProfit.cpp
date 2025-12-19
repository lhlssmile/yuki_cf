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
    int n,k;cin>>n>>k;vi prices(n),strategy(n);For(i,n)cin>>prices[i];For(i,n)cin>>strategy[i];
    ll mx_profit = 0LL;
    For(i, n) mx_profit += prices[i] * strategy[i];
    ll mx_change = 0,cur_change = 0;
    For(i, k>>1) cur_change += (0 - strategy[i]) * prices[i];
    FOR(i,k>>1,k) cur_change -= (1 - strategy[i]) * prices[i];
    mx_change = cur_change;
    FOR(i, 1, n - k + 1) {
        int j = i - 1;
        cur_change -= (1 - strategy[j]) * prices[j];
        int j_mid = i + k/2-1;
        cur_change += (1 - strategy[j_mid]) * prices[j];
        cur_change -= (0 - strategy[j_mid]) * prices[j];
        int j_new = i + k - 1;
        cur_change += (1 - strategy[j_new]) * prices[j_new];
        mx_change = max(mx_change, cur_change);
    }
    cout << mx_profit << "\n";
    return 0;
}

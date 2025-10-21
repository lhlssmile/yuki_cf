#include <bits/stdc++.h>
using namespace std;

#define ALL(v) (v).begin(), (v).end()
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define pb push_back
#define fi first
#define se second
#define V vector
#define SORT(v) sort(ALL(v))

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using umpii = unordered_map<int, int>;
const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
int solve(vi& a, int k, int op) {
    umpii cnt;
    map<int, int> diff;
    for (int x : a) {
        cnt[x]++;
        diff[x];
        diff[x - k]++;
        diff[x + k + 1]--;
    }
    int ans = 0, sumd = 0;
    for (auto [x, c] : diff) {
        sumd += c;
        ans = max(ans, min(cnt[x] + op, sumd));
    }
    return ans;
}
int main() {
    int n, k, op; cin >> n >> k >> op;
    vi a(n);
    for (int &x : a) cin >> x;
    cout << solve(a, k, op) << "\n";
    // your code here
    
    return 0;
}

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

using umpii = unordered_map<int, int>;
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;

int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
int t, n, m;
ll solve(vi& lovsub) {
    //ex: n = 6 size_n = 1 + 2 + 3 + 4 + 5 + 6 = (n + 1) *n / 2  m = 6?
    // b=[1,1,2,1,2,3,1,2,3,4,1,2,3,4,5,1,2,3,4,5,6]  x出现次数为: 1: n + 1, 2: n
    // fsb = 3 1 2 3 4 1 找最长严格增序列?
    int sbn = lovsub.size();
    int inc = 0;
    FOR(i, 1, sbn) if (lovsub[i] > lovsub[i - 1]) inc++; else inc = 0;
    // cout << inc << "\n";
    //如果等于sbn那么就算次数?否则就是1次  ex lov subarray 1 2 3
    if (inc == sbn - 1) return n - lovsub.back() + 1;
    return 1;
}
int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m; // n最大结尾数字 子序列长度?
        vi fsb(m);
        For(i, m) cin >> fsb[i];
        //子字符串匹配
        cout << solve(fsb) << "\n";
    }
    
    return 0;
}
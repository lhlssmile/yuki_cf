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
    int t; cin >> t; while(t--) {  // 加了cin>>t; 就是它！
        int n; cin >> n; vi a(2 * n); For(i, 2 * n) cin >> a[i];
        umpii cnt;
        EACH(x, a) cnt[x]++;
        int odd_cnt = 0, even_cnt = 0;
        for(auto [_, c] : cnt) {
            if (c & 1) odd_cnt++;
            else if (c > 0 && c % 2 == 0) even_cnt++; }
        int base = odd_cnt, extra;
        if (odd_cnt > 0) {
            extra = even_cnt << 1;
        } else {
            int pan = n % 2;
            int maxk = (even_cnt % 2 == pan) ? even_cnt : even_cnt - 1;
            extra = maxk << 1;
        }
        
        cout << base + extra << "\n";
    }    
    return 0;

}
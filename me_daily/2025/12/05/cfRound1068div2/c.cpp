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
    int t;cin>>t;while(t--){
        int n; long long k;cin>>n>>k;vector<long long> a(n);For(i,n)cin>>a[i];
        unordered_set<long long> st;EACH(x, a) st.insert(x);
        vector<long long> good;
        for (auto &x : st) {
            long long v = x;
            long long t_mul = 1;
            bool ok = true;
            while (v * t_mul <= k) {
                long long m = v * t_mul;
                if (st.count(m) == 0) { ok = false; break; }
                ++t_mul;
            }
            if (ok) good.pb(v);
        }
        unordered_map<long long,long long> min_good_div;
        for (auto &x : good) {
            long long v = x;
            long long t_mul = 1;
            while (v * t_mul <= k) {
                long long m = v * t_mul;
                if (st.count(m)) {
                    auto it = min_good_div.find(m);
                    if (it == min_good_div.end() || v < it->second) min_good_div[m] = v;
                }
                ++t_mul;
            }
        }
        bool possible = true;
        unordered_set<long long> ans_set;
        for (auto &x : a) {
            auto it = min_good_div.find(x);
            if (it == min_good_div.end()) { possible = false; break; }
            ans_set.insert(it->second);
        }
        if (!possible) {
            cout << -1 << "\n";
        } else {
            vector<long long> ans(ALL(ans_set));
            SORT(ans);
            cout << ans.size() << "\n";
            for (size_t i = 0; i < ans.size(); ++i) {
                if (i) cout << ' ';
                cout << ans[i];
            }
            cout << "\n";
        }
    }
    return 0;
}

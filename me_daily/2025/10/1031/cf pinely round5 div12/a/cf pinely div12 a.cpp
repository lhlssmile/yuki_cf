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

int main() {
    int t, r0, x, d, n;
    string divs;
    For(_, t)  {
        cin >> r0 >> x >> d >> n;
        cin >> divs;
        int ans = 0;
        int cur_s = r0;  // current rating
        For(i, n) {
            if (divs[i] == '1') {  // div1: 总是参加
                ans += 1;
                // 如果后面有'2'，降rating（用string::find，简单！）
                if (i < n - 1 && divs.find('2', i + 1) != string::npos) {
                    cur_s = max(0, cur_s - d);
                }
            } else {  // div2
                if (cur_s < x) {
                    ans += 1;
                    // 参加后，如果后面有'2'，降rating
                    if (i < n - 1 && divs.find('2', i + 1) != string::npos) {
                        cur_s = max(0, cur_s - d);
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
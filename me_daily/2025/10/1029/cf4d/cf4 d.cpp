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

struct Envelope {
    int w, h, idx;
    bool operator<(const Envelope& other) const {
        return w < other.w;
    }
};

int main() {
    int n, w, h;
    cin >> n >> w >> h;
    
    vector<Envelope> envs;
    For(i, n) {
        int wi, hi;
        cin >> wi >> hi;
        // 只考虑能放下卡片的信封
        if (wi > w && hi > h) {
            envs.pb({wi, hi, i + 1});
        }
    }
    
    if (envs.empty()) {
        cout << 0 << endl;
        return 0;
    }
    
    // 按宽度排序
    sort(ALL(envs));
    
    int m = envs.size();
    vi dp(m, 1);
    vi parent(m, -1);
    
    // DP求最长递增子序列
    FOR(i, 1, m) {
        For(j, i) {
            // 当前信封的宽高都要严格大于前一个
            if (envs[i].w > envs[j].w && envs[i].h > envs[j].h) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }
    }
    
    // 找到最长链的结尾
    int max_len = *max_element(ALL(dp));
    int end_idx = find(ALL(dp), max_len) - dp.begin();
    
    // 重构路径
    vi path;
    int idx = end_idx;
    while (idx != -1) {
        path.pb(envs[idx].idx);
        idx = parent[idx];
    }
    
    reverse(ALL(path));
    
    cout << max_len << endl;
    For(i, path.size()) {
        cout << path[i];
        if (i < path.size() - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}
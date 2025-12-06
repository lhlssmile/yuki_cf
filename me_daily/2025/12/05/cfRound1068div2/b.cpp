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
    int t;cin>>t;while(t--) {
        int n;cin>>n;vll a(n),b(n);For(i,n)cin>>a[i];For(i,n)cin>>b[i];
        

        long long maxK = 0, minK = 0;
        For(i,n){
            long long nextMax = max(maxK - a[i], b[i] - minK);
            long long nextMin = min(minK - a[i], b[i] - maxK);
            maxK = nextMax;
            minK = nextMin;
        }
        cout << maxK << "\n";
    }
    return 0;
}
// 笔记：
        // - 每一步是对当前分数 k 的线性变换：
        //   RED:  k' = k - a[i]  （关于 k 单调递增）
        //   BLUE: k' = b[i] - k  （关于 k 单调递减）
        // - 为了得到“下一步的最大值”，RED 需要上一步的最大 k；BLUE 需要上一步的最小 k。
        // - 因此只需同时维护 "上一步的最大/最小可达分数" 两个值即可：
        //   nextMax = max( maxK - a[i], b[i] - minK )
        //   nextMin = min( minK - a[i], b[i] - maxK )
        // - 初始 k=0，所以 maxK=minK=0。遍历一遍即可得到最终最大分数。
        // - 复杂度 O(n)；值范围在 64 位整数内。
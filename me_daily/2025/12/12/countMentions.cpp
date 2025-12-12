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
    int p,n;cin>>n;V<array<string,3>> events(n);
    static string HERE = "HERE",ALL = "ALL",OFFLINE ="OFFLINE",MESSAGE="MESSAGE";
    For(i,n){
        cin >> events[i][0] >> events[i][1] >> events[i][2];
    }
    vi ans(p,0);V<tuple<int,int,int>> es;
    int all = 0;
    for(auto &e : events) {
        int cur_t = stoi(e[1]);string mention=e[2];
        if(e[0][0]=='O'){
            int i = stoi(mention);es.emplace_back(cur_t,i,1);
            es.emplace_back(cur_t+60,-1,i);
        }else if(mention[0]=='A') {
            all++;
        }else if(mention[0]=='H'){
            all++;es.emplace_back(cur_t,2,-1);
        }else {
            for(const auto& part : mention | ranges::views::split(' ')) {
                string s(part.begin()+2,part.end());
                ans[stoi(s)]++;
            }
        }
    }
    ranges::sort(es);int here = 0;
    for(auto& [_, type, id] : es) {
        if(type==2)here++;
        else{ 
            ans[id] += type * here;
        }
    }
    for(int& cnt : ans) {cnt += all;}
    For(i,p) {
        cout << ans[i] << (i + 1 == p ? "" : " ");
    }
    /*
    pi:
    （ALL 次数）
+（该用户显式提到 id<number> 的次数）
+（所有 HERE 次数）
-（用户离线覆盖的 HERE 次数）

    */
    return 0;
}

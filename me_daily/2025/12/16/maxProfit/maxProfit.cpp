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

int solve(int n,vi& present,vi& future,V<vi>& hierarchy, int budget) {
    V<vi> g(n);EACH(x, hierarchy) {int u=x[0],v=x[1];g[u].pb(v);}
    const int _inf = 1e9;
    auto dfs = [&](this auto&& dfs, int x) -> V<vi>{
        V sub_f(2, vi(budget+1,-_inf));For(i,2) sub_f[i][0]=0;
        EACH(y, g[x]) {
            auto fy = dfs(y);
            For(k, 2) {
                vi nf(budget+1,-_inf);nf[0]=0;
                For(jy,fy[k].size()) {
                    int res_y=fy[k][jy];
                    if(res_y < 0) continue;
                    FOR(j,jy,budget+1) {
                        nf[j] = max(nf[j], sub_f[k][j - jy] + res_y);

                    }
                }
                sub_f[k] = nf;
            }
        }
        //加x自己
        V<vi> f(2, vi(budget+1, -_inf));
        For(k,2) {
            For(j, budget+1) f[k][j] = sub_f[0][j];
            int cost = present[x] / (k + 1), prof = future[x]-cost;
            if(prof<0) continue;
            FOR(j,cost,budget+1) {
                if(sub_f[1][j- cost] == -_inf) continue;
                f[k][j] = max(f[k][j], sub_f[1][j-cost]+prof);
            }
        }
        return f;
    };
    int ans=0;
    auto root_f = dfs(0);
    For(j, budget + 1) {
        ans = max(ans, root_f[0][j]);
    }
    return ans;
}

int main() {
    int n,h,budget;cin>>n>>h>>budget;vi present(n),future(n);
    For(i,n) cin>>present[i];For(i,n)cin>>future[i];
    V<V<int>> hierarchy(h);For(i,h){int u,v;cin>>u>>v;hierarchy[i]={u-1,v-1};}
    cout <<solve(n,present,future,hierarchy,budget)<<"\n";
    return 0;
}

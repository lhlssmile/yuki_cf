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

/**
 * m辆bus si->di v = x, 
 * all pi wants to lpos, s_pi -> l;
 */

int main() {
    int n,m; ll l; int x,y; cin>>n>>m>>l>>x>>y; V<pii> bsd(n); vi ppos(m);
    For(i, n) {int s,d;cin>>s>>d;bsd[i]={s,d};}
    For(i, m) {int p;cin>>p;ppos[i]=p;}
    V<ll> coords; coords.reserve(2*n+m);
    For(i,n){coords.pb(bsd[i].fi);coords.pb(bsd[i].se);} For(i,m){coords.pb(ppos[i]);}
    SORT(coords); coords.erase(unique(ALL(coords)), coords.end());
    auto getId = [&](ll v){ return (int)(lower_bound(ALL(coords), v) - coords.begin()); };
    int U = (int)coords.size();
    V<double> tag(4*U, 1e100);
    function<void(int,int,int,int,int,double)> upd = [&](int u,int L,int R,int ql,int qr,double val){
        if(ql<=L && R<=qr){ tag[u]=min(tag[u], val); return; }
        int mid=(L+R)>>1; if(ql<=mid) upd(u<<1,L,mid,ql,qr,val); if(qr>mid) upd(u<<1|1,mid+1,R,ql,qr,val);
    };
    function<double(int,int,int,int,double)> qry = [&](int u,int L,int R,int idx,double acc){
        acc=min(acc, tag[u]); if(L==R) return acc; int mid=(L+R)>>1; if(idx<=mid) return qry(u<<1,L,mid,idx,acc); else return qry(u<<1|1,mid+1,R,idx,acc);
    };
    EACH(se, bsd){ int lId=getId(se.fi), rId=getId(se.se); double val = (double)(se.se - se.fi) / (double)x + (double)(l - se.se) / (double)y; upd(1,0,U-1,lId,rId,val);}    
    cout.setf(std::ios::fixed); cout<<setprecision(10);
    For(i,m){ double ans = (double)(l - ppos[i]) / (double)y; int id=getId(ppos[i]); double v = qry(1,0,U-1,id,1e100); ans=min(ans, v); cout<<ans<<"\n"; }
    return 0;
}
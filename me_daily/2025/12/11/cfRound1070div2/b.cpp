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
        int n;cin>>n;string s;cin>>s;
        vi pos1;For(i,n){
            if(s[i]=='1') pos1.pb(i+1);
        }int k = pos1.size();
        int mx_g=0;
        For(i,k-1){
            int g = pos1[i+1]-pos1[i]-1;
            mx_g=max(g,mx_g);
        }
        int g = pos1[0]+n-1-pos1.back();mx_g=max(mx_g,g);
        cout<<mx_g<<"\n";
    }   
    return 0;
}
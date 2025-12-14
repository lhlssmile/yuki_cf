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
struct Fenwick{
    int n;vi tree;
    Fenwick(int n):n(n),tree(n+2,0) {}
    void update(int i,int v) {
        i++;while(i<=n) {
            tree[i] +=v;i += i & -i;
        }
    }
    int query(int i) {
        int s = 0;
        while(i){
            s += tree[i];
            i -= i & -i;
        }
        return s;
    }
    int range(int l, int r) {
        if (l>r) return 0;
        return query(r) - (l > 0 ? query(l - 1) : 0);}
};
int main() {
    string s;cin>>s;int q;cin>>q;V<vi> queries(q);
    For(i,q) {
        int type;cin>>type;if(type==1) {
            int j;cin>>j;queries[i].pb(j);
        }else{
            int l,r;cin>>l>>r;queries[i][0]=l,queries[i][1]=r;
        }
    }
    int n = s.size();
    Fenwick ft(n-1);
    //2type:l,r 最小删除数=r-l+1 - LAS_length.
    For(i,n-1) {
        int val = (s[i] != s[i+1] ? 1 : 0);ft.update(i,val);
    }
    vi ans;
    For(qi, q) {
        auto& q = queries[qi];int type = q[0];if(type==1){
            int j = q[1];char old_char = s[j];s[j]=(old_char=='A'?'B':'A');
            if(j>0){
                int pos = j-1;int old_trans=(s[pos]!=old_char?1:0);
                int new_trans=(s[pos]!=s[j]?1:0);
                ft.update(pos,new_trans-old_trans);
            }
            if (j<n-1) {
                int pos = j;
                    int old_trans = (old_char != s[j + 1] ? 1 : 0);
                    int new_trans = (s[j] != s[j + 1] ? 1 : 0);
                    ft.update(pos, new_trans - old_trans);
            }
        }else{
                int l = q[1], r = q[2];
                int sub_len = r - l + 1;
                if (sub_len == 1) {
                    ans.pb(0);
                    continue;
                }
                int trans_sum = ft.range(l, r - 1);
                int las = 1 + trans_sum;
                int del = sub_len - las;
                ans.pb(del);
        }
        
    }
    return 0;
}







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

struct Fenwick{
    int n;vi tree;
    Fenwick(int n):n(n),tree(n+2,0) {}
    void update(int i,int v) {
        i++;while(i<=n) {
            tree[i] +=v;i += i & -i;
        }
    }
    int query(int i) {
        int s = 0;
        i = i + 1;
        while(i > 0) {
            s += tree[i];
            i -= i & -i;
        }
        return s;
    }
    int range(int l, int r) {
        if (l>r) return 0;
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }
};

class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        int n = s.size();
        if (n == 0) return {};
        int q = queries.size();
        Fenwick ft(n-1);
        //2type:l,r 最小删除数=r-l+1 - LAS_length.
        For(i,n-1) {
            int val = (s[i] != s[i+1] ? 1 : 0);ft.update(i,val);
        }
        vi ans;
        For(qi, q) {
            auto& qq = queries[qi];int type = qq[0];if(type==1){
                int j = qq[1];char old_char = s[j];s[j]=(old_char=='A'?'B':'A');
                if(j>0){
                    int pos = j-1;int old_trans=(s[pos]!=old_char?1:0);
                    int new_trans=(s[pos]!=s[j]?1:0);
                    ft.update(pos,new_trans-old_trans);
                }
                if (j<n-1) {
                    int pos = j;
                        int old_trans = (old_char != s[j + 1] ? 1 : 0);
                        int new_trans = (s[j] != s[j + 1] ? 1 : 0);
                        ft.update(pos, new_trans - old_trans);
                }
            }else{
                    int l = qq[1], r = qq[2];
                    int sub_len = r - l + 1;
                    if (sub_len == 1) {
                        ans.pb(0);
                        continue;
                    }
                    int trans_sum = ft.range(l, r - 1);
                    int las = 1 + trans_sum;
                    int del = sub_len - las;
                    ans.pb(del);
            }
           
        }
            return ans;
        }
};
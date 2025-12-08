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
    int n;vll tree;
    Fenwick(int n):n(n){
        tree.assign(n+1,0);
    }
    void add(int i,ll v) {
        for (; i <= n; i += i & -i) {
            tree[i] += v;
        }
    }
    ll sum(int i) {
        ll s = 0;
        for (; i > 0; i -= i & -i) s += tree[i];
        return s;
    }
    ll range(int l,int r) {
        return sum(r) - sum(l - 1);
    }
};

//https://leetcode.cn/problems/minimum-inversion-count-in-subarrays-of-fixed-length/
int main() {
    int n,k;cin>>n>>k;vll nums(n);For(i,n)cin>>nums[i];
    vll vals = nums;SORT(vals);vals.erase(unique(ALL(vals)),vals.end());
    vi rank(n);For(i,n) rank[i] = lower_bound(ALL(vals), nums[i]) - vals.begin() + 1;
    int m = vals.size();Fenwick ft(m);
    ll cur_inv = 0;For(i, k) { // 第一个窗口
        cur_inv += ft.range(rank[i] + 1, m);ft.add(rank[i],1);
    }
    ll min_inv = cur_inv;FOR(i,k,n){
        ll oldL = i - k;cur_inv -= ft.range(1,rank[oldL]-1);ft.add(rank[oldL],-1);
        cur_inv += ft.range(rank[i]+1,m);ft.add(rank[i],1);min_inv=min(min_inv,cur_inv);
    }
    cout<<min_inv<<"\n";
    return 0;
}
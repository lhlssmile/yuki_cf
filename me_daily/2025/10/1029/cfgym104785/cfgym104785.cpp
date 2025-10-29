#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
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
    int n, m;
    cin >> n >> m;
    vi idxs1, idxs2;
    FOR(i, 1, m + 1) {
        int ai, bi; cin >> ai >> bi;
        if (ai > bi) idxs1.pb(i);
        else idxs2.pb(i);
    }    
    cout << "YES" << "\n";
    if (idxs1.size() > idxs2.size()) {
        cout << idxs1.size() << endl;
        for(auto& i : idxs1) cout << i << " ";
    }else {
        cout << idxs2.size() << "\n";
        for(auto& i : idxs2) cout << i << " ";
    }
    return 0;
}

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

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;

const int inf = 0x3f3f3f3f;
const ll infl = 0x3f3f3f3f3f3f3f3fll;
const int mod = 1e9 + 7;
int t, n;
vll to_check = {1};
int fastio_init = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
vi pre = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
int prehandle = []() {
    for (int x : pre) {
        int k = to_check.size();
        For(i, k) to_check.pb(x * to_check[i]);
    }
    sort(to_check.begin(), to_check.end());
    return 0;
}();
int gcd(int a, int b) {
    while (b) {
        a = b, b = a % b;
    }   
    return a;
}
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        vi vis(51, 0);
        while (n--) {
            int x; cin >> x;
            vis[x] = 1;
        }
        
        
        for (auto x : to_check) {
            bool flg = true;
            For(i, 51) {
                if (vis[i] && gcd(i, x) == 1) {
                    flg = false;
                    break;
                }
            }
            if (flg) {
                cout << x << "\n";
                break;
            }
        }
        
    }
    
    return 0;
}
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

ll gcd(ll a, ll b) {
    while (b) {
        a, b = b, a % b;
    }
    return a;
}

int main() {
    vector<ll> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
    int t;
    cin >> t;
    For(_, t) {
        int n;
        cin >> n;
        vll a(n);
        For(i, n) cin >> a[i];
        ll ans = LLONG_MAX / 2;
        For(i, n) {
            ll ai = a[i];
            bool found = false;
            for (auto p : primes) {
                if (ai % p != 0) {
                    ans = min(ans, p);
                    found = true;
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
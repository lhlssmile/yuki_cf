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
vll get_primes(ll x) {
    vll res;
    ll i = 2;
    while(i*i <= x) {
        if (x%i==0) res.pb(i);
        while(x%i==0) x/=i;
        i++;
    }
    if (x>1) res.pb(x);
    return res;
}
ll gcd(ll a,ll b) {
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}
int main() {
    int n;cin>>n;vll a(n),b(n);For(i,n)cin>>a[i];For(i,n)cin>>b[i];
    ll g = a[0];FOR(i,1,n) g = gcd(g,a[i]);
    if (g == 1) cout<<0<<"\n";
    else {
        vll primes = get_primes(g);int k = (int)primes.size(); ll INF = (1LL << 60);
        vll covers(n, 0);
        For(i,n) {
            long long mask = 0;
            For(j, k) {
                if (b[i] % primes[j] != 0) mask |= (1LL << j);
            }
            covers[i] = mask;
        }
        vll f(1<<k, INF);
        f[0] = 0;
        For(i, n) {
            long long mask_i = covers[i];
            vll new_f = f;
            for (long long prev = 0; prev < (1LL << k); ++prev) {
                if (f[prev] == INF) continue;
                long long new_m = mask_i | prev;
                new_f[new_m] = min(new_f[new_m], f[prev] + (long long)(i + 1) * (i + 2));
            }
            f = std::move(new_f);
        }
        long long ans = f[(1<<k) - 1];
        cout << (ans == INF ? -1 : ans) << "\n";
    }
    return 0;
}

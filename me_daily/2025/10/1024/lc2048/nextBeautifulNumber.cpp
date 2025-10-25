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

auto isBalanced = [](int n) -> bool {
    string s = to_string(n);
    if (s.find('0') != string::npos) return false;
    vi f(10, 0);
    For(i, s.size()) f[s[i] - '0']++;
    FOR(i, 1, 10) if (f[i] != i && f[i] != 0) return false;
    return true;
};
int main() {
    int n; cin >> n;
    
    // your code here
    
    int x = n + 1;
    while (true) {
        if (isBalanced(x)) cout << x; break;
        x++;
    }

    return 0;
}
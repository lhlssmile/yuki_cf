#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        map<ll, ll> freq;
        for (ll x : a) ++freq[x];
        ll base = 0;
        vector<ll> extras;
        for (auto& p : freq) {
            ll h = p.first, f = p.second;
            base += (h / 2) * f;
            if (h % 2 == 1) extras.push_back(f);
        }
        sort(extras.rbegin(), extras.rend());
        ll alice_extra = 0, bob_extra = 0;
        for (size_t i = 0; i < extras.size(); ++i) {
            if (i % 2 == 0) alice_extra += extras[i];
            else bob_extra += extras[i];
        }
        ll alice = base + alice_extra;
        ll bob = base + bob_extra;
        cout << alice << " " << bob << "\n";
    }
    return 0;
}
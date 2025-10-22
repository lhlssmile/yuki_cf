#include <bits/stdc++.h>
using namespace std;

int solve(string &s, int k) {
    int n = s.size();
    int ans = 0;
    int last = -k;  

    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            if (i - last >= k) {
                // 这个 1 与前一个有效 1 距离太远，需要保护它
                ++ans;
                last = i;  
            } else {
                // 距离近，不需要保护，但它也能起到“阻挡”作用
                last = i;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        string s;
        cin >> n >> k >> s;
        cout << solve(s, k) << "\n";
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    for(int test=0; test<t; test++) {
        int n; cin >> n;
        vector<long long> a(n+1);
        for(int i=1; i<=n; i++) cin >> a[i];
        vector<long long> M(n+1);
        M[1] = a[1];
        for(int i=2; i<=n; i++) M[i] = max(M[i-1], a[i]);
        long long ans = 0;
        for(int i=1; i<=n; i+=2) {  // 奇数 i
            if(i == n) {  // 最后奇数
                long long U = M[n-1] - 1;
                long long bi = min(a[n], max(0LL, U));
                ans += a[n] - bi;
            } else if(i == 1) {  // 第一
                long long U = M[2] - 1;
                long long bi = min(a[1], max(0LL, U));
                ans += a[1] - bi;
            } else {  // 中间奇数
                // 1 4 2 5 3 -> m = [1, 4, 4, 5, 5]
                long long U = min(M[i-1], M[i+1]) - 1;
                long long bi = min(a[i], max(0LL, U));
                ans += a[i] - bi;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
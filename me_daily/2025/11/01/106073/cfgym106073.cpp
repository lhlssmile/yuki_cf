#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, q;
	cin >> n >> q;

	vector<int> nums(q);
	for (auto &v: nums) cin >> v;

	int mod = 1e9 + 7, rev2 = (mod + 1) / 2;
	vector<int> ans(n + 1, 0);

	int cur = 0;
	reverse(nums.begin(), nums.end());

	for (auto &v: nums) {
		ans[v] = (1ll * cur * rev2 + ans[v]) % mod;
		cur = 1ll * (cur + v) * rev2 % mod;
	}

	ans[1] = (ans[1] + cur) % mod;

	for (int i = 1; i <= n; i ++)
		cout << ans[i] << '\n';

	return 0;
}
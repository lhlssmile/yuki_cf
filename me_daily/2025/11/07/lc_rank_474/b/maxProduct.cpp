#include <bits/stdc++.h>
using namespace std;

using ll = long long;
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        ll mx1 = 0, mx2 = 0;
        for (auto x : nums) {
            x = abs(x);
            if (x > mx1) {
                mx2 = mx1;
                mx1 = x;
            }else if (x >  mx2) {
                mx2 = x;
            }
        }
        return 1e5 * mx1 * mx2;
    }
};
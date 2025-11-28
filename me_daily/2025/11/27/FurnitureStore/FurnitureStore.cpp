#include <bits/stdc++.h>
#define For(i,n) for(int i = 0; i < (n);i++)
using namespace std;
using vi = vector<int>;

signed main() {
    int t;cin>>t;while(t--){
        int n;cin>>n;vi a(n);For(i,n)cin>>a[i];
        vi never_bought;
        int k = 0;
        int curr_min = 101;
        For(i, n) {
            if (a[i] >= curr_min) {
                k++;
                never_bought.push_back(i+1);
            }else {
                curr_min = min(curr_min, a[i]);
            }
        }
        cout<<k<<"\n";
        if (!never_bought.empty()) {
            For(i,never_bought.size()) {
            cout << never_bought[i] <<" ";
        }
        }
        
        cout <<"\n";
    }
    return 0;
}
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

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int val) :val(0),left(nullptr),right(nullptr) {}
    TreeNode(int val, auto* left, auto* right) : val(val), left(left), right(right) {}
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

auto input_tree(const vi& a) {
    // 层序遍历插入? a至少有一个val
    queue<TreeNode*> q;
    auto* root = new TreeNode(a[0]);
    q.push(root);
    int i = 1;
    while (!q.empty() && i < a.size()) {
        auto node = q.front(); q.pop();
        if (i < a.size() && a[i] != -1) {
            node->left = new TreeNode(a[i]);
            q.push(node->left);
        }
        ++i;
        if (i < a.size() && a[i] != -1) {
            node->right = new TreeNode(a[i]);
            q.push(node->right); 
        }
        ++i;
    }
    return root;
}
umpii cnt;
int mx_cnt;

int dfs(TreeNode* node) {
    if (!node) return 0;
    int s = node->val + dfs(node->left) + dfs(node->right);
    cnt[s]++;
    mx_cnt = max(mx_cnt, cnt[s]);
    return s;
}
vi findFrequentTreeSum(TreeNode* root) {
    cnt.clear();
    mx_cnt = 0;
    dfs(root);
    vi ans;
    for (auto& p: cnt) {
        if (p.second == mx_cnt) {
            ans.pb(p.first);
        }
    }
    return ans;
}
/**
 * 出现次数最多的子树元素和
 * 点权? 但这里只有父到子(DFS)?
 * 算 u -> v的sum -> (这里的uv是父子关系) 没必要用 s[u] + s[v] 2 * s_lca(u, v) + w_lca(u, v)
 */
int main() {
    int n; cin>>n; vi a(n);For(i, n) cin>>a[i]; auto* root = input_tree(a); 
    auto ans = findFrequentTreeSum(root);
    EACH(x, ans) cout << x << "\n";
    return 0;
}
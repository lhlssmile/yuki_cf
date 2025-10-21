#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef long long ll;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define SWAP(x, y) do { (x) = (x) ^ (y); (y) = (x) ^ (y); (x) = (x) ^ (y); } while(0)

const int INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;

int cmp_asc_int(const void *a, const void *b) { return (*(int*)a - *(int*)b); }

// main
int main() {
    int n;
    scanf("%d", &n);  // 先读n！
    int *a = (int*)calloc(n, sizeof(int));  // 现在n对了
    For(i, n) {
        scanf("%d", &a[i]);  // &a[i]
    }
    if (n == 1) {  // 边界，虽n>=2但防
        printf("1\n");
        free(a);
        return 0;
    }
    int tmp[2] = {a[0] - 1, a[1] - 1};
    if (tmp[1] > tmp[0]) {  // 加if！
        tmp[1]--;
    }
    tmp[1] += (n * (n - 1)) / 2;  // 加
    tmp[0] += tmp[1] / (n - 1);
    tmp[1] %= (n - 1);  // 加%！
    tmp[0] %= n;
    int *ans = (int*)calloc(n, sizeof(int));
    ans[0] = tmp[0] + 1;
    ans[1] = tmp[1] + 1;
    if (ans[1] >= ans[0]) {
        ans[1]++;
    }
    ans[1] = MIN(ans[1], n);  // 防> n (n=2可能)
    int *vis1 = (int*)calloc(n + 1, sizeof(int));
    int *vis2 = (int*)calloc(n + 1, sizeof(int));
    int *mapping = (int*)calloc(n + 1, sizeof(int));
    For(i, n + 1) vis2[i] = 1;
    FOR(i, 2, n) vis1[a[i]] = 1;
    For(i, 2) {  // i=0,1
        if (ans[i] <= n) vis2[ans[i]] = 0;  // 防> n
    }
    int p1 = 1, p2 = 1;
    for (int _ = 0; _ < n - 2; _++) {
        while (p1 <= n && !vis1[p1]) p1++;  // 加界！
        while (p2 <= n && !vis2[p2]) p2++;
        if (p1 > n || p2 > n) break;  // 安全
        mapping[p1] = p2;
        p1++;
        p2++;
    }
    FOR(i, 2, n) {
        ans[i] = mapping[a[i]];
    }
    For(i, n) {
        if (i > 0) printf(" "); 
        printf("%d", ans[i]);
    }
    printf("\n");  // \n
    //free
    free(a); free(ans); free(vis1); free(vis2); free(mapping);
    return 0;
}
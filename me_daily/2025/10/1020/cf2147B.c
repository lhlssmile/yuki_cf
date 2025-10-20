#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve(int n, int *res) {
    // calloc自动0，无需memset
    // memset(res, 0, 2 * n * sizeof(int));  // 删掉，用calloc
    
    // Fill first n positions with n, n-1, ..., 1
    for (int i = 0; i < n; i++) {
        res[i] = n - i;
    }
    
    // Fill remaining positions
    for (int x = n; x >= 1; x--) {
        for (int j = n; j < 2 * n; j += x) {
            if (res[j] == 0) {
                res[j] = x;
                break;
            }
        }
    }
}

int main() {
    int t, n;
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d", &n);
        
        int *res = calloc(2 * n, sizeof(int));  // 改calloc，一行清零
        solve(n, res);
        
        // 缓冲输出：用char buf收集，防TLE
        char buf[2000010];  // 2n<=4e5，数字max10位+空格，够大
        int pos = 0;
        for (int i = 0; i < 2 * n; i++) {
            pos += sprintf(buf + pos, "%d ", res[i]);  // 收集到buf
        }
        buf[pos - 1] = '\n';  // 替换最后一个空格为\n
        buf[pos] = '\0';      // 结束
        printf("%s", buf);    // 一次性输出
        
        free(res);
    }
    
    return 0;
}
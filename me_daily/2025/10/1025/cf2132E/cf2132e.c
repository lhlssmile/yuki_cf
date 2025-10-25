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

const int INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;

// 快速输入缓冲区
char buf[1 << 20], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

// 快速读取整数
int read_int() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

// 快速读取long long
ll read_ll() {
    ll x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

// 快速输出缓冲区
char out_buf[1 << 20];
int out_pos = 0;

void flush_output() {
    fwrite(out_buf, 1, out_pos, stdout);
    out_pos = 0;
}

void write_ll(ll x) {
    if (x < 0) {
        out_buf[out_pos++] = '-';
        x = -x;
    }
    if (x == 0) {
        out_buf[out_pos++] = '0';
    } else {
        char temp[20];
        int len = 0;
        while (x > 0) {
            temp[len++] = '0' + x % 10;
            x /= 10;
        }
        for (int i = len - 1; i >= 0; i--) {
            out_buf[out_pos++] = temp[i];
        }
    }
    out_buf[out_pos++] = '\n';
}

// 比较函数，用于qsort降序排序
int cmp_desc(const void *a, const void *b) {
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if (x > y) return -1;
    if (x < y) return 1;
    return 0;
}

// 三分搜索中的目标函数
ll calc_sum(ll *prefix_va, ll *prefix_ko, int k, int z) {
    return prefix_va[k] + prefix_ko[z - k];
}

int main() {
    int t = read_int();
    
    while (t--) {
        int n = read_int();
        int m = read_int();
        int q = read_int();
        
        // 使用动态内存分配
        ll *a = (ll*)calloc(n, sizeof(ll));
        ll *b = (ll*)calloc(m, sizeof(ll));
        ll *prefix_va = (ll*)calloc(n + 1, sizeof(ll));
        ll *prefix_ko = (ll*)calloc(m + 1, sizeof(ll));
        int **queries = (int**)calloc(q, sizeof(int*));
        for (int i = 0; i < q; i++) {
            queries[i] = (int*)calloc(3, sizeof(int));
        }
        
        // 读取Vadim的卡片
        for (int i = 0; i < n; i++) {
            a[i] = read_ll();
        }
        
        // 读取Kostya的卡片
        for (int i = 0; i < m; i++) {
            b[i] = read_ll();
        }
        
        // 读取查询
        for (int i = 0; i < q; i++) {
            queries[i][0] = read_int();
            queries[i][1] = read_int();
            queries[i][2] = read_int();
        }
        
        // 贪心策略：按降序排序
        qsort(a, n, sizeof(ll), cmp_desc);
        qsort(b, m, sizeof(ll), cmp_desc);
        
        // 计算前缀和
        prefix_va[0] = 0;
        for (int i = 0; i < n; i++) {
            prefix_va[i + 1] = prefix_va[i] + a[i];
        }
        
        prefix_ko[0] = 0;
        for (int i = 0; i < m; i++) {
            prefix_ko[i + 1] = prefix_ko[i] + b[i];
        }
        
        // 处理每个查询
        for (int i = 0; i < q; i++) {
            int x = queries[i][0];
            int y = queries[i][1];
            int z = queries[i][2];
            
            // 特殊情况：不需要选择任何卡片
            if (z == 0) {
                write_ll(0);
                continue;
            }
            
            // 计算Vadim选择卡片数量k的取值范围
            int L = (z - y > 0) ? z - y : 0;  // max(0, z - y)
            int R = (z < x) ? z : x;          // min(z, x)
            
            // 无解情况
            if (L > R) {
                write_ll(0);
                continue;
            }
            
            // 三分搜索找到最优的k值
            int low = L, high = R;
            while (high - low >= 3) {
                int m1 = low + (high - low) / 3;
                int m2 = high - (high - low) / 3;
                
                ll val1 = calc_sum(prefix_va, prefix_ko, m1, z);
                ll val2 = calc_sum(prefix_va, prefix_ko, m2, z);
                
                if (val1 > val2) {
                    high = m2;
                } else {
                    low = m1;
                }
            }
            
            // 在剩余的小范围内暴力搜索最优值
            ll mx = 0;
            for (int k = low; k <= high; k++) {
                ll current = calc_sum(prefix_va, prefix_ko, k, z);
                if (current > mx) {
                    mx = current;
                }
            }
            
            write_ll(mx);
        }
        
        // 释放动态分配的内存
        free(a);
        free(b);
        free(prefix_va);
        free(prefix_ko);
        for (int i = 0; i < q; i++) {
            free(queries[i]);
        }
        free(queries);
    }
    
    flush_output();  // 刷新输出缓冲区
    return 0;
}
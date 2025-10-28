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
#define ALL(v, n) (v), ((v) + (n))

const int INF = 0x3f3f3f3f;
const ll INFL = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1000000007;

// 快速输入缓冲区 - 解决scanf性能问题
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

// 排序比较函数
int cmp_asc_int(const void *a, const void *b) { return (*(int*)a - *(int*)b); }
int cmp_desc_int(const void *a, const void *b) { return (*(int*)b - *(int*)a); }
int cmp_asc_ll(const void *a, const void *b) { ll x=*(ll*)a, y=*(ll*)b; return (x > y) - (x < y); }
int cmp_desc_ll(const void *a, const void *b) { ll x=*(ll*)b, y=*(ll*)a; return (x > y) - (x < y); }

typedef struct {
    int left, right;
} Result;

Result check(int vi, int n, int* a, int k) {
    int* s = calloc(n + 1, sizeof(int));
    Result res = {0, 0};
    
    FOR(i, 1, n + 1) {
        int val = a[i] >= vi ? 1 : -1;
        s[i] = s[i - 1] + val;
    }
    
    int pos = 0;
    FOR(i, k, n + 1) {
        if (s[i - k] < s[pos]) pos = i - k;
        if (s[i] - s[pos] >= 0) {
            res.left = pos + 1;
            res.right = i;
            free(s);
            return res;
        }
    }
    free(s);
    return res;
}

void solve(int* a, int n, int k) {
    int lo = 1, hi = n, ans = 0;
    Result final_res = {0, 0};
    
    while (lo <= hi) {
        int vi = lo + (hi - lo) / 2;
        Result lr = check(vi, n, a, k);
        if (lr.left > 0) {
            ans = vi;
            final_res = lr;
            lo = vi + 1;
        } else {
            hi = vi - 1;
        }
    }
    printf("%d %d %d\n", ans, final_res.left, final_res.right);
}
int main() {
    int t, n, k;
    t = read_int();
    For(_, t) {
        n = read_int();
        k = read_int();
        int* a = calloc(n + 1, sizeof(int));
        FOR(i, 1, n + 1) a[i] = read_int();
        solve(a, n, k);
    }
    
    flush_output();  // 刷新输出缓冲区
    return 0;
}
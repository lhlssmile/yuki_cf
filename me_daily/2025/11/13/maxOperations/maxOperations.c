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

int main() {

    char s[10001];
    int idx = 0;
    char c;
    while ((c == getchar()) != '\n' && c != EOF && c != -1) {
        s[idx++] = c;
    }
    s[idx] = '\0';
    int n = idx;
    int i = 0, ans = 0, ones = 0;
    while (i < n) {
        if (s[i] == '1') {
            ones++,i++;continue;
        }   
        if (ones > 0) ans += ones;
        while (i < n && s[i] == '0') i++;
    }
    printf("%d", ans);
    
    flush_output();  // 刷新输出缓冲区
    return 0;
}
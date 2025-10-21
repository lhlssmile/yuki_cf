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

int cmp_asc_int(const void *a, const void *b) { return (*(int*)a - *(int*)b); }
int cmp_desc_int(const void *a, const void *b) { return (*(int*)b - *(int*)a); }
int cmp_asc_ll(const void *a, const void *b) { ll x=*(ll*)a, y=*(ll*)b; return (x > y) - (x < y); }
int cmp_desc_ll(const void *a, const void *b) { ll x=*(ll*)b, y=*(ll*)a; return (x > y) - (x < y); }

// 快速读int（模拟cin）
int read_int() {
    int x = 0; char c = getchar(); bool neg = false;
    while (c < '0' || c > '9') { if (c == '-') neg = true; c = getchar(); }
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return neg ? -x : x;
}

int main() {
    int t;
    scanf("%d", &t);
    For(_, t) {
        int n, m;
        scanf("%d %d", &n, &m);
        int *fsb = (int*)malloc(m * sizeof(int));
        For(i, m) scanf("%d", &fsb[i]);
        int inc = 0;
        FOR(i, 1, m) {
            if (fsb[i] > fsb[i - 1]) inc++;
            else inc = 0;
        }
        if (inc == m - 1) {
            printf("%d\n", n - fsb[m - 1] + 1);
        } else {
            printf("1\n");
        }
        free(fsb);
    }
    return 0;
}
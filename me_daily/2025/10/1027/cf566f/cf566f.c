#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define For(i, n) for (int i = 0; i < (n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
typedef long long ll;

const int MAXN = 1000001;

char buf[1 << 20], *p1 = buf, *p2 = buf;
#define getchar_fast() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
int read_int() {
    int x = 0, f = 1;
    char c = getchar_fast();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar_fast();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar_fast();
    }
    return x * f;
}

int main() {
    int n = read_int();
    bool* exist = (bool*)calloc(MAXN, sizeof(bool)); 
    int* f = (int*)calloc(MAXN, sizeof(int));
    int ans = 1;

    For(i, n) {
        int x = read_int();
        exist[x] = true;
    }

    FOR(x, 1, MAXN) {
        if (!exist[x]) continue;
        f[x] = MAX(f[x], 1);
        for (int y = x * 2; y < MAXN; y += x) { 
            if (exist[y]) f[y] = MAX(f[y], f[x] + 1);
        }
        ans = MAX(ans, f[x]);
    }

    printf("%d\n", ans);

    free(exist);
    free(f);
    return 0;
}

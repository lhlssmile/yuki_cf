#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

long long solve(long long *a, int n) {
    long long *odds = malloc(sizeof(long long) * n);  // 动态分配，够用
    long long *evens = malloc(sizeof(long long) * n);
    int odd_count = 0, even_count = 0;
    long long sum_e = 0;
    
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            evens[even_count++] = a[i];
            sum_e += a[i];
        } else {
            odds[odd_count++] = a[i];
        }
    }
    
    if (odd_count == 0) {
        free(odds);
        free(evens);
        return 0;
    }
    
    qsort(odds, odd_count, sizeof(long long), compare);
    
    long long sum_o = 0;
    for (int i = 0; i < odd_count; i++) {
        sum_o += odds[i];
    }
    
    int sac = odd_count / 2;
    long long sum_sac = 0;
    for (int i = 0; i < sac; i++) {
        sum_sac += odds[i];
    }
    
    free(odds);
    free(evens);
    return sum_o - sum_sac + sum_e;
}

int main() {
    int t, n;
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d", &n);
        long long a[200010];  // 也把a数组放大点，稳
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        
        long long ans = solve(a, n);
        printf("%lld\n", ans);
    }
    
    return 0;
}
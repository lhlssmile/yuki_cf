#include <stdio.h>
#include <stdlib.h>

// 最大值范围（ai <= 50）
#define MAX_N 51
// to_check数组的最大容量
#define MAX_TO_CHECK 50000
// 预处理的质数
int pre[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
int pre_size = sizeof(pre) / sizeof(pre[0]);

// 静态数组存储to_check
long long to_check[MAX_TO_CHECK];
size_t to_check_size = 0;

// GCD函数
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 比较函数，用于qsort
int cmp(const void *a, const void *b) {
    long long x = *(long long *)a;
    long long y = *(long long *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

// 预处理to_check
void prehandle() {
    to_check[to_check_size++] = 1; // 初始值1
    for (int i = 0; i < pre_size; i++) {
        size_t k = to_check_size;
        for (size_t j = 0; j < k; j++) {
            long long new_val = (long long)pre[i] * to_check[j];
            if (to_check_size < MAX_TO_CHECK && new_val <= 50 * 50) { // 限制大小
                to_check[to_check_size++] = new_val;
            }
        }
    }
    // 排序to_check
    qsort(to_check, to_check_size, sizeof(long long), cmp);
}

// 主函数
int main() {
    // 执行预处理
    prehandle();

    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int vis[MAX_N] = {0}; // 初始化vis数组
        while (n--) {
            int x;
            scanf("%d", &x);
            vis[x] = 1;
        }

        // 遍历to_check
        for (size_t i = 0; i < to_check_size; i++) {
            long long x = to_check[i];
            int flg = 1; // 标记是否满足条件
            for (int j = 0; j < MAX_N; j++) {
                if (vis[j] && gcd(j, (int)x) == 1) {
                    flg = 0;
                    break;
                }
            }
            if (flg) {
                printf("%lld\n", x);
                break;
            }
        }
    }

    return 0;
}
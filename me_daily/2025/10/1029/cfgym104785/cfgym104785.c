#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *idxs1 = (int*)malloc(m * sizeof(int));
    int *idxs2 = (int*)malloc(m * sizeof(int));
    int count1 = 0, count2 = 0;
    
    for (int i = 1; i <= m; i++) {
        int ai, bi;
        scanf("%d %d", &ai, &bi);
        if (ai > bi) {
            idxs1[count1++] = i;
        } else {
            idxs2[count2++] = i;
        }
    }
    
    printf("YES\n");
    
    if (count1 > count2) {
        printf("%d\n", count1);
        for (int i = 0; i < count1; i++) {
            printf("%d", idxs1[i]);
            if (i < count1 - 1) printf(" ");
        }
        printf("\n");
    } else {
        printf("%d\n", count2);
        for (int i = 0; i < count2; i++) {
            printf("%d", idxs2[i]);
            if (i < count2 - 1) printf(" ");
        }
        printf("\n");
    }
    
    free(idxs1);
    free(idxs2);
    return 0;
}
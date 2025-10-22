#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define For(i, n) for (int i = 0; i < (n); ++i)

typedef struct {
    int first, second;
} Pair;

typedef struct {
    Pair *data;
    int size;
    int cap;
} PairVector;

void init(PairVector *v) {
    v->size = 0;
    v->cap = 8;
    v->data = malloc(sizeof(Pair) * v->cap);
}

void ensure_capacity(PairVector *v) {
    if (v->size >= v->cap) {
        v->cap *= 2;
        v->data = realloc(v->data, sizeof(Pair) * v->cap);
    }
}

void push_back(PairVector *v, int a, int b) {
    ensure_capacity(v);
    v->data[v->size].first = a;
    v->data[v->size].second = b;
    v->size++;
}

void free_v(PairVector *v) {
    free(v->data);
    v->data = NULL;
    v->size = v->cap = 0;
}

int main() {
    int n;
    scanf("%d", &n);

    PairVector xy;
    init(&xy);

    if (n & 1) {
        push_back(&xy, 0, 0);
        int x = 0, y = 0;
        for (int i = 0; i < n / 2 - 1; ++i) {
            y += 25;
            push_back(&xy, x, y);
            x += 25;
            push_back(&xy, x, y);
        }
        x = MAX(x, 25);
        push_back(&xy, x, 0);
        push_back(&xy, x / 25 * 9, -x / 25 * 12);
    } else {
        push_back(&xy, 0, 0);
        int x = 0, y = 0;
        for (int i = 0; i < n / 2 - 1; ++i) {
            y += 25;
            push_back(&xy, x, y);
            x += 25;
            push_back(&xy, x, y);
        }
        push_back(&xy, x, 0);
    }

    int dx = 5, dy = 12;
    for (int i = 0; i < xy.size; ++i) {
        int x = xy.data[i].first;
        int y = xy.data[i].second;
        int X = x * dx + y * dy;
        int Y = x * (-dy) + y * dx;
        printf("%d %d\n", X, Y);
    }

    free_v(&xy);
    return 0;
}

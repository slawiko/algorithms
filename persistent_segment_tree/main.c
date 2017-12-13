#include <stdio.h>
#include <stdlib.h>

struct Vertex {
    struct Vertex* l;
    struct Vertex* r;
    int min;
    int max;
    int cnt;
};

int cmp (const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}

void init(struct Vertex* v, int* a, int n, int i_from,  int min, int max) {
    if (v == NULL) {
        return;
    }
    if (n > 1) {
        int n_l = n / 2 + (n % 2 == 0 ? 0 : 1);
        int n_r = n / 2;

        v->l = (struct Vertex*)malloc(sizeof(struct Vertex));
        init(v->l, a, n_l, i_from, min, a[i_from + n_l - 1]);
        v->r = (struct Vertex*)malloc(sizeof(struct Vertex));
        init(v->r, a, n_r, i_from + n_l, a[i_from + n_l], max);
    } else {
        v->l = NULL;
        v->r = NULL;
    }
    v->min = min;
    v->max = max;
    v->cnt = 0;
}

struct Vertex* set(struct Vertex* v, int value) {
    if (v == NULL) {
        return NULL;
    }
    struct Vertex* temp = (struct Vertex*)malloc(sizeof(struct Vertex));
    if (v->min == value && v->max == value) {
        temp->l = NULL;
        temp->r = NULL;
        temp->min = value;
        temp->max = value;
        temp->cnt = v->cnt + 1;
    } else if (v->l->min <= value && value <= v->l->max) {
        temp->l = set(v->l, value);
        temp->r = v->r;
        temp->min = v->min;
        temp->max = v->max;
        temp->cnt = temp->l->cnt + v->r->cnt;
    } else {
        temp->l = v->l;
        temp->r = set(v->r, value);
        temp->min = v->min;
        temp->max = v->max;
        temp->cnt = v->l->cnt + temp->r->cnt;
    }

    return temp;
}

int getCnt(struct Vertex* v, int x, int y) {
    if (v == NULL) {
        return 0;
    }
    if (v->min > x) x = v->min;
    if (v->max < y) y = v->max;
    if (x > y) return 0;

    if (v->min == x && v->max == y) {
        return v->cnt;
    }
    return getCnt(v->l, x, y) + getCnt(v->r, x, y);
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    int* a = (int*)malloc(N * sizeof(int));
    int* temp_a = (int*)malloc(N * sizeof(int));
    int tmp;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &tmp);
        a[i] = tmp;
        temp_a[i] = tmp;
    }

    int* clean_a = (int*)malloc(N * sizeof(int));
    qsort(temp_a, N, sizeof(int), cmp);
    int clean_N = 1;
    clean_a[0] = temp_a[0];
    for (int i = 1; i < N; ++i) {
        if (clean_a[clean_N - 1] != temp_a[i]) {
            clean_a[clean_N] = temp_a[i];
            clean_N++;
        }
    }

    struct Vertex** roots = (struct Vertex**)malloc((N + 1) * sizeof(struct Vertex*));
    for (int i = 0; i < N + 1; ++i) {
        roots[i] = (struct Vertex*)malloc(sizeof(struct Vertex));
        if (i == 0) {
            init(roots[i], clean_a, clean_N, 0, clean_a[0], clean_a[clean_N - 1]);
        } else {
            roots[i] = set(roots[i - 1], a[i - 1]);
        }
    }

    int l, r, x, y, cnt;
    for (int i = 0; i < Q; ++i) {
        scanf("%d %d %d %d", &l, &r, &x, &y);
        cnt = getCnt(roots[r], x, y) - getCnt(roots[l - 1], x, y);
        printf("%d\n", cnt);
    }

    free(a);
    for (int i = 0; i < N + 1; ++i) {
        free(roots[i]);
    }
    return 0;
}
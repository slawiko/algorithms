#include <stdio.h>
#include <stdlib.h>

struct Index {
    double v;
    int i;
};

int cmpfunc (const void * a, const void * b) {
    struct Index *i1 = (struct Index*)a;
    struct Index *i2 = (struct Index*)b;
    if (i1->v > i2->v) {
        return -1;
    }
    if (i1->v < i2->v) {
        return 1;
    }
    return 0;
}

int* find_subset(const int* a, const int* b, int n, int k, int b_max) {
    double l = 0, m = n * 500000, r = n * 1000000;
    struct Index* sums = (struct Index*)malloc(n * sizeof(struct Index));

    double set_sum = 0;

    while ((r - l) > 1. / (b_max * k)) {
        set_sum = 0;
        for (int i = 0; i < n; ++i) {
            sums[i] = (struct Index){a[i] - m * b[i], i};
        }

        qsort(sums, n, sizeof(struct Index), cmpfunc);

        for (int i = 0; i < k; ++i) {
            set_sum += sums[i].v;
        }
        if (set_sum > 0) {
            l = m;
        } else if (set_sum < 0) {
            r = m;
        } else {
            break;
        }
        m = l + (r - l) / 2.;
    }

    int* result = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; ++i) {
        result[i] = sums[i].i + 1;
    }

    free(sums);

    return result;
}

int main() {
    int T;
    int n, k;
    int *a, *b;
    int *result;

    scanf("%d", &T);

    for (int i = 0; i < T; ++i) {
        scanf("%d %d", &n, &k);

        a = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[j]);
        }

        int b_max = 0;
        b = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            scanf("%d", &b[j]);
            if (b[j] > b_max) b_max = b[j];
        }

        result = find_subset(a, b, n, k, b_max);
        for (int j = 0; j < k; ++j) {
            printf("%d ", result[j]);
        }
        printf("\n");

        free(result);
        free(a);
        free(b);
    }


    return 0;
}
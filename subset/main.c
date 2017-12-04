#include <stdio.h>
#include <stdlib.h>

struct Index {
    long v;
    int i;
};

int cmpfunc (const void * a, const void * b) {
    struct Index *i1 = (struct Index*)a;
    struct Index *i2 = (struct Index*)b;
    if (i1->v > i2->v) {
        return 1;
    }
    if (i1->v < i2->v) {
        return -1;
    }
    return 0;
}

long* find_subset(const long* a, const long* b, int n, int k) {
    int t = n * 500000;
    struct Index* sums = (struct Index*)malloc(k * sizeof(struct Index));

    for (int i = 0; i < n; ++i) {
        sums[i] = (struct Index){a[i] - t * b[i], i};
    }

    qsort(sums, n, sizeof(struct Index), cmpfunc);

    return sums;
}

int main() {
    int T;
    int n, k;
    long *a, *b;
    long *result;

    scanf("%d", &T);

    for (int i = 0; i < T; ++i) {
        scanf("%d %d", &n, &k);

        a = (long*)malloc(n * sizeof(long));
        for (int j = 0; j < n; ++j) {
            scanf("%ld", &a[j]);
        }

        b = (long*)malloc(n * sizeof(long));
        for (int j = 0; j < n; ++j) {
            scanf("%ld", &b[j]);
        }

        result = find_subset(a, b, n, k);
        for (int j = 0; j < k; ++j) {
            printf("%ld ", result[j]);
        }
        printf("\n");
    }



    return 0;
}
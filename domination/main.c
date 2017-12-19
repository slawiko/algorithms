#include <stdio.h>
#include <stdlib.h>

int contains(const int* X, int a, int n) {
    for (int i = 0; i < n; ++i) {
        if (X[i] == a) return i;
    }
    return -1;
}

int empty_index(const int* C, int n) {
    for (int i = 0; i < n; ++i) {
        if (C[i] == 0) return i;
    }
    return -1;
}

const int NEUTRAL_ELEMENT = 1;

int main() {
    int k;
    scanf("%d", &k);

    int* X = (int*)malloc((k - 1) * sizeof(int));
    for (int i = 0; i < k - 1; ++i) {
        X[i] = NEUTRAL_ELEMENT;
    }
    int* C = (int*)malloc((k - 1) * sizeof(int));
    for (int i = 0; i < k - 1; ++i) {
        C[i] = 0;
    }

    int a, index, e_index;
    scanf("%d", &a);

    while(a != -1) {
        if (a == 0) {
            for (int i = 0; i < k - 1; ++i) {
                printf("%d ", X[i]);
            }
            printf("\n");
        } else {
            index = contains(X, a, k - 1);
            if (index != -1) {
                C[index] += 1;
            } else {
                e_index = empty_index(C, k - 1);
                if (e_index == -1) {
                    for (int i = 0; i < k - 1; ++i) {
                        C[i]--;
                        if (C[i] == 0) X[i] = NEUTRAL_ELEMENT;
                    }
                } else {
                    X[e_index] = a;
                    C[e_index]++;
                }
            }
        }

        scanf("%d", &a);
    }

    free(X);
    free(C);

    return 0;
}
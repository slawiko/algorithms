#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Vertex {
    int from;
    int to;
    struct Vertex* l;
    struct Vertex* r;
    int min;
    int max;
    int cnt;
};

int cmp (const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}
//
//void calc_add_info(struct Vertex* v) {
//    if (v == NULL) {
//        return;
//    }
//    if (v->value == -1) {
//        v->odd_sum = v->l->odd_sum + v->r->odd_sum;
//        v->odd_cnt = v->l->odd_cnt + v->r->odd_cnt;
//        v->even_sum = v->l->even_sum + v->r->even_sum;
//        v->even_cnt = v->l->even_cnt + v->r->even_cnt;
//    } else {
//        bool is_even = v->value % 2 == 0;
//        v->odd_sum = is_even ? 0 : v->value;
//        v->even_sum = is_even ? v->value : 0;
//        v->odd_cnt = is_even ? 0 : 1;
//        v->even_cnt = is_even ? 1 : 0;
//    }
//    if (v->incr_cnt > 0) {
//        v->odd_sum += v->odd_cnt * v->incr_cnt;
//        v->even_sum += v->even_cnt * v->incr_cnt;
//
//        if (v->incr_cnt % 2 == 1) {
//            v->odd_sum = v->odd_sum ^ v->even_sum;
//            v->even_sum = v->odd_sum ^ v->even_sum;
//            v->odd_sum = v->odd_sum ^ v->even_sum;
//
//            v->odd_cnt = v->odd_cnt ^ v->even_cnt;
//            v->even_cnt = v->odd_cnt ^ v->even_cnt;
//            v->odd_cnt = v->odd_cnt ^ v->even_cnt;
//        }
//    }
//}

void init(struct Vertex* v, int* a, int n, int i_from,  int from, int to) {
    if (v == NULL) {
        return;
    }
    v->from = from;
    v->to = to;
    if (n > 1) {
        int n_l = n / 2 + (n % 2 == 0 ? 0 : 1);
        int n_r = n / 2;

        v->l = (struct Vertex*)malloc(sizeof(struct Vertex));
        init(v->l, a, n_l, i_from, from, a[i_from + n_l - 1]);
        v->r = (struct Vertex*)malloc(sizeof(struct Vertex));
        init(v->r, a, n_r, i_from + n_l, a[i_from + n_l], to);
    } else {
        v->l = NULL;
        v->r = NULL;
    }
    v->min = from;
    v->max = to;
    v->cnt = n;
}

//void incr_incr(struct Vertex* v, int incr) {
//    if (v->incr_cnt == -1) {
//        v->value += incr;
//    } else {
//        v->incr_cnt += incr;
//    }
//}
//
//void check_if_incr(struct Vertex* v) {
//    if (v == NULL) {
//        return;
//    }
//    if (v->incr_cnt > 0 && v->value == -1) {
//        incr_incr(v->l, v->incr_cnt);
//        calc_add_info(v->l);
//        incr_incr(v->r, v->incr_cnt);
//        calc_add_info(v->r);
//        v->incr_cnt = 0;
//    }
//}
//
//void inc(struct Vertex* v, int l, int r, int c) {
//    if (v == NULL) {
//        return;
//    }
//    if (v->from > l) l = v->from;
//    if (v->to < r) r = v->to;
//    if (l > r) return;
//
//    check_if_incr(v);
//
//    if (v->from == l && v->to == r) {
//        if (v->incr_cnt == -1) {
//            v->value += c;
//        } else {
//            v->incr_cnt += c;
//        }
//    } else {
//        inc(v->l, l, r, c + v->incr_cnt);
//        inc(v->r, l, r, c + v->incr_cnt);
//        v->incr_cnt = 0;
//    }
//    calc_add_info(v);
//}
//
//void set(struct Vertex* v, int pos, int value) {
//    if (v == NULL) {
//        return;
//    }
//    if (v->from > pos || pos > v->to) {
//        return;
//    }
//
//    check_if_incr(v);
//
//    if (v->from == pos && v->to == pos) {
//        v->value = value;
//    } else {
//        set(v->l, pos, value);
//        set(v->r, pos, value);
//    }
//    calc_add_info(v);
//}
//
//long long getSumEven(struct Vertex* v, int l, int r) {
//    if (v == NULL) {
//        return 0;
//    }
//    if (v->from > l) l = v->from;
//    if (v->to < r) r = v->to;
//    if (l > r) return 0;
//
//    if (v->from == l && v->to == r) {
//        return v->even_sum;
//    }
//    check_if_incr(v);
//    return getSumEven(v->l, l, r) + getSumEven(v->r, l, r);
//}
//
//long long getSumOdd(struct Vertex* v, int l, int r) {
//    if (v == NULL) {
//        return 0;
//    }
//    if (v->from > l) l = v->from;
//    if (v->to < r) r = v->to;
//    if (l > r) return 0;
//
//    if (v->from == l && v->to == r) {
//        return v->odd_sum;
//    }
//    check_if_incr(v);
//    return getSumOdd(v->l, l, r) + getSumOdd(v->r, l, r);
//}

void clean(struct Vertex* v) {
    if (v->l != NULL) {
        clean(v->l);
    }
    if (v->r != NULL) {
        clean(v->r);
    }
    free(v);
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
            init(roots[0], clean_a, clean_N, 0, clean_a[0], clean_a[clean_N - 1]);
        } else {

        }
    }

    int l, r, x, y;
    for (int i = 0; i < Q; ++i) {
        scanf("%d %d %d %d", &l, &r, &x, &y);
    }

    free(a);
    clean(roots[0]);
    return 0;
}
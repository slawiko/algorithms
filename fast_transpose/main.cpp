#include <stdio.h>
#include <vector>

std::vector<int> generate_input(int n, int seed) {
    std::vector<int> d(n * n);
    for (size_t i = 0; i < d.size(); ++i) {
        d[i] = seed;
        seed = ((long long) seed * 197 + 2017) & 987654;
    }
    return d;
}

long long get_hash(const std::vector<int> &d) {
    const long long MOD = 987654321054321LL;
    const long long MUL = 179;

    long long result_value = 0;
    for (size_t i = 0; i < d.size(); ++i)
        result_value = (result_value * MUL + d[i]) & MOD;
    return result_value;
}

int main() {
    int n, seed, k;
    const int BLOCK = 30;

    scanf("%d %d %d", &n, &seed, &k);
    std::vector<int> matrix = generate_input(n, seed);

    int i, j, size;
    for (int m = 0; m < k; ++m) {
        scanf("%d %d %d", &i, &j, &size);

        for (int i1 = 0; i1 < size && i1 < n; i1 += BLOCK) {
            for (int j1 = i1; j1 < size && j1 < n; j1 += BLOCK) {
                for (int ib = 0; ib < BLOCK && i1 + ib < size; ++ib) {
                    for (int jb = i1 == j1 ? ib + 1 : 0; jb < BLOCK && j1 + jb < size; ++jb) {
                        std::swap(matrix[(i + j1 + jb) * n + (j + i1 + ib)], matrix[(i + i1 + ib) * n + (j + j1 + jb)]);
                    }
                }
            }
        }
    }

    printf("%lld", get_hash(matrix));

    return 0;
}
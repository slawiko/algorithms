#include <iostream>
#include <fstream>

int main() {
    std::ifstream fin;
    fin.open("/Users/slawiko/workspace/algorithms_practice/CacheMiss/in.txt");

    int cache_size = 0;
    int k = 0;
    int line_size = 0;
    int n = 0;
    fin >> cache_size;
    fin >> k;
    fin >> line_size;
    fin >> n;

    int lines_count = cache_size / (k * line_size);

    int* addresses = new int[n];
    for (int i = 0; i < n; i++) {
        fin >> addresses[i];
    }

    int** cache = new int* [k];
    for (int i = 0; i < k; i++) {
        cache[i] = new int[lines_count];
        for (int j = 0; j < lines_count; j++) {
            cache[i][j] = 0;
        }
    }

    int cache_miss = 0;
    int cache_hit = 0;
    for (int i = 0; i < n; i++) {

    }

    delete[] addresses;

    return 0;
}
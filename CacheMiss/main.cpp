#include <iostream>

struct cache_line {
    int last_modified;
    int first_address;
};

int main() {
    int cache_size = 0;
    int k = 0;
    int line_size = 0;
    int n = 0;
    std::cin >> cache_size;
    std::cin >> k;
    std::cin >> line_size;
    std::cin >> n;


    int* addresses = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> addresses[i];
    }

    int lines_count = cache_size / (k * line_size);
    cache_line** cache = new cache_line* [k];
    for (int i = 0; i < k; i++) {
        cache[i] = new cache_line[lines_count];
        for (int j = 0; j < lines_count; j++) {
            cache[i][j].last_modified = -1;
            cache[i][j].first_address = -1;
        }
    }

    int cache_miss = 0;
    int cache_hit = 0;
    int line_number = 0;
    int bank_number = 0;
    for (int i = 0; i < n; i++) {
        line_number = (addresses[i] / line_size) % lines_count;
        bank_number = 0;
        int worse_time = cache[bank_number][line_number].last_modified;
        bool hit = false;
        for (int j = 0; j < k; j++) {
            if (cache[j][line_number].first_address != -1 &&
                cache[j][line_number].first_address + line_size > addresses[i] &&
                addresses[i] >= cache[j][line_number].first_address) {
                hit = true;
                cache[j][line_number].last_modified = i;
                break;
            } else if (worse_time > cache[j][line_number].last_modified) {
                bank_number = j;
                worse_time = cache[bank_number][line_number].last_modified;
            }
        }
        if (hit) {
            cache_hit++;
        } else {
            cache_miss++;
            cache[bank_number][line_number].first_address = addresses[i] - (addresses[i] % line_size);
            cache[bank_number][line_number].last_modified = i;
        }
    }

    std::cout << cache_hit << " " << cache_miss;

    delete[] addresses;
    delete[] cache;

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

const int k = 7;
const int m = 10000000;
std::hash<char*> name_hash;
std::vector<bool> bloom_filter(m);

unsigned int SDBMHash(const char* str, unsigned int length) {
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

size_t double_hashing(char* str, size_t length, int index) {
    return (name_hash(str) + index * SDBMHash(str, length)) % m;
}

int check(char* name) {
    bool exist = true;
    for (int i = 0; i < k; ++i) {
        if (!bloom_filter[double_hashing(name, std::strlen(name), i)]) {
            exist = false;
            break;
        }
    }

    return exist ? 1 : 0;
}

void add(char* name) {
    for (int i = 0; i < k; ++i) {
        size_t tmp = double_hashing(name, strlen(name), i);
        std::cout << tmp << '\n';
        bloom_filter[tmp] = true;
    }
}

int main() {
    int N;
    std::ifstream in("input.txt");
    std::ofstream of("output.txt");
    in >> N;

    int cmd_buffer, exist;
    char name_buffer[25];
    for (int i = 0; i < N; ++i) {
        in >> cmd_buffer >> name_buffer;

        switch (cmd_buffer) {
            case 0:
                exist = check(name_buffer);
                of << exist;
                break;
            case 1:
                add(name_buffer);
                break;
        }
    }
    return 0;
}
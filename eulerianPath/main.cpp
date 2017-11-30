#include <stdio.h>
#include <vector>
#include <iostream>

struct Vertex {
    int number;
    bool is_visited;
};

void dfs(std::vector<std::vector<Vertex>>& vs, Vertex& cur, int prev) {
    std::cout << cur.number;
    cur.is_visited = true;
    for (int i = 0; i < vs[cur.number - 1].size(); ++i) {
        if (vs[cur.number - 1][i].number != prev && !vs[cur.number - 1][i].is_visited) {
            dfs(vs, vs[cur.number - 1][i], cur.number);
            std::cout << cur.number;
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<Vertex>> vertices(n);
    int from;
    int to;
    for (size_t i = 0; i < n - 1; i++) {
        std::cin >> from >> to;
        vertices[from - 1].push_back({ to, false });
        vertices[to - 1].push_back({ from, false });
    }

    dfs(vertices, vertices[0][0], -1);

    return 0;
}
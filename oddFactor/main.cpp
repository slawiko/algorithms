#include <stdio.h>
#include <vector>
#include <iostream>

struct Edge {
    int from;
    int to;
};

int dfs(std::vector<std::vector<int>>& vs, std::vector<bool>& marks, int cur, int prev, std::vector<Edge>& result) {
    int index = cur - 1;
    if (marks[index]) {
        return 0;
    }
    marks[index] = true;
    int counter = 0;
    for (int i = 0; i < vs[index].size(); ++i) {
        if (vs[index][i] != prev && !marks[vs[index][i] - 1]) {
            if (dfs(vs, marks, vs[index][i], cur, result) == 1) {
                counter++;
            }
        }
    }
    if (counter % 2 == 0) {
        if (prev == -1) {
            return -1;
        }
        result.push_back({ prev, cur });
        return 1;
    }
    return 0;
}

int main() {
    int n;
    int m;
    std::cin >> n;
    std::cin >> m;

    std::vector<std::vector<int>> vertices(n);
    int from;
    int to;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to;
        vertices[from - 1].push_back(to);
        vertices[to - 1].push_back(from);
    }

    std::vector<Edge> result;
    std::vector<bool> marks;
    for (int i = 0; i < n; ++i) {
        marks.push_back(false);
    }
    int tmp;

    for (int i = 0; i < n; ++i) {
        tmp = dfs(vertices, marks, vertices[i][0], -1, result);
        if (tmp == -1) {
            std::cout << -1;
            return 0;
        }
    }

    std::cout << result.size() << '\n';

    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i].from << ' ' << result[i].to << '\n';
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <random>
#include <queue>

int** create_graph(size_t n, int m, int *&degrees, double *&gist)
{
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    rng.seed(std::random_device{}());

    size_t size = n * m;
    int** result = new int*[size];
    for (int i = 0; i < size; i++) {
        result[i] = new int[size];
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
        }
    }

    int* tempDegrees = new int [size];
    for (int i = 0; i < size; i++) {
        tempDegrees[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        double p = dist(rng);
        double threshold = 1. / (2. * (i + 1.) - 1.);
        if (threshold > p) {
            result[i/m][i/m] += 1;
            tempDegrees[i] += 2;
        } else {
            int index = 0;
            threshold += tempDegrees[index] / (2. * (i + 1.) - 1.);
            while (threshold < p) {
                index++;
                threshold += tempDegrees[index] / (2. * (i + 1.) - 1.);
            }
            result[index/m][i/m] += 1;
            result[i/m][index/m] += 1;
            tempDegrees[i] += 1;
            tempDegrees[index] += 1;
        }
    }

    for (int i = 0; i < size; i++) {
        degrees[i / m] += tempDegrees[i];
    }

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (degrees[j] == i) {
                count++;
            }
        }
        gist[i] = ((double)count) / n;
    }

    return result;
}

int **get_distances(size_t n, int **&result) {
    int **distances = new int *[n];
    for (int i = 0; i < n; i++) {
        distances[i] = new int[n];
        for (int j = 0; j < n; j++) {
            distances[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < n; i++) {
        std::queue<int> q;
        q.push(i);
        distances[i][i] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int j = 0; j < n; j++) {
                if (result[v][j] != 0) {
                    if (distances[i][j] == INT_MAX) {
                        q.push(j);
                    }
                    distances[i][j] = std::min(distances[i][j], distances[i][v] + 1);
                }
            }
        }
    }

    return distances;
}

double get_stat(size_t n, int** &result, int &svazn, int &max_dist)
{
    int sum = 0;
    int count = 0;

    int** distances = get_distances(n, result);

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (distances[i][j] == INT_MAX) {
                svazn = 0;
            } else {
                if (distances[i][j] > max_dist) {
                    max_dist = distances[i][j];
                }

                sum += distances[i][j];
                count++;
            }
        }
    }

    return (double)sum / (double)count;
}

void algorithm(size_t n, int m, std::string path)
{
    int* degree = new int [n];
    for (int i = 0; i < n; i++) {
        degree[i] = 0;
    }

    int svazn = 1;
    double* data_for_gistagram = new double[n];

    int** result = create_graph(n, m, degree, data_for_gistagram);
    int max_dist = 0;
    double average_dist = get_stat(n, result, svazn, max_dist);

    std::ofstream fout;
    fout.open(path);

    fout << svazn << "," << average_dist << "," << max_dist;
    fout << std::endl;
    fout << std::endl;

    for (int i = 0; i < n; i++) {
        fout << data_for_gistagram[i] << std::endl;
    }

    fout.close();
}

int main()
{
    //algorithm(4000, 10, "/Users/slawiko/workspace/algorithms_practice/RandomGraph/4000-10-out.csv");
    //algorithm(6000, 12, "/Users/slawiko/workspace/algorithms_practice/RandomGraph/6000-12-out.csv");
    //algorithm(8000, 12, "/Users/slawiko/workspace/algorithms_practice/RandomGraph/8000-12-out.csv");
    algorithm(10000, 10, "/Users/slawiko/workspace/algorithms_practice/RandomGraph/10000-10-out.csv");

    return 0;
}
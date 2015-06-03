#include <fstream>

using namespace std;

int max(int a, int b) {
	int max = a > b ? a : b;
	return max;
};

int main() {
	int n, m;
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	fin >> n >> m;

	int *sequence;
	sequence = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> sequence[i];
	}
	fin.close();

	int **tempMatr = new int *[m + 1];
	for (int i = 0; i < m + 1; i++) {
		tempMatr[i] = new int[n];
	}

	for (int i = 0; i < m + 1; i++) {
		for (int j = n - 1; j >= 0; j--) {
			tempMatr[i][j] = 1;
			for (int k = j + 1; k < n; k++) {
				if (sequence[j] < sequence[k]) {
					tempMatr[i][j] = max(tempMatr[i][j], tempMatr[i][k] + 1);
				}
				else if (i > 0) {
					tempMatr[i][j] = max(tempMatr[i][j], tempMatr[i - 1][k] + 1);
				}
			}
		}
	}

	int result = 0;
	for (int j = 0; j < n; j++) {
		result = max(result, tempMatr[m][j]);
	}

	fout << result;
	fout.close();

	for (int i = 0; i < m + 1; ++i) {
		delete[] tempMatr[i];
	}
	delete[] sequence;
	delete[] tempMatr;

	return 0;
}
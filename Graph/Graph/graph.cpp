#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n = 0, m = 0;
	fin >> n;
	fin >> m;

	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}

	int temp1, temp2;

	for (int i = 0; i < m; i++) {
		fin >> temp1;
		fin >> temp2;
		matrix[temp1-1][temp2-1] = 1;
		matrix[temp2-1][temp1-1] = 1;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fout << matrix[i][j] << " ";
		}
		fout << endl;
	}

	fout.close();
	fin.close();

	return 0;
}
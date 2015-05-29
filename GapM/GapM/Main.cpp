#include <fstream>
#include <iostream>

using namespace std;

int main() {
	int n, m;
	ifstream fin("input.txt");
	fin >> n >> m;

	int *A;
	A = new int[n];
	for (int i = 0; i < n; i++) {
		fin >> A[i];
	}
	fin.close();





	ofstream fout("output.txt");
	fout.close();
	return 0;
}
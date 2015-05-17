#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

int main() {
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	queue<int> queue;

	int n;
	fin >> n;

	for (int i = 0; i < n; i++) {
		queue.push(i);
	}

	int* res = new int[n];

	int temp = 0;
	int color = 0;
	while (!queue.empty()) {
		temp = queue.front();
		queue.pop();
		res[temp] = color;
		color = 1 - color;
		temp = queue.front();
		queue.pop();
		if (!queue.empty()) {
			queue.push(temp);
		} else {
			res[temp] = color;
		}
	}

	fout << res[0];

	for (int i = 1; i < n; i++) {
		fout << " " << res[i];
	}

	return 0;
}
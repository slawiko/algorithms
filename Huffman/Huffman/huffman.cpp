#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct Node {
	int number;
	long frequency;

	Node() {
		this->number = 0;
		this->frequency = 0;
	}
	Node(int number, long frequency) {
		this->number = number;
		this->frequency = frequency;
	}
};

int main() {
	int N;
	ifstream fin("huffman.in");
	fin >> N;

	queue<Node> nodes;
	int number;
	long frequency;
	for (int i = 0; i < N; i++) {
		fin >> frequency;
		number = i + 1;
		Node node(number, frequency);
		nodes.push(node);
	}








	ofstream fout("huffman.out");

	fout.close();
	return 0;
}
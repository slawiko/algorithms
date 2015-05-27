#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	int number;
	long long frequency;
	Node* left;
	Node* right;
	Node* father;

	Node() {
		this->number = 0;
		this->frequency = 0;
		this->left = NULL;
		this->right = NULL;
		this->father = NULL;
	}
	Node(long long frequency) {
		this->number = INT_MAX;
		this->frequency = frequency;
		this->left = NULL;
		this->right = NULL;
		this->father = NULL;
	}
	Node(int number, long long frequency) {
		this->number = number;
		this->frequency = frequency;
		this->left = NULL;
		this->right = NULL;
		this->father = NULL;
	}
	Node(int number, long long frequency, Node *left, Node *right) {
		this->number = number;
		this->frequency = frequency;
		this->left = left;
		this->right = right;
		this->father = NULL;
	}
};

struct LessThanByFrequency {
	bool operator()(const Node& first, const Node& second) const{
		if (first.frequency != second.frequency) {
			return first.frequency > second.frequency;
		} else {
			return first.number > second.number;
		}
	}
};

Node treeBuilding(priority_queue<Node, vector<Node>, LessThanByFrequency> nodes) {
	while (nodes.size() > 1) {
		Node left = nodes.top();
		nodes.pop();
		Node right = nodes.top();
		nodes.pop();
		Node *father = new Node(left.frequency + right.frequency);
		father->left = &left;
		father->right = &right;
		left.father = right.father = father;
		nodes.push(*father);
	}

	Node root = nodes.top();
	return root;
}

long long huffmanCodeLength(int height, Node *node) {
	long long length = 0;
	if (!node->left && !node->right) {
		length += height * node->frequency;
	}
	else if (!node->left) {
		length += huffmanCodeLength(height + 1, node->right);
	}
	else if (!node->right) {
		length += huffmanCodeLength(height + 1, node->left);
	}
	else {
		length += huffmanCodeLength(height + 1, node->left);
		length += huffmanCodeLength(height + 1, node->right);
	}
	return length;
}

int main() {
	int N;
	ifstream fin("huffman.in");
	fin >> N;

	priority_queue<Node, vector<Node>, LessThanByFrequency> nodes;
	int number;
	long long frequency;
	for (int i = 0; i < N; i++) {
		fin >> frequency;
		number = i + 1;
		nodes.push(Node(number, frequency));
	}
	fin.close();

	Node root = treeBuilding(nodes);
	long long result = huffmanCodeLength(0, &root);

	ofstream fout("huffman.out");
	fout << result;
	cout << result;
	fout.close();
	return 0;
}
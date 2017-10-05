#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	long long frequency;
	Node* left;
	Node* right;
	Node* father;

	Node() {
		this->frequency = 0;
		this->left = NULL;
		this->right = NULL;
		this->father = NULL;
	}
	Node(long long frequency) {
		this->frequency = frequency;
		this->left = NULL;
		this->right = NULL;
		this->father = NULL;
	}

	Node(long long frequency, Node *left, Node *right) {
		this->frequency = frequency;
		this->left = left;
		this->right = right;
		this->father = NULL;
	}
};

struct LessThanByFrequency {
	bool operator()(const Node& first, const Node& second) const{
		return first.frequency > second.frequency;
	}
};

Node treeBuilding(priority_queue<Node, vector<Node>, LessThanByFrequency> nodes) {
	while (nodes.size() > 1) {
		Node *left = new Node(nodes.top().frequency, nodes.top().left, nodes.top().right);
		nodes.pop();
		Node *right = new Node(nodes.top().frequency, nodes.top().left, nodes.top().right);
		nodes.pop();
		Node *father = new Node(left->frequency + right->frequency);
		father->left = left;
		father->right = right;
		left->father = right->father = father;
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
	long long frequency;
	for (int i = 0; i < N; i++) {
		fin >> frequency;
		nodes.push(Node(frequency));
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
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
	int number;
	long frequency;
	Node* left;
	Node* right;
	Node* father;
	int height;

	Node() {
		this->number = 0;
		this->frequency = 0;
		this->left = NULL;
		this->right = NULL;
		this->father = NULL;
		this->height = 0;
	}
	Node(long frequency) {
		this->number = INT_MAX;
		this->frequency = frequency;
		this->left = NULL;
		this->right = NULL;
		this->father = NULL;
		this->height = 0;
	}
	Node(int number, long frequency) {
		this->number = number;
		this->frequency = frequency;
		this->left = NULL;
		this->right = NULL;
		this->father = NULL;
		this->height = 0;
	}
	Node(int number, long frequency, Node *left, Node *right) {
		this->number = number;
		this->frequency = frequency;
		this->left = left;
		this->right = right;
		this->father = NULL;
		this->height = 0;
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
		Node *left = new Node(nodes.top().number, nodes.top().frequency, nodes.top().left, nodes.top().right);
		nodes.pop();
		Node *right = new Node(nodes.top().number, nodes.top().frequency, nodes.top().left, nodes.top().right);
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

int main() {
	int N;
	ifstream fin("huffman.in");
	fin >> N;

	priority_queue<Node, vector<Node>, LessThanByFrequency> nodes;
	int number;
	long frequency;
	for (int i = 0; i < N; i++) {
		fin >> frequency;
		number = i + 1;
		nodes.push(Node(number, frequency));
	}
	fin.close();

	Node root = treeBuilding(nodes);

	ofstream fout("huffman.out");
	int result = 0;
	fout << result;

	fout.close();
	return 0;
}
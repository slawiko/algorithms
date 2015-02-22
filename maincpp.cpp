#include <iostream>
#include <fstream>

using namespace std;

int ROOT = INT_MAX;
int INIT_HEIGHT = INT_MAX;

struct Node {

	int weight;
	int height;
	bool rightSon;
	bool leftSon;
	bool half_path;
	Node *right;
	Node *left;
	Node *father;
	
	Node() {

		this->weight = ROOT;
		this->height = INIT_HEIGHT;
		this->rightSon = false;
		this->leftSon = false;
		this->half_path = false;
		this->father = NULL;
		this->right = NULL;
		this->left = NULL;
	}

	Node(int weight) {

		this->weight = weight;
		this->height = INIT_HEIGHT;
		this->rightSon = false;
		this->leftSon = false;
		this->half_path = false;
		this->father = NULL;
		this->right = NULL;
		this->left = NULL;
	}
};

class Tree {

public:

	Node* root = new Node();
	int maxHalfPath = 0;

	void addNode(int addWeight, Node* node) {

		if (this->root->weight == ROOT) {

			this->root->weight = addWeight;
		}
		else if (addWeight > node->weight) {
				
			if (node->right != NULL)
				addNode(addWeight, node->right);
			else {

				Node* temp = new Node();
				node->right = temp;
				node->right->weight = addWeight;
				node->right->father = node;
				node->right->rightSon = true;
			}
		}
		else if (addWeight < node->weight) {

			if (node->left != NULL)
				addNode(addWeight, node->left);
			else {

				Node* temp = new Node();
				node->left = temp;
				node->left->weight = addWeight;
				node->left->father = node;
				node->left->leftSon = true;
			}
		}
		
		return;
	}

	void halfPath() {

		/*основной алгоритм*/
	}

	void rightDelete(int deleteWeight) {

		Node* tmp = new Node();
		tmp = findNode(deleteWeight, root);

		if (tmp == NULL)
			return;
		else if ((tmp->left == NULL) && (tmp->right == NULL)) {

			if (tmp->rightSon) {

				tmp->father->right = NULL;
				delete tmp;
			}
			else {

				tmp->father->left = NULL;
				delete tmp;
			}
		}
		else if ((tmp->left != NULL) && (tmp->right == NULL)) {

			if (tmp->leftSon) {

				tmp->father->left = tmp->left;
				tmp->left->father = tmp->father;
				delete tmp;
			}
			else if (tmp->rightSon) {

				tmp->father->right = tmp->left;
				tmp->left->father = tmp->father;
				delete tmp;
			}
		}
		else if ((tmp->left == NULL) && (tmp->right != NULL)) {

			if (tmp->leftSon) {

				tmp->father->left = tmp->right;
				tmp->right->father = tmp->father;
				delete tmp;
			}
			else if (tmp->rightSon) {

				tmp->father->right = tmp->right;
				tmp->right->father = tmp->father;
				delete tmp;
			}
		}
		else {

			Node* tmp2 = findLeft(tmp->right);
			int tempWeight = tmp2->weight;
			rightDelete(tmp2->weight);
			tmp->weight = tempWeight;
		}
	}

	void findMaxHalfPath() {

		maxHalfPath = this->heightNode(this->root);

		if ((root->right) && (root->left)) {
			if (root->right->height >= root->left->height)
				maxHalfPath += root->right->height;
			else
				maxHalfPath += root->left->height;
		}
	}

	void directLeftTraverseAndPrinting(ofstream& out, Node* node) {

		if (node) {

			out << node->weight << endl;
			directLeftTraverseAndPrinting(out, node->left);
			directLeftTraverseAndPrinting(out, node->right);
		}
	}

	int heightNode(Node* node) {

		if (node)
			return heightNode(node->right) >= heightNode(node->left) ? node->height = 1 + heightNode(node->right) : node->height = 1 + heightNode(node->left);
		else
			return -1;
	}

	Node*& findLeft(Node* node){

		if (node->left != NULL)
			return findLeft(node->left);
		else
			return node;
	}

	Node*& findNode(int findWeight, Node* node) {

		if (node == NULL)
			return node;
		else if (node->weight == findWeight)
			return node;
		else if (node->weight > findWeight)
			return findNode(findWeight, node->left);
		else 
			return findNode(findWeight, node->right);
	}
};

int main() {

	Tree tree;

 	ifstream fin("in.txt");
	ofstream fout("out.txt");

	int tmp = 0;

	while (!fin.eof()) {

		fin >> tmp;
		tree.addNode(tmp, tree.root);
	}

	tree.findMaxHalfPath();






	tree.directLeftTraverseAndPrinting(fout, tree.root);

	fin.close();
	fout.close();
	return 0;
}
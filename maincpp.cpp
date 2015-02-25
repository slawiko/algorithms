#include <iostream>
#include <fstream>

using namespace std;

int ROOT_INIT = INT_MAX;
int HEIGHT_INIT = 0;
int LEAVES_GAVES_HEIGHT_INIT = -1;
int MAX_PATH_COUNT_INIT = 0;


struct Node {

	int weight;
	int height;
	int leavesGavesHeight;
	int maxPathCount;
	bool rightSon;
	bool leftSon;
	bool halfPathRoot;
	Node *right;
	Node *left;
	Node *father;
	
	Node() {

		this->weight = ROOT_INIT;
		this->height = HEIGHT_INIT;
		this->leavesGavesHeight = LEAVES_GAVES_HEIGHT_INIT;
		this->maxPathCount = MAX_PATH_COUNT_INIT;
		this->rightSon = false;
		this->leftSon = false;
		this->halfPathRoot = false;
		this->father = NULL;
		this->right = NULL;
		this->left = NULL;
	}

	Node(int weight) {

		this->weight = weight;
		this->height = HEIGHT_INIT;
		this->leavesGavesHeight = LEAVES_GAVES_HEIGHT_INIT;
		this->maxPathCount = MAX_PATH_COUNT_INIT;
		this->rightSon = false;
		this->leftSon = false;
		this->halfPathRoot = false;
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

		if (this->root->weight == ROOT_INIT) {

			this->root->weight = addWeight;
		}
		else if (addWeight > node->weight) {
			
			if (node->right != NULL) {

				addNode(addWeight, node->right);
			}
			else {

				Node* temp = new Node();
				node->right = temp;
				node->right->weight = addWeight;
				node->right->father = node;
				node->right->rightSon = true;
			}
		}
		else if (addWeight < node->weight) {

			if (node->left != NULL) {

				addNode(addWeight, node->left);
			}
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

	void reverseLeftTraverse(Node* node) {

		if (node) {

			reverseLeftTraverse(node->left);
			reverseLeftTraverse(node->right);
			solve(node);
		}
	}

	void solve(Node* node) { //shitName

		if (node) {

			if (!node->left && !node->right) {

				node->height = 0;
				node->leavesGavesHeight = 1;
			}
			else if (node->left && !node->right) {

				node->height = node->left->height + 1;
				node->leavesGavesHeight = node->left->leavesGavesHeight;
			}
			else if (!node->left && node->right) {

				node->height = node->right->height + 1;
				node->leavesGavesHeight = node->right->leavesGavesHeight;
			}
			else {

				if (node->left->height > node->right->height) {

					node->height = node->left->height + 1;
					node->leavesGavesHeight = node->left->leavesGavesHeight;
				}
				else if (node->left->height == node->right->height) {

					node->height = node->left->height + 1;
					node->leavesGavesHeight = node->left->leavesGavesHeight + node->right->leavesGavesHeight;
				}
				else {

					node->height = node->right->height + 1;
					node->leavesGavesHeight = node->right->leavesGavesHeight;
				}
			}
		}
	}

	void rightDelete(int deleteWeight) {

		Node* tmp = new Node();
		tmp = findNode(deleteWeight, root);

		if (tmp == NULL) {

			return;
		}
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

	void directLeftTraversePrinting(ofstream& out, Node* node) {

		if (node) {

			out << node->weight << endl;
			directLeftTraversePrinting(out, node->left);
			directLeftTraversePrinting(out, node->right);
		}
	}

	int heightNode(Node* node) {

		if (node) {

			return heightNode(node->right) >= heightNode(node->left) ? node->height = 1 + heightNode(node->right) : node->height = 1 + heightNode(node->left);
		}
		else {

			return -1;
		}
	}

	Node*& findLeft(Node* node){

		if (node->left != NULL) {

			return findLeft(node->left);
		}
		else {

			return node;
		}
	}

	Node*& findNode(int findWeight, Node* node) {

		if (node == NULL) {

			return node;
		}
		else if (node->weight == findWeight) {

			return node;
		}
		else if (node->weight > findWeight) {

			return findNode(findWeight, node->left);
		}
		else {

			return findNode(findWeight, node->right);
		}
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


	tree.reverseLeftTraverse(tree.root);

	tree.directLeftTraversePrinting(fout, tree.root);

	fin.close();
	fout.close();
	return 0;
}
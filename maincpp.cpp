#include <iostream>
#include <fstream>

using namespace std;

int ROOT_INIT = INT_MAX;
int HEIGHT_INIT = 0;

struct Node {

	int weight;
	int height;
	bool rightSon;
	bool leftSon;
	bool halfPathRoot;
	bool halfPathNode;
	Node *right;
	Node *left;
	Node *father;
	
	Node() {

		this->weight = ROOT_INIT;
		this->height = HEIGHT_INIT;
		this->rightSon = false;
		this->leftSon = false;
		this->halfPathRoot = false;
		this->halfPathNode = false;
		this->father = NULL;
		this->right = NULL;
		this->left = NULL;
	}

	Node(int weight) {

		this->weight = weight;
		this->height = HEIGHT_INIT;
		this->rightSon = false;
		this->leftSon = false;
		this->halfPathRoot = false;
		this->halfPathNode = false;
		this->father = NULL;
		this->right = NULL;
		this->left = NULL;
	}
};

class Tree {

public:

	Node* root = new Node();
	int maxSumHeightSon = 0;
	int i = 0;   //фигня

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

	void reverseLeftTraverseHeight(Node* node) {

		if (node) {

			reverseLeftTraverseHeight(node->left);
			reverseLeftTraverseHeight(node->right);
			heightNode(node);
		}
	}

	void directLeftTraversePathNode(Node* node) {

		if (node) {

			if (!node->father && node->height >= maxSumHeightSon) {

				node->halfPathRoot = true;
				node->halfPathNode = true;

				pathNode(node->left);
				pathNode(node->right);
			}

			if (node->left && node->right) {

				if (node->left->height + node->right->height == maxSumHeightSon) {

					node->halfPathRoot = true;
					node->halfPathNode = true;

					pathNode(node->left);
					pathNode(node->right);
				}	
			}
			else if (!node->left && node->right) {

				if (node->right->height == maxSumHeightSon) {

					node->halfPathRoot = true;
					node->halfPathNode = true;

					pathNode(node->right);
				}
			}
			else if (node->left && !node->right) {

				if (node->left->height == maxSumHeightSon) {

					node->halfPathRoot = true;
					node->halfPathNode = true;

					pathNode(node->left);
				}
			}

			directLeftTraversePathNode(node->left);
			directLeftTraversePathNode(node->right);
		}
	}

	void pathNode(Node* node) {

		if (node) {

			node->halfPathNode = true;
			
			if (!node->left && !node->right) {

				return;
			}
			else if (!node->left && node->right) {

				pathNode(node->right);
			}
			else if (node->left && !node->right) {

				pathNode(node->left);
			}
			else {

				if (node->left->height > node->right->height) {

					pathNode(node->left);
				}
				else if (node->left->height < node->right->height) {

					pathNode(node->right);
				}
				else {

					pathNode(node->left);
					pathNode(node->right);
				}
			}
		}
	}

	void internalLeftTraverse(Node* node) {

		if (i < 2) {

			if (node) {

				bool flag = false;

				internalLeftTraverse(node->left);
				secondPlace(node);
				internalLeftTraverse(node->right);
			}
		}
	}

	void secondPlace(Node* node) {

		if (node->halfPathNode) {

			i++;
		}
		if (i == 2) {

			rightDelete(node->weight);
			return;
		}
	}

	void directLeftTraversePrinting(ofstream& out, Node* node) {

		if (node) {

			out << node->weight << endl;
			directLeftTraversePrinting(out, node->left);
			directLeftTraversePrinting(out, node->right);
		}
	}

	void heightNode(Node* node) {

		if (node) {

			if (!node->left && !node->right) {

				node->height = 0;
			}
			else if (node->left && !node->right) {

				node->height = node->left->height + 1;

				if ((node->left->height > maxSumHeightSon) && (node->father)) {

					maxSumHeightSon = node->left->height;
				}
			}
			else if (!node->left && node->right) {

				node->height = node->right->height + 1;

				if ((node->right->height > maxSumHeightSon) && (node->father)) {

					maxSumHeightSon = node->right->height;
				}
			}
			else {

				if (node->left->height > node->right->height) {

					node->height = node->left->height + 1;
				}
				else if (node->left->height == node->right->height) {

					node->height = node->left->height + 1;
				}
				else {

					node->height = node->right->height + 1;
				}

				if ((node->left->height + node->right->height > maxSumHeightSon) && (node->father)) {

					maxSumHeightSon = node->left->height + node->right->height;
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

	tree.reverseLeftTraverseHeight(tree.root);

	tree.directLeftTraversePathNode(tree.root);

	tree.internalLeftTraverse(tree.root);

	tree.directLeftTraversePrinting(fout, tree.root);

	fin.close();
	fout.close();
	return 0;
}
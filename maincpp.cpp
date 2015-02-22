#include <iostream>
#include <fstream>

using namespace std;

int ROOT = INT_MAX;
int ROOT_DEPTH = 0;
int INIT_DEPTH = -1;

struct Node {

	int weight;
	int depth;
	bool rightSon;
	bool leftSon;
	Node *right;
	Node *left;
	Node *father;
	
	Node() {

		this->weight = ROOT;
		this->depth = ROOT_DEPTH;
		this->rightSon = false;
		this->leftSon = false;
		this->father = NULL;
		this->right = NULL;
		this->left = NULL;
	}

	Node(int weight) {

		this->weight = weight;
		this->depth = INIT_DEPTH
			;
		this->rightSon = false;
		this->leftSon = false;
		this->father = NULL;
		this->right = NULL;
		this->left = NULL;
	}
};

class Tree {

public:

	Node* root = new Node();

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

	Node*& findLeft(Node* node){

		if (node->left != NULL)
			return findLeft(node->left);
		else
			return node;
	}

	void directLeftTraverse() {

		/*прямой левый обход*/
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
	int tmp = 0;

	while (!fin.eof()) {

		fin >> tmp;
		tree.addNode(tmp, tree.root);
	}

	//Node* node = new Node();

	tree.rightDelete(30);

	return 0;
}
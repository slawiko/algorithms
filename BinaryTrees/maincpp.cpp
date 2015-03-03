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
	int maxLength = 0;
	int place = 0;
	int deletedNode = 0;

	void addNode(int addWeight, Node* node) {

		if (this->root->weight == ROOT_INIT) {

			this->root->weight = addWeight;
			return;
		}

		if (addWeight > node->weight) {
			
			if (node->right) {

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

			if (node->left) {

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
	}

	void reverseLeftTraverseHeight(Node* node) {

		if (node) {

			reverseLeftTraverseHeight(node->left);
			reverseLeftTraverseHeight(node->right);
			heightNode(node);
		}
	}

	void heightNode(Node* node) {

		if (node) {

			if (!node->left && !node->right) {

				node->height = 0;
			}
			else if (node->left && !node->right) {

				node->height = node->left->height + 1;

				if (node->left->height + 1 > maxLength) {

					maxLength = node->left->height + 1;
				}
			}
			else if (!node->left && node->right) {

				node->height = node->right->height + 1;

				if (node->right->height + 1> maxLength) {

					maxLength = node->right->height + 1;
				}
			}
			else {

				if (node->left->height >= node->right->height) {

					node->height = node->left->height + 1;
				}
				else {

					node->height = node->right->height + 1;
				}

				if (node->left->height + node->right->height + 2 > maxLength) {

					maxLength = node->left->height + node->right->height + 2;
				}
			}
		}
	}

	void directLeftTraversePathNode(Node* node) {

		if (node) {

			if (node->left && node->right) {

				if (node->left->height + node->right->height + 2 == maxLength) {

					node->halfPathRoot = true;
					node->halfPathNode = true;
				}
				else if (node->father) {

					if (node->father->halfPathRoot) {

						node->halfPathNode = true;
					}
					else if (node->father->halfPathNode) {

						if (node->father->left && node->father->right) {

							if (node->father->left->height > node->father->right->height) {

								node->father->left->halfPathNode = true;
							}
							else if (node->father->left->height < node->father->right->height) {

								node->father->right->halfPathNode = true;
							}
							else {

								node->father->left->halfPathNode = true;
								node->father->right->halfPathNode = true;
							}
						}
						else if (node->father->left) {

							node->father->left->halfPathNode = true;
						}
						else if (node->father->right) {

							node->father->right->halfPathNode = true;
						}
					}
				}
			}
			else if (!node->left && node->right) {

				if (node->right->height + 1 == maxLength) {

					node->halfPathRoot = true;
					node->halfPathNode = true;
				}
				else if (node->father) {

					if (node->father->halfPathRoot) {

						node->halfPathNode = true;
					}
					else if (node->father->halfPathNode) {

						if (node->father->left && node->father->right) {

							if (node->father->left->height > node->father->right->height) {

								node->father->left->halfPathNode = true;
							}
							else if (node->father->left->height < node->father->right->height) {

								node->father->right->halfPathNode = true;
							}
							else {

								node->father->left->halfPathNode = true;
								node->father->right->halfPathNode = true;
							}
						}
						else if (node->father->left) {

							node->father->left->halfPathNode = true;
						}
						else if (node->father->right) {

							node->father->right->halfPathNode = true;
						}
					}
				}
			}
			else if (node->left && !node->right) {

				if (node->left->height + 1 == maxLength) {

					node->halfPathRoot = true;
					node->halfPathNode = true;
				}
				else if (node->father) {

					if (node->father->halfPathRoot) {

						node->halfPathNode = true;
					}
					else if (node->father->halfPathNode) {

						if (node->father->left && node->father->right) {

							if (node->father->left->height > node->father->right->height) {

								node->father->left->halfPathNode = true;
							}
							else if (node->father->left->height < node->father->right->height) {

								node->father->right->halfPathNode = true;
							}
							else {

								node->father->left->halfPathNode = true;
								node->father->right->halfPathNode = true;
							}
						}
						else if (node->father->left) {

							node->father->left->halfPathNode = true;
						}
						else if (node->father->right) {

							node->father->right->halfPathNode = true;
						}
					}
				}
			}
			else {

				if (node->father) {

					if (node->father->halfPathRoot) {

						node->halfPathNode = true;
					}
					else if (node->father->halfPathNode) {

						if (node->father->left && node->father->right) {

							if (node->father->left->height > node->father->right->height) {

								node->father->left->halfPathNode = true;
							}
							else if (node->father->left->height < node->father->right->height) {

								node->father->right->halfPathNode = true;
							}
							else {

								node->father->left->halfPathNode = true;
								node->father->right->halfPathNode = true;
							}
						}
						else if (node->father->left) {

							node->father->left->halfPathNode = true;
						}
						else if (node->father->right) {

							node->father->right->halfPathNode = true;
						}
					}
				}
			}

			directLeftTraversePathNode(node->left);
			directLeftTraversePathNode(node->right);
		}
	}

	void internalLeftTraverse(Node* node) {

		if (place < 2) {

			if (node) {

				internalLeftTraverse(node->left);

				if (node->halfPathNode) {

					place++;
				}
				if (place == 2) {

					deletedNode = node->weight;
				}

				internalLeftTraverse(node->right);
			}
		}
	}

	void rightDelete(int deleteWeight) {

		Node* tmp = new Node();
		tmp = findNode(deleteWeight, root);

		if (tmp == NULL) {

			return;
		}
		else if (!tmp->left && !tmp->right) {

			if (tmp->leftSon) {

				tmp->father->left = NULL;
				delete tmp;
			}
			else if (tmp->rightSon){

				tmp->father->right = NULL;
				delete tmp;
			}
		}
		else if (tmp->left && !tmp->right) {

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
		else if (!tmp->left && tmp->right) {

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

	Node*& findLeft(Node* node){

		if (node->left != NULL) {

			return findLeft(node->left);
		}
		else {

			return node;
		}
	}

	void directLeftTraversePrinting(ofstream& out, Node* node) {

		/*out << node->weight;
		if (node->left) {

			out << endl;
			directLeftTraversePrinting(out, node->left);
		}
		if (node->right) {

			out << endl;
			directLeftTraversePrinting(out, node->right);
		}*/

		if (node) {

			out << node->weight << endl;
			directLeftTraversePrinting(out, node->left);
			directLeftTraversePrinting(out, node->right);
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
	tree.rightDelete(tree.deletedNode);
	tree.directLeftTraversePrinting(fout, tree.root);

	fin.close();
	fout.close();
	return 0;
}
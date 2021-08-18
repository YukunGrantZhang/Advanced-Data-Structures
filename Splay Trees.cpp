/*
 * Splay Trees.cpp
 *
 *  Created on: 19 Jan 2021
 *      Author: Grant
 */

#include <iostream>
using namespace std;

class Node
{
public:
	int data;
	Node* parent = NULL;
	Node* left = NULL;
	Node* right = NULL;
};

class BinarySearchTree
{
public:
	Node* root;
	int height;
};

int found = 0;

Node* discover(Node* node, int value)
{
	if (node->data == value)
	{
		//found = 1;
		return node;
	}
	else
	{
		if (value < node->data)
		{
			discover(node->left, value);
		}
		else
		{
			discover(node->right, value);
		}
	}
}

void rotate(BinarySearchTree* tree, int value)
{
	Node* root = tree->root;

	Node* node = discover(root, value);

	if (node->parent == NULL)
	{
		return;
	}

	Node* parent = node->parent;

	if (parent->left == node)
	{
		if (parent->parent != NULL)
		{
			Node* parent_parent = parent->parent;

			if (parent_parent->left == parent)
			{
				node->parent = parent_parent;
				parent_parent->left = node;
			}
			else
			{
				node->parent = parent_parent;
				parent_parent->right = node;
			}

			parent->left = node->right;
			if (node->right != NULL)
			{
				node->right->parent = parent;
			}

			node->right = parent;
			parent->parent = node;
		}
		else
		{
			//cout << "HERE";

			node->parent = NULL;

			parent->left = node->right;
			if (node->right != NULL)
			{
				node->right->parent = parent;
			}

			node->right = parent;
			parent->parent = node;

			tree->root = node;

			//cout << root->data;
		}
	}
	else
	{
		if (parent->parent != NULL)
		{
			Node* parent_parent = parent->parent;

			if (parent_parent->left == parent)
			{
				node->parent = parent_parent;
				parent_parent->left = node;
			}
			else
			{
				node->parent = parent_parent;
				parent_parent->right = node;
			}

			parent->right = node->left;
			if (node->left != NULL)
			{
				node->left->parent = parent;
			}

			node->left = parent;
			parent->parent = node;
		}
		else
		{
			node->parent = NULL;

			parent->right = node->left;
			if (node->left != NULL)
			{
				node->left->parent = parent;
			}

			node->left = parent;
			parent->parent = node;

			tree->root = node;
		}
	}
}

void splay(BinarySearchTree* tree, int value)
{
	Node* root = tree->root;

	Node* node = discover(root, value);

	if (node == root)
	{
		return;
	}

	if (node->parent == root)
	{
		rotate(tree, value);
		return;
	}
	else
	{
		Node* parent = node->parent;
		Node* parent_parent = node->parent->parent;

		if (parent_parent->left == parent && parent->left == node)
		{
			//cout << "HERE";

			int y = parent->data;
			int x = node->data;

			rotate(tree, y);
			rotate(tree, x);
		}
		else if (parent_parent->right == parent && parent->right == node)
		{
			int y = parent->data;
			int x = node->data;

			rotate(tree, y);
			rotate(tree, x);
		}
		else
		{
			int x = node->data;

			rotate(tree, x);
			rotate(tree, x);
		}
	}

	splay(tree, value);
}

void delete_splay(BinarySearchTree* tree, int value)
{
	Node* root = tree->root;

	Node* node = discover(root, value);

	if (node->parent == root)
	{
		node->left = root->left;
		node->parent = NULL;

		tree->root = node;
		return;
	}
	else
	{
		Node* parent = node->parent;
		Node* parent_parent = node->parent->parent;

		if (parent_parent->left == parent && parent->left == node)
		{
			//cout << "HERE";

			int y = parent->data;
			int x = node->data;

			rotate(tree, y);
			rotate(tree, x);
		}
		else if (parent_parent->right == parent && parent->right == node)
		{
			int y = parent->data;
			int x = node->data;

			rotate(tree, y);
			rotate(tree, x);
		}
		else
		{
			int x = node->data;

			rotate(tree, x);
			rotate(tree, x);
		}
	}

	splay(tree, value);
}

void Insert(BinarySearchTree* tree, Node* node, int value)
{
	Node* root = tree->root;

	/*
	if (node == NULL)
	{
		Node* n = new Node();
		n->data = value;
		node = n;
		cout << "HERE";
		return;
	}
	*/

	if (value <= node->data)
	{
		if (node->left == NULL)
		{
			Node* n = new Node();
			n->parent = node;
			n->data = value;

			node->left = n;

			splay(tree, n->data);

			return;
		}
		else
		{
			Insert(tree, node->left, value);
		}
	}
	else
	{
		if (node->right == NULL)
		{
			Node* n = new Node();
			n->parent = node;
			n->data = value;

			node->right = n;

			splay(tree, n->data);

			return;
		}
		else
		{
			Insert(tree, node->right, value);
		}
	}
	return;
}

void find(BinarySearchTree* tree, Node* node, int value)
{
	if (node->data == value)
	{
		found = 1;
		splay(tree, value);
		return;
	}
	else
	{
		if (value < node->data)
		{
			find(tree, node->left, value);
		}
		else
		{
			find(tree, node->right, value);
		}
	}
}

void Delete(BinarySearchTree* tree, int value)
{
	//Node* root = tree->root;

	splay(tree, value);

	Node* root = tree->root;

	Node* r_minimum = tree->root->right;

	while (r_minimum->left != NULL)
	{
		r_minimum = r_minimum->left;
	}

	//cout << r_minimum->data;

	delete_splay(tree, r_minimum->data);
}

// Driver code
int main()
{
	BinarySearchTree* tree = new BinarySearchTree();
	tree->root = new Node();
	tree->root->data = 9;

	Insert(tree, tree->root, 8);
	Insert(tree, tree->root, 7);
	Insert(tree, tree->root, 6);
	Insert(tree, tree->root, 5);
	Insert(tree, tree->root, 4);
	Insert(tree, tree->root, 3);
	Insert(tree, tree->root, 2);
	Insert(tree, tree->root, 1);

	find(tree, tree->root, 5);

	Delete(tree, 6);

	cout << "The number " << 5 << " is in the tree is " << found;

    return 0;
}



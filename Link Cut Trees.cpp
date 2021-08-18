/*
 * Link Cut Trees.cpp
 *
 *  Created on: 2 Feb 2021
 *      Author: Grant
 */

#include <iostream>
using namespace std;

class Node
{
public:
	int data;
	int node_name;
	Node* parent = NULL;
	Node* left = NULL;
	Node* right = NULL;
};

class BinarySearchTree
{
public:
	BinarySearchTree* path_parent_tree = NULL;
	Node* path_parent = NULL;
	Node* root;
	int height;
};

class LinkCutTree
{
public:
	BinarySearchTree* root_tree;
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

void Insert(BinarySearchTree* tree, Node* node, int depth, int node_name)
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

	if (depth <= node->data)
	{
		if (node->left == NULL)
		{
			Node* n = new Node();
			n->parent = node;
			n->data = depth;
			n->node_name = node_name;

			node->left = n;

			splay(tree, n->data);

			return;
		}
		else
		{
			Insert(tree, node->left, depth, node_name);
		}
	}
	else
	{
		if (node->right == NULL)
		{
			Node* n = new Node();
			n->parent = node;
			n->data = depth;
			n->node_name = node_name;

			node->right = n;

			splay(tree, n->data);

			return;
		}
		else
		{
			Insert(tree, node->right, depth, node_name);
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

Node* search(BinarySearchTree* tree, Node* node, int value)
{
	if (node->data == value)
	{
		//found = 1;
		//splay(tree, value);
		return node;
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

void join(BinarySearchTree* tree1, BinarySearchTree* tree2)
{
	int target_height = tree2->height - 1;

	Node* parent_node = search(tree1, tree1->root, target_height);

	tree2->path_parent_tree = tree1;
	tree2->path_parent = parent_node;

	cout << parent_node->data << endl;
}

BinarySearchTree* access_tree = NULL;

void access(BinarySearchTree* tree, int v)
{
	splay(tree, v);

	cout << "Splay" << tree->root->data << endl;

	if (tree->root->right != NULL)
	{
		BinarySearchTree* new_tree = new BinarySearchTree();
		new_tree->height = tree->root->right->data;
		new_tree->root = tree->root->right;
		new_tree->root->parent = NULL;
		new_tree->path_parent = tree->root;
		new_tree->path_parent_tree = tree;

		tree->root->right = NULL;

		access_tree = new_tree;
	}

	Node* w = tree->path_parent;
	BinarySearchTree* w_tree = tree->path_parent_tree;
	//Node* v_node = tree->root;
	BinarySearchTree* v_tree = tree;

	//int r = 0;
	while (w != NULL)
	{
		splay(w_tree, w->data);

		BinarySearchTree* new_new_tree = new BinarySearchTree();
		new_new_tree->height = w_tree->root->right->data;
		new_new_tree->root = w_tree->root->right;
		new_new_tree->root->parent = NULL;
		new_new_tree->path_parent = w_tree->root;
		new_new_tree->path_parent_tree = w_tree;

		access_tree = new_new_tree;

		//w_tree->root->right = v_node;
		w_tree->root->right = v_tree->root;
		w_tree->root->right->parent = w_tree->root;
		v_tree->path_parent = NULL;;
		v_tree->path_parent_tree = NULL;

		splay(w_tree, w_tree->root->right->data);

		w = w_tree->path_parent;
		w_tree = w_tree->path_parent_tree;
		//v_node = w_tree->root;
		v_tree = w_tree;

		//r++;
	}
}

void findroot(BinarySearchTree* base_tree, BinarySearchTree* target_tree, int v)
{
	access(target_tree, v);

	Node* current_node = base_tree->root;

	while (current_node->left != NULL)
	{
		current_node = current_node->left;
	}

	splay(base_tree, current_node->data);
}

void inordertraversal(Node* current_node)
{
	if (current_node == NULL)
	{
		return;
	}

	inordertraversal(current_node->left);

	cout << current_node->data << endl;

	inordertraversal(current_node->right);
}

void mincapacity(BinarySearchTree* base_tree, BinarySearchTree* target_tree, int v)
{
	access(target_tree, v);

	inordertraversal(base_tree->root);
}

void cut(BinarySearchTree* base_tree, BinarySearchTree* target_tree, int v)
{
	access(target_tree, v);

	cout << base_tree->root->data << endl;

	base_tree->root->left->parent = NULL;
	base_tree->root->left = NULL;
}

void link(LinkCutTree* overall_tree, LinkCutTree* overall_tree1, BinarySearchTree* target_tree1, BinarySearchTree* target_tree2, int w, int v)
{
	access(target_tree2, v);
	access(target_tree1, w);

	target_tree1->path_parent_tree = target_tree2;

	Node* current_node = target_tree2->root;

	while (current_node->left != NULL)
	{
		current_node = current_node->left;
	}

	splay(target_tree1, current_node->data + 1); //Sets tree heights to ensure balance

	target_tree1->root->left->parent = NULL; //Deletes values shallower than the root
	target_tree1->root->left = NULL; //Deletes values shallower than the root

	target_tree1->path_parent = current_node;
}
// Driver code
int main()
{
	LinkCutTree* overall_tree = new LinkCutTree();

	BinarySearchTree* tree1 = new BinarySearchTree();
	tree1->height = 0;
	tree1->root = new Node();
	tree1->root->data = 2;
	tree1->root->node_name = 1;
	Insert(tree1, tree1->root, 3, 0);
	Insert(tree1, tree1->root, 1, 3);
	Insert(tree1, tree1->root, 0, 5);

	overall_tree->root_tree = tree1;

	BinarySearchTree* tree2 = new BinarySearchTree();
	tree2->height = 1;
	tree2->root = new Node();
	tree2->root->data = 2;
	tree2->root->node_name = 2;
	Insert(tree2, tree2->root, 3, 0);
	Insert(tree2, tree2->root, 1, 4);

	join(tree1, tree2);



	LinkCutTree* overall_tree1 = new LinkCutTree();

	BinarySearchTree* tree3 = new BinarySearchTree();
	tree3->height = 0;
	tree3->root = new Node();
	tree3->root->data = 2;
	tree3->root->node_name = 1;
	Insert(tree3, tree3->root, 3, 0);
	Insert(tree3, tree3->root, 1, 3);
	Insert(tree3, tree3->root, 0, 5);

	overall_tree->root_tree = tree3;

	BinarySearchTree* tree4 = new BinarySearchTree();
	tree4->height = 2;
	tree4->root = new Node();
	tree4->root->data = 2;
	tree4->root->node_name = 7;
	Insert(tree4, tree4->root, 3, 0);

	join(tree3, tree4);

	//access(tree4, 3);

	//access(tree2, 3);

	//findroot(tree1, tree2, 3);

	//mincapacity(tree1, tree2, 3);

	//cut(tree1, tree2, 3);

	link(overall_tree, overall_tree1, tree2, tree4, 3, 3);

	//find(tree, tree->root, 1);

	//Delete(tree, 6);

	//cout << "The depth " << 1 << " is in the tree is " << found;

	cout << "HERE" << endl;

    return 0;
}



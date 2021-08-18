/*
 * B Tree.cpp
 *
 *  Created on: 24 Mar 2021
 *      Author: Grant
 */

#include <iostream>

using namespace std;

#define N 5

class Leaves {
  public:
	Leaves* parent;

	Leaves* leaves_array[N];
	int numbers_array[N - 1];

	Leaves() {
		parent = NULL;

		for (int i = 0; i < N; i++)
		{
			leaves_array[i] = NULL;
		}

		for (int j = 0; j < N - 1; j++)
		{
			numbers_array[j] = 0;
		}
	}
};

class Tree {
  public:
    Leaves* root;

    Tree() {
    	root = NULL;
    }
};

void propagate_up(Tree* tree, Leaves* leaf, int value)
{
	int array[N];

	int count = N - 1;

	bool insert = false;
	for (int a = N - 2; a >= 0; a--)
	{
		if (a == 0 && insert == false)
		{
			array[count] = leaf->numbers_array[a];

			count--;
			array[count] = value;
			break;
		}

		if (value >= leaf->numbers_array[a] && insert == false)
		{
			array[count] = value;
			count--;
			a++;

			insert = true;
		}
		else
		{
			array[count] = leaf->numbers_array[a];
			count--;
		}
	}

	for (int b = 0; b < N; b++)
	{
		cout << array[b] << endl;
	}

	int median_index;

	if (N % 2 != 0)
	{
		median_index = N / 2;
	}
	else
	{
		median_index = (N - 1) / 2;
	}

	cout << "Median 1 is " << array[median_index] << endl;

	int left[N - 1];
	int middle[N - 1];
	int right[N - 1];

	for (int c = 0; c < N - 1; c++)
	{
		left[c] = 0;
		middle[c] = 0;
		right[c] = 0;
	}

	int count_left = 0;
	int count_middle = 0;
	int count_right = 0;
	for (int d = 0; d < N; d++)
	{
		if (d < median_index)
		{
			left[count_left] = array[d];
			count_left++;
		}

		if (d == median_index)
		{
			middle[count_middle] = array[d];
			count_middle++;
		}

		if (d > median_index)
		{
			right[count_right] = array[d];
			count_right++;
		}
	}

	int upward_number = array[median_index];






	int upper_array[N];

	int upper_count = N - 1;

	bool upper_insert = false;
	for (int a1 = N - 2; a1 >= 0; a1--)
	{
		if (a1 == 0 && upper_insert == false)
		{
			upper_array[upper_count] = leaf->parent->numbers_array[a1];

			upper_count--;
			upper_array[upper_count] = upward_number;
			break;
		}

		if (upward_number >= leaf->parent->numbers_array[a1] && upper_insert == false)
		{
			upper_array[upper_count] = upward_number;
			upper_count--;
			a1++;

			upper_insert = true;
		}
		else
		{
			upper_array[upper_count] = leaf->parent->numbers_array[a1];
			upper_count--;
		}
	}

	cout << endl;
	for (int b1 = 0; b1 < N; b1++)
	{
		cout << upper_array[b1] << endl;
	}

	int upper_median_index;

	if (N % 2 != 0)
	{
		upper_median_index = N / 2;
	}
	else
	{
		upper_median_index = (N - 1) / 2;
	}

	cout << "Median 2 is " << upper_array[upper_median_index] << endl;

	int upper_left[N - 1];
	int upper_middle[N - 1];
	int upper_right[N - 1];

	for (int c1 = 0; c1 < N - 1; c1++)
	{
		upper_left[c1] = 0;
		upper_middle[c1] = 0;
		upper_right[c1] = 0;
	}

	int upper_count_left = 0;
	int upper_count_middle = 0;
	int upper_count_right = 0;
	for (int d1 = 0; d1 < N; d1++)
	{
		if (d1 < upper_median_index)
		{
			upper_left[upper_count_left] = upper_array[d1];
			upper_count_left++;
		}

		if (d1 == upper_median_index)
		{
			upper_middle[upper_count_middle] = upper_array[d1];
			upper_count_middle++;
		}

		if (d1 > upper_median_index)
		{
			upper_right[upper_count_right] = upper_array[d1];
			upper_count_right++;
		}
	}

	if (leaf->parent->parent == NULL)
	{
		Leaves* upper_leaf = new Leaves();

		upper_leaf->numbers_array[0] = upper_middle[0];

		Leaves* upper_leaf_left = new Leaves();
		Leaves* upper_leaf_right = new Leaves();

		for (int i = 0; i < upper_count_left; i++)
		{
			upper_leaf_left->numbers_array[i] = upper_left[i];
		}

		for (int j = 0; j < upper_count_right; j++)
		{
			upper_leaf_right->numbers_array[j] = upper_right[j];
		}

		upper_leaf->leaves_array[0] = upper_leaf_left;
		upper_leaf->leaves_array[1] = upper_leaf_right;

		upper_leaf_left->parent = upper_leaf;
		upper_leaf_right->parent = upper_leaf;

		int upper_left_index_count = 0;
		int upper_right_index_count = 0;

		for (int k = 0; k < N; k++)
		{
			if (k <= upper_median_index)
			{
				if (leaf->parent->leaves_array[k]->numbers_array[0] == left[0])
				{
					Leaves* new_left = new Leaves();
					Leaves* new_right = new Leaves();

					for (int k1 = 0; k1 < count_left; k1++)
					{
						new_left->numbers_array[k1] = left[k1];
					}

					for (int k2 = 0; k2 < count_right; k2++)
					{
						new_right->numbers_array[k2] = right[k2];
					}

					upper_leaf_left->leaves_array[upper_left_index_count] = new_left;
					upper_left_index_count++;
					upper_leaf_left->leaves_array[upper_left_index_count] = new_right;
					upper_left_index_count++;

					new_left->parent = upper_leaf_left;
					new_right->parent = upper_leaf_left;

					continue;
				}

				upper_leaf_left->leaves_array[upper_left_index_count] = leaf->parent->leaves_array[k];
				upper_left_index_count++;

				leaf->parent->leaves_array[k]->parent = upper_leaf_left;
			}
			else
			{
				if (leaf->parent->leaves_array[k]->numbers_array[0] == left[0])
				{
					Leaves* new_left = new Leaves();
					Leaves* new_right = new Leaves();

					for (int k1 = 0; k1 < count_left; k1++)
					{
						new_left->numbers_array[k1] = left[k1];
					}

					for (int k2 = 0; k2 < count_right; k2++)
					{
						new_right->numbers_array[k2] = right[k2];
					}

					upper_leaf_right->leaves_array[upper_right_index_count] = new_left;
					upper_right_index_count++;
					upper_leaf_right->leaves_array[upper_right_index_count] = new_right;
					upper_right_index_count++;

					new_left->parent = upper_leaf_right;
					new_right->parent = upper_leaf_right;

					continue;
				}

				upper_leaf_right->leaves_array[upper_right_index_count] = leaf->parent->leaves_array[k];
				upper_right_index_count++;

				leaf->parent->leaves_array[k]->parent = upper_leaf_right;
			}
		}

		tree->root = upper_leaf;
	}
	else
	{
		Leaves* upper = leaf->parent->parent;

		int position;

		for (int x = 0; x < N - 1; x++)
		{
			if (upper_middle[0] < upper->numbers_array[x])
			{
				for (int x1 = N - 2; x1 > x; x1--)
				{
					upper->numbers_array[x1] = upper->numbers_array[x1 - 1];
				}

				for (int x2 = N - 1; x2 > x + 1 ; x2--)
				{
					upper->leaves_array[x2] = upper->leaves_array[x2 - 1];
				}

				position = x;
				break;
			}

			if (upper->numbers_array[x] == 0)
			{
				position = x;
				break;
			}
		}

		Leaves* left_position = upper->leaves_array[position];
		Leaves* right_position = upper->leaves_array[position + 1];

		Leaves* upper_leaf_left = new Leaves();
		Leaves* upper_leaf_right = new Leaves();

		for (int i = 0; i < upper_count_left; i++)
		{
			upper_leaf_left->numbers_array[i] = upper_left[i];
		}

		for (int j = 0; j < upper_count_right; j++)
		{
			upper_leaf_right->numbers_array[j] = upper_right[j];
		}

		upper->leaves_array[position] = upper_leaf_left;
		upper->leaves_array[position + 1] = upper_leaf_right;

		upper_leaf_left->parent = upper;
		upper_leaf_right->parent = upper;

		int upper_left_index_count = 0;
		int upper_right_index_count = 0;

		for (int k = 0; k < N; k++)
		{
			if (k <= upper_median_index)
			{
				if (leaf->parent->leaves_array[k]->numbers_array[0] == left[0])
				{
					Leaves* new_left = new Leaves();
					Leaves* new_right = new Leaves();

					for (int k1 = 0; k1 < count_left; k1++)
					{
						new_left->numbers_array[k1] = left[k1];
					}

					for (int k2 = 0; k2 < count_right; k2++)
					{
						new_right->numbers_array[k2] = right[k2];
					}

					upper_leaf_left->leaves_array[upper_left_index_count] = new_left;
					upper_left_index_count++;
					upper_leaf_left->leaves_array[upper_left_index_count] = new_right;
					upper_left_index_count++;

					new_left->parent = upper_leaf_left;
					new_right->parent = upper_leaf_left;

					continue;
				}

				upper_leaf_left->leaves_array[upper_left_index_count] = leaf->parent->leaves_array[k];
				upper_left_index_count++;

				leaf->parent->leaves_array[k]->parent = upper_leaf_left;
			}
			else
			{
				if (leaf->parent->leaves_array[k]->numbers_array[0] == left[0])
				{
					Leaves* new_left = new Leaves();
					Leaves* new_right = new Leaves();

					for (int k1 = 0; k1 < count_left; k1++)
					{
						new_left->numbers_array[k1] = left[k1];
					}

					for (int k2 = 0; k2 < count_right; k2++)
					{
						new_right->numbers_array[k2] = right[k2];
					}

					upper_leaf_right->leaves_array[upper_right_index_count] = new_left;
					upper_right_index_count++;
					upper_leaf_right->leaves_array[upper_right_index_count] = new_right;
					upper_right_index_count++;

					new_left->parent = upper_leaf_right;
					new_right->parent = upper_leaf_right;

					continue;
				}

				upper_leaf_right->leaves_array[upper_right_index_count] = leaf->parent->leaves_array[k];
				upper_right_index_count++;

				leaf->parent->leaves_array[k]->parent = upper_leaf_right;
			}
		}
	}

}

void insert_leaves(Tree* tree, Leaves* leaf, int value)
{
	cout << "INSERT LEAVES" << endl;

	bool integer_full = true;
	bool leaves_empty = true;

	for (int i = 0; i < N - 1; i++)
	{
		if (leaf->numbers_array[i] == 0)
		{
			integer_full = false;
		}
	}

	for (int j = 0; j < N; j++)
	{
		if (leaf->leaves_array[j] != NULL)
		{
			leaves_empty = false;
		}
	}

	if (leaves_empty == false)
	{
		cout << "LEAVES EMPTY" << endl;
		for (int a = 0; a < N - 1; a++)
		{
			if (leaf->numbers_array[a] == 0)
			{
				insert_leaves(tree, leaf->leaves_array[a], value);
				//cout << "Leaf " << a << endl;
				break;
			}

			if (value < leaf->numbers_array[a])
			{
				insert_leaves(tree, leaf->leaves_array[a], value);
				//cout << "Leaf " << a << endl;
				break;
			}
		}
	}

	if (integer_full == false && leaves_empty == true)
	{
		cout << "INSERT NUMBERS" << endl;

		for (int y = 0; y < N - 1; y++)
		{
			cout << leaf->numbers_array[y] << endl;
		}

		for (int a = 0; a < N - 1; a++)
		{
			if (value >= leaf->numbers_array[a])
			{
				if (leaf->numbers_array[a] == 0)
				{
					leaf->numbers_array[a] = value;
					break;
				}

				if (a < N - 1)
				{
					if (leaf->numbers_array[a + 1] == 0)
					{
						leaf->numbers_array[a + 1] = value;
						break;
					}
				}

				if (a < N - 1)
				{
					if (value < leaf->numbers_array[a + 1])
					{
						//cout << "HERE" << value << endl;

						for (int a1 = N - 1; a1 > a + 1; a1--)
						{
							leaf->numbers_array[a1] = leaf->numbers_array[a1 - 1];
						}

						leaf->numbers_array[a + 1] = value;

						break;
					}
				}
			}

			if (a == 0)
			{
				if (value < leaf->numbers_array[a])
				{
					//cout << "Here" << value << endl;

					for (int a1 = N - 1; a1 > a; a1--)
					{
						leaf->numbers_array[a1] = leaf->numbers_array[a1 - 1];

					}

					leaf->numbers_array[a] = value;

					break;
				}
			}
		}
	}

	bool parent_full = true;

	for (int k = 0; k < N - 1; k++)
	{
		if (leaf->parent->numbers_array[k] == 0)
		{
			parent_full = false;
		}
	}

	//cout << "PARENT" << endl;

	if (integer_full == true && leaves_empty == true && parent_full == true)
	{
		//cout << "HERE" << endl;
		propagate_up(tree, leaf, value);
	}

	if (integer_full == true && leaves_empty == true && parent_full == false)
	{
		int array[N];

		int count = N - 1;

		bool insert = false;
		for (int a = N - 2; a >= 0; a--)
		{
			if (a == 0 && insert == false)
			{
				array[count] = leaf->numbers_array[a];

				count--;
				array[count] = value;
				break;
			}

			if (value >= leaf->numbers_array[a] && insert == false)
			{
				array[count] = value;
				count--;
				a++;

				insert = true;
			}
			else
			{
				array[count] = leaf->numbers_array[a];
				count--;
			}
		}

		for (int b = 0; b < N; b++)
		{
			cout << array[b] << endl;
		}

		int median_index;

		if (N % 2 != 0)
		{
			median_index = N / 2;
		}
		else
		{
			median_index = (N - 1) / 2;
		}

		cout << "Median Index is " << median_index << endl;

		int left[N - 1];
		int middle[N - 1];
		int right[N - 1];

		for (int c = 0; c < N - 1; c++)
		{
			left[c] = 0;
			middle[c] = 0;
			right[c] = 0;
		}

		int count_left = 0;
		int count_middle = 0;
		int count_right = 0;
		for (int d = 0; d < N; d++)
		{
			if (d < median_index)
			{
				left[count_left] = array[d];
				count_left++;
			}

			if (d == median_index)
			{
				middle[count_middle] = array[d];
				count_middle++;
			}

			if (d > median_index)
			{
				right[count_right] = array[d];
				count_right++;
			}
		}

		Leaves* middle_leaves = new Leaves();
		Leaves* left_leaves = new Leaves();
		Leaves* right_leaves = new Leaves();

		for (int e = 0; e < N - 1; e++)
		{
			if (middle[0] < leaf->parent->numbers_array[e])
			{
				for (int e1 = N - 2; e1 > e ; e1--)
				{
					leaf->parent->numbers_array[e1] = leaf->parent->numbers_array[e1 - 1];
				}

				for (int e2 = N - 1; e2 > e + 1 ; e2--)
				{
					leaf->parent->leaves_array[e2] = leaf->parent->leaves_array[e2 - 1];
				}

				leaf->parent->numbers_array[e] = middle[0];
				leaf->parent->leaves_array[e] = left_leaves;
				leaf->parent->leaves_array[e + 1] = right_leaves;

				for (int e3 = 0; e3 < count_left; e3++)
				{
					left_leaves->numbers_array[e3] = left[e3];
				}

				for (int e4 = 0; e4 < count_right; e4++)
				{
					right_leaves->numbers_array[e4] = right[e4];
				}

				leaf->parent->leaves_array[e]->parent = leaf->parent;
				leaf->parent->leaves_array[e + 1]->parent = leaf->parent;

				break;
			}

			if (leaf->parent->numbers_array[e] == 0)
			{
				leaf->parent->numbers_array[e] = middle[0];
				leaf->parent->leaves_array[e] = left_leaves;
				leaf->parent->leaves_array[e + 1] = right_leaves;

				for (int e3 = 0; e3 < count_left; e3++)
				{
					left_leaves->numbers_array[e3] = left[e3];
				}

				for (int e4 = 0; e4 < count_right; e4++)
				{
					right_leaves->numbers_array[e4] = right[e4];
				}

				leaf->parent->leaves_array[e]->parent = leaf->parent;
				leaf->parent->leaves_array[e + 1]->parent = leaf->parent;

				break;
			}
		}
	}

}

void insert_tree(Tree* tree, int value)
{
	bool integer_full = true;
	bool leaves_empty = true;

	for (int i = 0; i < N - 1; i++)
	{
		if (tree->root->numbers_array[i] == 0)
		{
			integer_full = false;
		}
	}

	for (int j = 0; j < N; j++)
	{
		if (tree->root->leaves_array[j] != NULL)
		{
			leaves_empty = false;
		}
	}

	if (leaves_empty == false)
	{
		for (int a = 0; a < N - 1; a++)
		{
			if (tree->root->numbers_array[a] == 0)
			{
				insert_leaves(tree, tree->root->leaves_array[a], value);
				//cout << "Leaf " << a << endl;
				break;
			}

			if (value < tree->root->numbers_array[a])
			{
				insert_leaves(tree, tree->root->leaves_array[a], value);
				//cout << "Leaf " << a << endl;
				break;
			}
		}
	}

	if (integer_full == false && leaves_empty == true)
	{
	for (int a = 0; a < N - 1; a++)
	{
		if (value >= tree->root->numbers_array[a])
		{
			if (tree->root->numbers_array[a] == 0)
			{
				tree->root->numbers_array[a] = value;
				break;
			}

			if (a < N - 1)
			{
				if (tree->root->numbers_array[a + 1] == 0)
				{
					tree->root->numbers_array[a + 1] = value;
					break;
				}
			}

			if (a < N - 1)
			{
				if (value < tree->root->numbers_array[a + 1])
				{
					//cout << "HERE" << value << endl;

					for (int a1 = N - 1; a1 > a + 1; a1--)
					{
						tree->root->numbers_array[a1] = tree->root->numbers_array[a1 - 1];
					}

					tree->root->numbers_array[a + 1] = value;

					break;
				}
			}
		}

		if (a == 0)
		{
			if (value < tree->root->numbers_array[a])
			{
				//cout << "Here" << value << endl;

				for (int a1 = N - 1; a1 > a; a1--)
				{
					tree->root->numbers_array[a1] = tree->root->numbers_array[a1 - 1];

				}

				tree->root->numbers_array[a] = value;

				break;
			}
		}
	}
	}

	if (integer_full == true && leaves_empty == true)
	{
		int array[N];

		int count = N - 1;

		bool insert = false;
		for (int a = N - 2; a >= 0; a--)
		{
			if (a == 0 && insert == false)
			{
				array[count] = tree->root->numbers_array[a];

				count--;
				array[count] = value;
				break;
			}

			if (value >= tree->root->numbers_array[a] && insert == false)
			{
				array[count] = value;
				count--;
				a++;

				insert = true;
			}
			else
			{
				array[count] = tree->root->numbers_array[a];
				count--;
			}
		}

		for (int b = 0; b < N; b++)
		{
			cout << array[b] << endl;
		}

		int median_index;

		if (N % 2 != 0)
		{
			median_index = N / 2;
		}
		else
		{
			median_index = (N - 1) / 2;
		}

		cout << "Median Index is " << median_index << endl;

		int left[N - 1];
		int middle[N - 1];
		int right[N - 1];

		for (int c = 0; c < N - 1; c++)
		{
			left[c] = 0;
			middle[c] = 0;
			right[c] = 0;
		}

		int count_left = 0;
		int count_middle = 0;
		int count_right = 0;
		for (int d = 0; d < N; d++)
		{
			if (d < median_index)
			{
				left[count_left] = array[d];
				count_left++;
			}

			if (d == median_index)
			{
				middle[count_middle] = array[d];
				count_middle++;
			}

			if (d > median_index)
			{
				right[count_right] = array[d];
				count_right++;
			}
		}

		Leaves* new_root = new Leaves();
		Leaves* left_leaves = new Leaves();
		Leaves* right_leaves = new Leaves();

		new_root->numbers_array[0] = middle[0];
		new_root->leaves_array[0] = left_leaves;
		new_root->leaves_array[1] = right_leaves;

		for (int e1 = 0; e1 < count_left; e1++)
		{
			left_leaves->numbers_array[e1] = left[e1];
		}

		for (int e2 = 0; e2 < count_right; e2++)
		{
			right_leaves->numbers_array[e2] = right[e2];
		}

		new_root->leaves_array[0]->parent = new_root;
		new_root->leaves_array[1]->parent = new_root;
		tree->root = new_root;
	}
}

int main()
{
	Tree* newtree = new Tree();
	Leaves* newleaf = new Leaves();

	newtree->root = newleaf;

	insert_tree(newtree, 1);
	insert_tree(newtree, 2);
	insert_tree(newtree, 9);
	insert_tree(newtree, 10);

	cout << newtree->root->numbers_array[0] << endl;
	cout << newtree->root->numbers_array[1] << endl;
	cout << newtree->root->numbers_array[2] << endl;
	cout << newtree->root->numbers_array[3] << endl;
	cout << endl;

	insert_tree(newtree, 11);

	cout << newtree->root->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[0]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[0] << endl;
	cout << endl;

	insert_tree(newtree, 3);
	insert_tree(newtree, 4);
	insert_tree(newtree, 5);

	cout << newtree->root->leaves_array[1]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[1] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[2] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[3] << endl;
	cout << endl;

	insert_tree(newtree, 6);
	insert_tree(newtree, 8);

	cout << newtree->root->leaves_array[1]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[1] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[2] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[3] << endl;
	cout << endl;

	insert_tree(newtree, 7);

	cout << newtree->root->leaves_array[1]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[1] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[2] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[3] << endl;
	cout << endl;

	insert_tree(newtree, 18);
	insert_tree(newtree, 19);
	insert_tree(newtree, 20);

	cout << newtree->root->leaves_array[4]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[4]->numbers_array[1] << endl;
	cout << newtree->root->leaves_array[4]->numbers_array[2] << endl;
	cout << newtree->root->leaves_array[4]->numbers_array[3] << endl;
	cout << endl;

	insert_tree(newtree, 12);
	insert_tree(newtree, 14);
	insert_tree(newtree, 15);

	cout << "HERE" << endl;

	cout << newtree->root->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[0]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[0]->numbers_array[1] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[1]->numbers_array[1] << endl;
	cout << newtree->root->leaves_array[0]->leaves_array[0]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[0]->leaves_array[1]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[0]->leaves_array[2]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[1]->leaves_array[0]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[1]->leaves_array[1]->numbers_array[0] << endl;
	cout << newtree->root->leaves_array[1]->leaves_array[2]->numbers_array[0] << endl;


	return 0;
}



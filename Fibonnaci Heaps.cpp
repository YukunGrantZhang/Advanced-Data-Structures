/*
 * Fibonnaci Heaps.cpp
 *
 *  Created on: 18 Jan 2021
 *      Author: Grant
 */

#include <iostream>
using namespace std;

class Node
{
    public:
    int data;
    int rank;
	Node* parent;
    Node* child;
    Node* right;
    Node* left;
};

void printList(Node* node)
{
    Node* last;
    cout<<"\nTraversal in forward direction \n";
    while (node != NULL)
    {
        cout<<"Node: "<<node->data<<" Rank: " << node->rank <<endl;
        last = node;
        node = node->right;
    }
    cout << endl;
}

Node* chosen_node = NULL;

void bubbleup(Node* node)
{
	int temp;

	if (node->parent != NULL)
	{
		if (node->data < node->parent->data)
		{
			temp = node->parent->data;
			node->parent->data = node->data;
			node->data = temp;

			bubbleup(node->parent);
		}
	}

	return;
}

void update(Node* node, int original_value, int new_value)
{
	if (node->data == original_value)
	{
		//chosen_node = node;
		node->data = new_value;
		bubbleup(node);
		return;
	}

	if (node->child != NULL)
	{
		if (node->child->data == original_value)
		{
			//chosen_node = node->child;
			node->child->data = new_value;
			bubbleup(node->child);
			return;
		}
		else
		{
			update(node->child, original_value, new_value);
		}
	}

	if (node->right != NULL)
	{
		if (node->right->data == original_value)
		{
			//chosen_node = node->right;
			node->right->data = new_value;
			bubbleup(node->right);
			return;
		}
		else
		{
			update(node->right, original_value, new_value);
		}
	}

	return;
}

void insert(Node** head_ref, int new_data)
{
	Node* new_node = new Node();

	Node* last = *head_ref;

	new_node->data = new_data;
	new_node->rank = 0;
	new_node->parent = NULL;
	new_node->child = NULL;
	new_node->right = NULL;

	if (*head_ref == NULL)
	{
		new_node->left = NULL;
	    *head_ref = new_node;
	    return;
	}

	while (last->right != NULL)
	{
		last = last->right;
	}

	last->right = new_node;

	new_node->left = last;

	return;
}

void bubbledown(Node* node, int times)
{
	int temp;

	if (node->parent != NULL)
	{
		if (node->data < node->parent->data)
		{
			temp = node->parent->data;
			node->parent->data = node->data;
			node->data = temp;
			bubbleup(node);

			if (node->right != NULL && times == 2)
			{
				bubbledown(node->right, 2);
			}

			if (node->child != NULL)
			{
				bubbledown(node->child, 2);
			}
		}
	}

	return;
}

void update_parent(Node* root, Node* child_roots)
{
	Node* last;

	while (root != NULL)
	{
	    if (root->rank == child_roots->rank)
	    {
	    	child_roots->parent = root;
	    	child_roots->parent->rank = child_roots->parent->rank + 1;

	    	if (root->child == NULL)
	    	{
	    		root->child = child_roots;
	    		bubbleup(root->child);
	    	}
	    	else
	    	{
	    		Node* n = root->child;

	    	    while (n->right != NULL)
	    	    {
	    	    	n = n->right;
	    	    }

	    	    n->right = child_roots;
	    	    bubbledown(child_roots, 1);
	    	}

	    	return;
	    }
		last = root;
	    root = root->right;
	}

	root = child_roots;
	last->right = root;
	root->left = last;
}

void quickmerge(Node* node)
{
	Node* previous = node;
	node = node->right;

	while (node != NULL)
	{
		if (previous->rank == node->rank)
		{
			if (node->right != NULL)
			{
				previous->right = node->right;
				node->right->left = previous;
			}
			else
			{
				previous->right = NULL;
			}

			node->parent = previous;
			node->parent->rank = node->parent->rank + 1;

			if (previous->child == NULL)
			{
				previous->child = node;
				bubbleup(previous->child);
			}
			else
			{
				Node* n = previous->child;

				while (n->right != NULL)
				{
					n = n->right;
				}

				n = node;
				bubbleup(n);
			}
		}

		previous = node;
		node = node->right;
	}
}

void deletemin(Node** head_ref)
{
	Node* root = *head_ref;

	Node* chosen_starting_node = root;

	Node* node = root;
	Node* last;
	while (node != NULL)
	{
		if (node->data < chosen_starting_node->data)
		{
			chosen_starting_node = node;
		}

		last = node;
	    node = node->right;
	}

	//cout << chosen_starting_node->data << endl;

	Node* child_roots = chosen_starting_node->child;
	Node* before;

	while (child_roots != NULL)
	{
		update_parent(root, child_roots);

		before = child_roots;
		child_roots = child_roots->right;
		before->right = NULL;
	}

	if (chosen_starting_node == *head_ref)
	{
		*head_ref = chosen_starting_node->right;
		chosen_starting_node->right->left = NULL;
		chosen_starting_node = NULL;
	}
	else
	{
		chosen_starting_node->left->right = chosen_starting_node->right;
		chosen_starting_node->right->left = chosen_starting_node->left;
		chosen_starting_node = NULL;
	}

	Node* previous;
	Node* current_node;
	bool exists = true;

	while (exists == true)
	{
		exists = false;

		previous = *head_ref;
		current_node = previous->right;

	    while (current_node != NULL)
	    {
	        if (previous->rank == current_node->rank)
	        {
	        	exists = true;
	        }

	        previous = current_node;
	        current_node = current_node->right;
	    }

	    if (exists == true)
	    {
	    	quickmerge(*head_ref);
	    }
	}

	//cout << "Chosen starting node: " << chosen_starting_node->data << endl;



}

int main()
{
    /* Start with the empty list */
    Node* head = NULL;


    insert(&head, 1);
    insert(&head, 5);
    insert(&head, 8);
    insert(&head, 9);
    insert(&head, 11);
    insert(&head, 12);
    insert(&head, 15);
    insert(&head, 16);

    //insert(&head, 18);
    //insert(&head, 19);
    //insert(&head, 21);
    //insert(&head, 22);
    //insert(&head, 23);
    //insert(&head, 24);
    //insert(&head, 25);
    //insert(&head, 26);

    /*
    insert(&head, 16);
    insert(&head, 15);
    insert(&head, 12);
    insert(&head, 11);
    insert(&head, 9);
    insert(&head, 8);
    insert(&head, 7);
    insert(&head, 6);

    insert(&head, 25);
    insert(&head, 24);
    insert(&head, 23);
    insert(&head, 22);
    insert(&head, 21);
    insert(&head, 20);
    insert(&head, 19);
    insert(&head, 18);
	*/

    printList(head);

    deletemin(&head);

    //update(head, 26, 1);

    printList(head);

    update(head, 8, 1);

    printList(head);

    return 0;
}



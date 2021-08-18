/*
 * Chaining Dictionary Power of Two Choices.cpp
 *
 *  Created on: 17 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <cmath>
using namespace std;

int p = 19;
int k = 5;

class Node {
public:
    int data;
    Node* next;
};

int hashing_function1(int x)
{
	int sum = 0;
	int i;

	int a[p];
	for (i = 0; i < p; i++)
	{
		a[i] = i;
	}

	for (i = 0; i < k; i++)
	{
		sum = sum + int(a[i] * pow(x, i));
	}
	sum = sum % p;

	return sum;
}

int hashing_function2(int x)
{
	int sum = 0;
	int i;

	int a[p];
	for (i = 0; i < p; i++)
	{
		a[i] = i;
	}

	for (i = 0; i < k; i++)
	{
		sum = sum + int(a[i + 1] * pow(x, i));
	}
	sum = sum % p;

	return sum;
}

int length(Node* hashing_array[], int bucket)
{
	Node* u = hashing_array[bucket];

	int size = 1;

	while (u->data != 100)
	{
		u = u->next;

		size++;
	}

	return size;
}

void update(Node* hashing_array[], int value)
{
	int temp1 = hashing_function1(value);
	int temp2 = hashing_function1(value);
	Node* input_node;

	if (hashing_array[temp1]->data == 100)
	{
		hashing_array[temp1]->data = value;
	}
	else if (hashing_array[temp2]->data == 100)
	{
		hashing_array[temp2]->data = value;
	}
	else
	{
		int length1 = length(hashing_array, temp1);
		int length2 = length(hashing_array, temp2);

		if (length1 < length2)
		{
			input_node = hashing_array[temp1]->next;
		}
		else if (length2 < length1)
		{
			input_node = hashing_array[temp2]->next;
		}
		else
		{
			if (temp1 <= temp2)
			{
				input_node = hashing_array[temp1]->next;
			}
			else
			{
				input_node = hashing_array[temp2]->next;
			}
		}

		while (input_node->data != 100)
		{
			input_node = input_node->next;
		}

		input_node->data = value;
	}
}

int query(Node* hashing_array[], int value)
{
	int temp1 = hashing_function1(value);
	Node* u = hashing_array[temp1];

	while (u->data != 100)
	{
		if (u->data == value)
		{
			return true;
		}

		u = u->next;
	}

	int temp2 = hashing_function2(value);
	Node* v = hashing_array[temp2];

	while (v->data != 100)
	{
		if (v->data == value)
		{
			return true;
		}

		v = v->next;
	}

	return false;
}

int main()
{
   int sz = 100;
   int randArray[sz];
   for(int i=0;i<sz;i++)
   {
	   randArray[i] = rand() % 100;
   }

   for(int i=0;i<sz;i++)
   {
	   cout << "Elements no " << i+1 << "::" << randArray[i] << " ";
	   cout << "Hashing Address " << "::" << hashing_function1(randArray[i]) << endl;
   }

   int hashing_array_size = 20;
   Node* hashing_array[hashing_array_size];

   Node* node;
   for (int a = 0; a < hashing_array_size; a++)
   {
	   hashing_array[a] = new Node();
	   hashing_array[a]->data = 100;
	   hashing_array[a]->next = new Node();

	   node = hashing_array[a]->next;
	   for (int r = 0; r < 20; r++)
	   {
		   node->data = 100;
		   node->next = new Node();
		   node = node->next;
	   }
   }

   Node* input_node;
   for (int b = 0; b < sz; b++)
   {
	   int temp1 = hashing_function1(randArray[b]);
	   int temp2 = hashing_function1(randArray[b]);

	   if (hashing_array[temp1]->data == 100)
	   {
		   hashing_array[temp1]->data = randArray[b];
	   }
	   else if (hashing_array[temp2]->data == 100)
	   {
		   hashing_array[temp2]->data = randArray[b];
	   }
	   else
	   {
		   int length1 = length(hashing_array, temp1);
		   int length2 = length(hashing_array, temp2);

		   if (length1 < length2)
		   {
			   input_node = hashing_array[temp1]->next;
		   }
		   else if (length2 < length1)
		   {
			   input_node = hashing_array[temp2]->next;
		   }
		   else
		   {
			   if (temp1 <= temp2)
			   {
				   input_node = hashing_array[temp1]->next;
			   }
			   else
			   {
				   input_node = hashing_array[temp2]->next;
			   }
		   }

		   while (input_node->data != 100)
		   {
			   input_node = input_node->next;
		   }

		   input_node->data = randArray[b];
	   }
   }

   int update_value = 5;
   update(hashing_array, update_value);

   int query_value = 99;
   bool in_hash = query(hashing_array, query_value);

   if (in_hash == true)
   {
	   cout << "Value is in the hash table" << endl;
   }
   else
   {
	   cout << "Value is not in the hash table" << endl;
   }

   //cout << "Size of bucket " << 3 << " is " << length(hashing_array, 3) << endl;

   return 0;
}



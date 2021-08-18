/*
 * Lazy Funnel Sort.cpp
 *
 *  Created on: 26 Mar 2021
 *      Author: Grant
 */

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define N 50

class Node {
public:
	Node* parent;
	Node* left_child;
	Node* right_child;

	int buffer[N];
	int buffer_size;

	Node() {
		parent = NULL;
		left_child = NULL;
		right_child = NULL;

		for (int i = 0; i < N; i++)
		{
			buffer[i] = 0;
		}
	}
};

class Tree {
public:
	Node* root;

	Tree() {
		root = NULL;
	}
};

Node* sorting(int buffer1[], int buffer2[])
{
	Node* result = new Node();

	int count1 = 0;
	int count2 = 0;

	while(buffer1[count1] != 0)
	{
		count1++;
	}

	while(buffer2[count2] != 0)
	{
		count2++;
	}

	int new_buffer1[count1];
	int new_buffer2[count2];

	for (int x = 0; x < count1; x++)
	{
		new_buffer1[x] = buffer1[x];
	}

	for (int y = 0; y < count2; y++)
	{
		new_buffer2[y] = buffer2[y];
	}

	//sort(new_buffer1, new_buffer1 + count1);
	//sort(new_buffer2, new_buffer2 + count2);

	int a = 0;
	int b = 0;
	int buffer_count = 0;
	while (a <= count1 && b <= count2)
	{
		if (a == count1)
		{
			result->buffer[buffer_count] = new_buffer2[b];
			buffer_count++;
			b++;
			continue;
		}

		if (b == count2)
		{
			result->buffer[buffer_count] = new_buffer1[a];
			buffer_count++;
			a++;
			continue;
		}

		if (new_buffer1[a] < new_buffer2[b])
		{
			result->buffer[buffer_count] = new_buffer1[a];
			buffer_count++;
			a++;
		}
		else
		{
			result->buffer[buffer_count] = new_buffer2[b];
			buffer_count++;
			b++;
		}
	}

	return result;
}

Node* funnel_sort(Node* endpoints[], int n)
{
	cout << "SIZE " << n << endl;
	for (int x = 0; x < n; x++)
	{
		cout << "Endpoints" << endl;
		for (int y = 0; y < N; y++)
		{
			cout << endpoints[x]->buffer[y] << " ";
		}
		cout << endl;
	}
	cout << endl;

	Node* new_endpoints[N];

	for (int i = 0; i < N; i++)
	{
		new_endpoints[i] = NULL;
	}

	int endpoints_count = 0;
	for (int j = 0; j < n; j += 2)
	{
		if ((j + 1) == n)
		{
			new_endpoints[endpoints_count] = endpoints[j];
			endpoints_count++;
			break;
		}

		new_endpoints[endpoints_count] = sorting(endpoints[j]->buffer, endpoints[j + 1]->buffer);
		endpoints_count++;
	}

	if (endpoints_count == 1)
	{
		return new_endpoints[0];
	}
	else
	{
		funnel_sort(new_endpoints, endpoints_count);
	}
}

int main()
{
	Tree* new_tree = new Tree();
	int n = 20;
	int array[n] = {1, 5, 3, 6, 9, 15, 5, 8, 2, 11, 21, 2, 8, 1, 15, 3, 9, 6, 18, 1};
	int b = 4;
	int size = n / b;

	Node* endpoints_array[N];

	for (int i = 0; i < b; i++)
	{
		endpoints_array[i] = new Node();
	}

	for (int j = 0; j < b; j++)
	{
		int count = j * size;
		int temp_size = 0;
		for (int k = 0; k < size; k++)
		{
			if (count == n)
			{
				break;
			}

			endpoints_array[j]->buffer[k] = array[count];
			temp_size++;
			count++;
		}
		sort(endpoints_array[j]->buffer, endpoints_array[j]->buffer + temp_size);
	}

	cout << endpoints_array[3]->buffer[0] << endl;
	cout << endpoints_array[3]->buffer[1] << endl;
	cout << endpoints_array[3]->buffer[2] << endl;
	cout << endpoints_array[3]->buffer[3] << endl;
	cout << endpoints_array[3]->buffer[4] << endl;
	cout << endl;

	Node* resulting_node = funnel_sort(endpoints_array, b);

	cout << resulting_node->buffer[0] << endl;
	cout << resulting_node->buffer[1] << endl;
	cout << resulting_node->buffer[2] << endl;
	cout << resulting_node->buffer[3] << endl;
	cout << resulting_node->buffer[4] << endl;
	cout << resulting_node->buffer[5] << endl;
	cout << resulting_node->buffer[6] << endl;
	cout << resulting_node->buffer[7] << endl;
	cout << resulting_node->buffer[8] << endl;
	cout << resulting_node->buffer[9] << endl;
	cout << resulting_node->buffer[10] << endl;
	cout << resulting_node->buffer[11] << endl;
	cout << resulting_node->buffer[12] << endl;
	cout << resulting_node->buffer[13] << endl;
	cout << resulting_node->buffer[14] << endl;
	cout << resulting_node->buffer[15] << endl;
	cout << resulting_node->buffer[16] << endl;
	cout << resulting_node->buffer[17] << endl;
	cout << resulting_node->buffer[18] << endl;
	cout << resulting_node->buffer[19] << endl;

	cout << "HERE";

	return 0;
}


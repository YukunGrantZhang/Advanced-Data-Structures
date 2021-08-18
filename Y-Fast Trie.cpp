/*
 * Y-Fast Trie.cpp
 *
 *  Created on: 13 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int final_size;
int array_sez = 16;

int* tree_array(int *lower_level, int size, int final_result_size)
{
	int y;
	if (size % 2 > 0)
	{
		y = int(size/2) + 1;
	}
	else
	{
		y = int(size/2);
	}

	int * result = new int[y + final_result_size];
	//cout << y << endl;

	int new_array[y];

	for (int x = 1; x <= y; x++)
	{
		int index = 2 * x - 2;
		int comparison_index = index + 1;

		if (comparison_index == size)
		{
			if (lower_level[index] == 1)
			{
				new_array[x - 1] = 1;
			}
			else
			{
				new_array[x - 1] = 0;
			}
			continue;
		}

		if (lower_level[index] == 1 or lower_level[comparison_index] == 1)
		{
			new_array[x - 1] = 1;
		}
		else
		{
			new_array[x - 1] = 0;
		}
		//cout << new_array[x - 1] << endl;
	}

	int *new_array_pointer;
	new_array_pointer = new_array;

	copy(new_array_pointer, new_array_pointer + y, result);
	copy(lower_level, lower_level + final_result_size, result + y);

	/*
	for (int a = 0; a < (y + final_result_size); a++)
	{
		cout << result[a];
	}
	cout << endl;
	*/

	//final_result = result;

	if (y == 1)
	{
		final_size = y + final_result_size;

		int m = 15;
		for (int t = 30; t > 14; t--)
		{
			if (result[t] == 1)
			{
				result[t] = m;
			}
			m--;
		}
		return result;
	}
	else
	{
		return tree_array(result, y, y + final_result_size);
	}



	//return result;
}

int predecessor(int *final_array, int final_array_size, int *original_array, int *hash_table[], int value, int hash_table_size)
{
	if (original_array[value] == 1)
	{
		for (int i = 0; i < hash_table_size; i++)
		{
			if (*(hash_table[i]) == value)
			{
				return *(hash_table[i - 1]);
			}
		}
	}
	else
	{
		int final_array_index = 15 + value;

		cout << "Final Array Index " << final_array_index << endl;

		int index = (final_array_index - 1) >> 1;

		while (final_array[index] == 0)
		{
			index = (index - 1) >> 1;
		}
		cout << "Ancestor Index " << index << endl;

		int left_ancestor = 2 * index + 1;
		int right_ancestor = 2 * index + 2;
		//cout << "Left Ancestor " << left_ancestor << endl;
		//cout << "Right Ancestor " << right_ancestor << endl;

		while (left_ancestor <= final_array_size and right_ancestor <= final_array_size)
		{
			if (final_array[left_ancestor] == 1)
			{
				index = left_ancestor;
			}
			else
			{
				index = right_ancestor;
			}
			left_ancestor = 2 * index + 1;
			right_ancestor = 2 * index + 2;
		}
		cout << "Final Index " << index << endl;

		return final_array[index];
	}
}

int main() {
	int original_array[16] = {1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0};
	int *original_array_pointer;
	original_array_pointer = original_array;
	//final_result = original_array;

	int *final_array;
	final_array = tree_array(original_array_pointer, 16, 16);

	for (int a = 0; a < (final_size); a++)
	{
		cout << final_array[a];
	}
	cout << endl;
	cout << "Final Size:" << final_size << endl;

	int hash_table_size = 0;
	for (int x = 0; x < 16; x++)
	{
		if (original_array[x] == 1)
		{
			hash_table_size++;
		}
	}
	cout << "Hash Table Size:" << hash_table_size << endl;

	int *hash_table[hash_table_size];
	int i = 0;
	for (int x = 0; x < 16; x++)
	{
		if (original_array[x] == 1)
		{
			hash_table[i] = &final_array[15 + x];
			i++;
		}
	}

	for (int x = 0; x < hash_table_size; x++)
	{
		cout << *(hash_table[x]) << endl;
	}

	int p;
	int value = 9;

	p = predecessor(final_array, final_size, original_array_pointer, hash_table, value, hash_table_size);

	cout << "Predecessor of " << value << " is " << p << endl;

	return 0;
}



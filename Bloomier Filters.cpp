/*
 * Bloomier Filters.cpp
 *
 *  Created on: 16 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <cmath>
using namespace std;

int p = 101;
int k = 5;

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
		sum = sum + int(a[i + 1] * pow(x, i));
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
		sum = sum + int(a[i + 2] * pow(x, i));
	}
	sum = sum % p;

	return sum;
}

void insert(int hashing_array[][2], int value, int selection)
{
	int temp;

	if (selection == 1)
	{
		temp = hashing_function1(value);
	}
	else
	{
		temp = hashing_function2(value);
	}

	if (hashing_array[temp][0] == 100)
	{
		hashing_array[temp][0] = value;
		hashing_array[temp][1] = selection;
	}
	else
	{
		if (hashing_array[temp][1] == 1)
		{
			int original_value = hashing_array[temp][0];
			hashing_array[temp][0] = value;
			hashing_array[temp][1] = selection;
			insert(hashing_array, original_value, 2);
		}
		else
		{
			int original_value = hashing_array[temp][0];
			hashing_array[temp][0] = value;
			hashing_array[temp][1] = selection;
			insert(hashing_array, original_value, 1);
		}
	}

	return;
}

bool query(int hashing_array[][2], int value)
{
	int temp1 = hashing_function1(value);
	int u1 = temp1;

	int temp2 = hashing_function2(value);
	int u2 = temp2;

	if (hashing_array[u1][0] == value || hashing_array[u2][0] == value)
	{
		return true;
	}

	return false;
}

int main()
{
   int sz = 25;
   int randArray[sz];
   for(int i=0;i<sz;i++)
   {
	   randArray[i] = rand() % 100;
   }

   for(int i=0;i<sz;i++)
   {
	   cout << "Elements no " << i+1 << "::" << randArray[i] << " ";
	   cout << "Hashing Address 1 " << "::" << hashing_function1(randArray[i]) << endl;
   }
   cout << endl;

   for(int y=0;y<sz;y++)
   {
	   cout << "Elements no " << y+1 << "::" << randArray[y] << " ";
   	   cout << "Hashing Address 2 " << "::" << hashing_function2(randArray[y]) << endl;
   }
   cout << endl;

   int hashing_array_size = 4 * sz;
   int hashing_array[hashing_array_size][2];

   for (int j = 0; j < hashing_array_size; j++)
   {
	   hashing_array[j][0] = 100;
	   hashing_array[j][1] = 0;
   }

   for (int u = 0; u < sz; u++)
   {
	   insert(hashing_array, randArray[u], 1);
   }

   int update_value = 39;
   insert(hashing_array, update_value, 1);

   int query_value = 91;
   bool in_hash = query(hashing_array, query_value);

   if (in_hash == true)
   {
	   cout << "Value is in the hash table" << endl;
   }
   else
   {
	   cout << "Value is not in the hash table" << endl;
   }

   return 0;
}



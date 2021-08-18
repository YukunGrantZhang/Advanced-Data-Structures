/*
 * Bloom Filters.cpp
 *
 *  Created on: 16 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <cmath>
using namespace std;

int p = 101;
int k = 2;

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

int update(int hashing_array1[], int hashing_array2[], int value)
{
	int temp1 = hashing_function1(value);
	int temp2 = hashing_function2(value);

	if (hashing_array1[temp1] == 0)
	{
		hashing_array1[temp1] = 1;
	}

	if (hashing_array2[temp2] == 0)
	{
		hashing_array2[temp2] = 1;
	}
}

bool query(int hashing_array1[], int hashing_array2[], int value)
{
	int temp1 = hashing_function1(value);
	int u1 = temp1;

	int temp2 = hashing_function2(value);
	int u2 = temp2;

	if (hashing_array1[u1] != 0 && hashing_array2[u2] != 0)
	{
		return true;
	}

	return false;
}

int main()
{
   int sz = 50;
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


   int hashing_array_size = 2 * sz;
   int hashing_array1[hashing_array_size];
   int hashing_array2[hashing_array_size];

   for (int j = 0; j < hashing_array_size; j++)
   {
	   hashing_array1[j] = 0;
   }

   for(int e=0;e<sz;e++)
   {
   	   int temp = hashing_function1(randArray[e]);

   	   if (hashing_array1[temp] == 0)
   	   {
   		   hashing_array1[temp] = 1;
   	   }
   }

   for (int j1 = 0; j1 < hashing_array_size; j1++)
   {
   	   hashing_array2[j1] = 0;
   }

   for(int e1=0;e1<sz;e1++)
   {
	   int temp = hashing_function2(randArray[e1]);

	   if (hashing_array2[temp] == 0)
	   {
		   hashing_array2[temp] = 1;
	   }
   }

   int update_value = 39;
   update(hashing_array1, hashing_array2, update_value);

   int query_value = 98;
   bool in_hash = query(hashing_array1, hashing_array2, query_value);

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



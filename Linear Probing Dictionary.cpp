/*
 * Linear Probing Dictionary.cpp
 *
 *  Created on: 15 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <cmath>
using namespace std;

int p = 19;
int k = 5;

int hashing_function(int x)
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

int update(int hashing_array[], int value)
{
	int temp = hashing_function(value);

	if (hashing_array[temp] == 1000)
	{
		hashing_array[temp] = value;
	}
	else
	{
		int u = temp;

		while (hashing_array[u] != 1000)
		{
			u++;
		}

		hashing_array[u] = value;
	}
}

int query(int hashing_array[], int value)
{
	int temp = hashing_function(value);
	int u = temp;

	while (hashing_array[u] != 1000)
	{
		if (hashing_array[u] == value)
		{
			return true;
		}

		u++;
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
	   cout << "Hashing Address " << "::" << hashing_function(randArray[i]) << endl;
   }

   int hashing_array_size = 300;
   int hashing_array[hashing_array_size];

   for (int j = 0; j < hashing_array_size; j++)
   {
	   hashing_array[j] = 1000;
   }

   for(int e=0;e<sz;e++)
   {
   	   int temp = hashing_function(randArray[e]);

   	   if (hashing_array[temp] == 1000)
   	   {
   		   hashing_array[temp] = randArray[e];
   	   }
   	   else
   	   {
   		   int u = temp;

   		   while (hashing_array[u] != 1000)
   		   {
   			   u++;
   		   }

   		   hashing_array[u] = randArray[e];
   	   }
   }

   int update_value = 39;
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


   return 0;
}



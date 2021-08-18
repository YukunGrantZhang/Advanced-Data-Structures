/*
 * MapReduce.cpp
 *
 *  Created on: 28 Mar 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

#define N 50

float mapping[N][2];
float result[N];

void maps(float input[], int n, float interval)
{
	for (int i = 0; i < n; i++)
	{
		float c = input[i] / interval;

		int m = ceil(c) - 1;

		mapping[i][0] = input[i];
		mapping[i][1] = float(m);
	}
}

void reduce(int number, int n)
{
	float buckets[number][N];

	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < N; j++)
		{
			buckets[i][j] = 0;
		}
	}

	for (int k = 0; k < n; k++)
	{
		int count;

		for (int k1 = 0; k1 < N; k1++)
		{
			if (buckets[int(mapping[k][1])][k1] == 0)
			{
				count = k1;
				break;
			}
		}

		buckets[int(mapping[k][1])][count] = mapping[k][0];
	}

	for (int m = 0; m < number; m++)
	{
		for (int m1 = 0; m1 < N; m1++)
		{
			cout << buckets[m][m1] << " ";
		}
		cout << endl;
	}

	int result_count = 0;
	for (int p = 0; p < number; p++)
	{
		int limit;
		for (int p1 = 0; p1 < N; p1++)
		{
			if (buckets[p][p1] == 0)
			{
				limit = p1;
				break;
			}
		}

		float sorting[limit];

		for (int p2 = 0; p2 < limit; p2++)
		{
			sorting[p2] = buckets[p][p2];
		}

		sort(sorting, sorting + limit);

		for (int p3 = 0; p3 < limit; p3++)
		{
			result[result_count] = sorting[p3];
			result_count++;
		}
	}
}

int main()
{
	int input_size = 20;
	int interval = 5;
	float input[input_size] = {5, 6, 9, 1, 3, 2, 7, 4, 8, 15, 11, 13, 12, 10, 14, 20, 18, 19, 16, 17};

	maps(input, input_size, interval);

	for (int i = 0; i < input_size; i++)
	{
		cout << mapping[i][0] << " " << mapping[i][1] << endl;
	}
	cout << endl;

	int number = 4;

	reduce(number, input_size);

	for (int j = 0; j < N; j++)
	{
		if (result[j] == 0)
		{
			break;
		}

		cout << result[j] << endl;
	}
}



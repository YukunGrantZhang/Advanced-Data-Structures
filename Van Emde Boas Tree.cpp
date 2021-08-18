/*
 * Van Emde Boas Tree.cpp
 *
 *  Created on: 13 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <cmath>
using namespace std;

int V_summary[4] = {0, 0, 0, 0};
int summary_max = 100;
int summary_min = 100;

int V_cluster[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
int cluster_max[4] = {100, 100, 100, 100};
int cluster_min[4] = {100, 100, 100, 100};

void insert(int x)
{
	int c = x / 4;
	int i = x % 4;

	if (V_summary[c] == 0)
	{
		V_summary[c] = 1;
	}

	if (V_cluster[c][i] == 0)
	{
		V_cluster[c][i] = 1;
	}

	if (summary_max == 100 && summary_min == 100)
	{
		summary_max = c;
		summary_min = c;
	}

	if (c < summary_min)
	{
		summary_min = c;
	}

	if (c > summary_max)
	{
		summary_max = c;
	}

	if (cluster_max[c] == 100 && cluster_min[c] == 100)
	{
		cluster_max[c] = i;
		cluster_min[c] = i;
	}

	if (i < cluster_min[c])
	{
		cluster_min[c] = i;
	}

	if (i > cluster_max[c])
	{
		cluster_max[c] = i;
	}
}

int predecessor(int x)
{
	int c = x / 4;
	int i = x % 4;

	int a;
	int b;
	for (a = c; a >= 0; a--)
	{
		if (a == c && cluster_min[a] != 100)
		{
			b = cluster_min[a];
			break;
		}
		if (cluster_max[a] != 100)
		{
			b = cluster_min[a];
			break;
		}
	}

	return 4 * a + b;
}


int main() {
	int *V_summary_pointer = V_summary;
	int (*V_cluster_pointer)[4] = V_cluster;

	insert(3);
	insert(15);
	insert(12);

	int p = 5;
	cout << "Predecessor of " << 5 << " is " << predecessor(p) << endl;
	return 0;
}



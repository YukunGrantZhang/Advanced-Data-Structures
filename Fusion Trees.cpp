/*
 * Fusion Trees.cpp
 *
 *  Created on: 14 Jan 2021
 *      Author: Grant
 */

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int sketch_positions[3] = {0, 0, 0};

void sketchpositions(int n, int position)
{
	int i;
	int a[10];

	for(i=0; n>0; i++)
	{
		a[i] = n%2;
		n = n/2;
	}

	for(i=i-1 ;i>=0 ;i--)
	{
		cout << a[i];

		if (a[i] == 1)
		{
			sketch_positions[position] = i + 1;
			//sketch_positions[position] = i;
		}
	}
	cout << endl;
}

int getsketches(int n)
{
	int i;
	int a[10];

	for(i=0; n>0; i++)
	{
		a[i] = n%2;
		n = n/2;
	}

	int sketches[3] = {0, 0, 0};

	int temp = i - 1;

	for(i=i-1 ;i>=0 ;i--)
	{
		for (int x = 0; x < 3; x++)
		{
			if (sketch_positions[x] == i)
			{
				sketches[sketch_positions[x] - 1] = a[i];
				//sketches[sketch_positions[x]] = a[i];
			}
		}

		cout << a[i];
	}
	cout << endl;

	int result = 0;
	for (int y = 0; y < 3; y++)
	{
		cout << sketches[y];

		if (sketches[y] == 1)
		{
			result = result + pow(2, y);
		}
	}
	cout << endl << endl;

	return result;
}

int decimaltobinary(int n)
{
	int i;
	int a[50];

	for(i=0; n>0; i++)
	{
		a[i] = n%2;
		n = n/2;
	}

	cout << "Sketch Compilation" <<endl;

	for(i=i-1 ;i>=0 ;i--)
	{
		cout<<a[i];
	}
}

int test_sketch = 0;

void testsketchpositions(int n)
{
	int i;
	int a[10];

	for(i=0; n>0; i++)
	{
		a[i] = n%2;
		n = n/2;
	}

	for(i=i-1 ;i>=0 ;i--)
	{
		cout << a[i];

		if (a[i] == 1)
		{
			test_sketch = i + 1;
			//sketch_positions[position] = i;
		}
	}
	cout << endl;
}

int gettestsketches(int n)
{
	int i;
	int a[10];

	for(i=0; n>0; i++)
	{
		a[i] = n%2;
		n = n/2;
	}

	int sketches[3] = {0, 0, 0};

	int temp = i - 1;

	for(i=i-1 ;i>=0 ;i--)
	{
		if (i == test_sketch)
		{
			//cout << "Test Sketch " << test_sketch <<endl;
			sketches[i] = a[i];
		}

		if (i == test_sketch - 1)
		{
			if (a[i] == 1)
			{
				sketches[i] = 0;

				int j;
				for(j=i-1 ;j>=0 ;j--)
				{
					sketches[j] = 1;
				}
			}
			else
			{
				sketches[i] = 1;

				int j;
				for(j=i-1 ;j>=0 ;j--)
				{
					sketches[j] = 0;
				}
			}
		}

		/*
		for (int x = 0; x < 3; x++)
		{
			if (sketch_positions[x] == i)
			{
				sketches[sketch_positions[x] - 1] = a[i];
				//sketches[sketch_positions[x]] = a[i];
			}
		}
		*/
		cout << a[i];
	}
	cout << endl;

	cout << "Sketches: ";
	for(int r=2 ;r >= 0 ; r--)
	{
		cout << sketches[r];
	}
	cout << endl;

	int result = 0;

	for (int y = 0; y < 3; y++)
	{
		//cout << sketches[y];

		if (sketches[y] == 1)
		{
			result = result + pow(2, y);
		}
	}
	cout << endl << endl;


	return result;
}

int predecessor(int n)
{
	int i;
	int a[50];

	for(i=0; n>0; i++)
	{
		a[i] = n%2;
		n = n/2;
	}

	//cout << "Predecessor " <<endl;

	int t = i;
	int r;

	for(i=0 ;i < t ;i++)
	{
		if ((i + 1) % 4 == 0)
		{
			if (a[i] == 0)
			{
				r = (i + 1) / 4;
				break;
			}
		}
		//cout<<a[i];
	}

	return r - 2;
}

int main() {
	int inputs[4] = {16, 20, 22, 29};
	int inputs_sketches[4] = {0, 0, 0, 0};
	int multiplied_inputs_sketches = 0;

	for (int a = 0; a < 3; a++)
	{
		int temp_sketch = (inputs[a]) ^ (inputs[a + 1]);
		cout << "Sketch Placements: " << temp_sketch << endl;
		sketchpositions(temp_sketch, a);
	}

	for (int b = 0; b < 3; b++)
	{
		cout << "Sketch Position: " << sketch_positions[b] << endl;
	}

	for (int c = 0; c < 4; c++)
	{
		inputs_sketches[c] = getsketches(inputs[c]);
	}

	cout << "Input Sketches" << endl;

	for (int d = 0; d < 4; d++)
	{
		cout << inputs_sketches[d] << endl;
	}
	cout <<endl;

	int m;
	for (int e = 0; e < 4; e++)
	{
		m = e * 4;
		//cout << m <<endl;
		multiplied_inputs_sketches = multiplied_inputs_sketches + inputs_sketches[e] * pow(2, m);
	}
	cout << multiplied_inputs_sketches <<endl;

	decimaltobinary(multiplied_inputs_sketches);

	cout << endl << endl;





	int find_number = 18;
	int left_position;
	int right_position;
	int t_sketch = 0;

	int positions[4];

	for (int g = 0; g < 3; g++)
	{
		int temp = 0;

		/*
		if (g == 0)
		{
			temp = find_number ^ (inputs[g]);
		}
		else if (g == 4)
		{
			temp = find_number ^ (inputs[g - 1]);
		}
		else
		{
			int i = find_number ^ (inputs[g - 1]);
			int j = find_number ^ (inputs[g]);
			temp = min(i, j);
		}
		*/

		int i = find_number ^ (inputs[g]);
		int j = find_number ^ (inputs[g + 1]);
		temp = max(i, j);

		if (temp > 0)
		{
			cout << "Sketch Placements: " << temp << endl;
			testsketchpositions(temp);
			break;
		}

		//cout << "Sketch Placements: " << temp << endl;
		//sketchpositions(temp_sketch, a);
	}

	cout << "Test sketch number: " << test_sketch << endl;

	int result = gettestsketches(find_number);

	cout << "Result: " << result << endl;

	int new_multiplied_inputs_sketches = 0;
	int new_m;
	for (int y = 0; y < 4; y++)
	{
		new_m = y * 4;

		new_multiplied_inputs_sketches = new_multiplied_inputs_sketches + result * pow(2, new_m);
	}

	int new_m_minus;
	for (int v = 0; v < 5; v++)
	{
		if (v == 0)
		{
			continue;
		}

		if (v == 1)
		{
			new_m_minus = v * 3;
		}
		else
		{
			new_m_minus = v * 4 - 1;
		}

		new_multiplied_inputs_sketches = new_multiplied_inputs_sketches + pow(2, new_m_minus);
	}

	cout << new_multiplied_inputs_sketches <<endl;

	decimaltobinary(new_multiplied_inputs_sketches);

	cout << endl << endl;

	int final_result = new_multiplied_inputs_sketches - multiplied_inputs_sketches;
	cout << "FInal Result " << final_result << endl;
	decimaltobinary(final_result);

	cout << endl;

	int answer = predecessor(final_result);

	if (answer >= 0)
	{
		cout << "Predecessor of " << find_number << " is " << inputs[answer] << endl;
	}
	//cout << "Hello World!" << endl; // prints !!!Hello World!!!
	return 0;
}



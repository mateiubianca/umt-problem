// probl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

using namespace std;

ifstream f("input.txt");

int commonPoints(vector<int> v1, vector<int> v2) {
	vector<int> v3;

	set_intersection(v1.begin(), v1.end(),v2.begin(), v2.end(),back_inserter(v3));

	return v3.size();
}

int computeCombinationsOf2(int n) {
	return n * (n - 1) / 2;
}

struct Point {
	int x, y;
} ;

int main()
{
	/*
	i decided to store the points read from the file in a map, where the x coordinate will be the key, and the y coordinates
	will be stored in a vector of integeres, which will be the value.

	So for example, for the sample input provided in the problem, the map will be like this:
		1 -> [1, 3]
		2 -> [1, 3]
		3 -> [1, 3]

	The reason I decided to store the data like this is because this way, i have together all the points that have the same x. And from the details of the
	problem, the 4 corners of the rectangle must have the same x, 2 by 2, so that the edges are parallel with the y axis, and they must have the same y,
	2 by 2, to be parallel to x axis.

	So, for example, the fact that both keys 1 and 2 have the points 1 and 3 in their vectors, means that i can draw a rectangle, like in the following representation:

	3   *		*

	2

	1   *		*

		1	2	3
	
	So, in the while loop i simply build the map variable.

	After doing this, i need to sort the arrays (i will explain later why).

	Now to find the number of arrays, i need to find the common number of points between each 2 vectors of integers from the map of points. So i do this by using 2
	for loops. I also placed some conditions, if the size of the vector is smaller than 2, simply pass over it, because an edge can not be found on that x value.

	In the commonPoints function, i use the function set_intersection, which performs the intersection on 2 vectors. The vectors need to be sorted, that's why i did
	that before. The function returns the size of the resulted intersection, aka the number of common points.

	Now, we know that there are n common y points between the vectors of 2 x coordinates, so how many rectangles can we build out of them?
	This is solved using combinations, since we need 2 y points for a rectangle, the answer is Combinations of n taken 2 times. This number is simply added to the final
	number of rectangles.


	Talking about complexity, let's denote the number of different x coordinates with n, and suppose that for each x coordinate, we have k y coordinates.
	So the total number of points is n*k.
	To create the map, the time complexity is O(n*k), because 1 push_back takes O(1)
	Next, sorting each vector using the sort function takes O(k*logk), so for n vectors that will be O(n*k*logk)
	The function that calculates the number of common points has a linear complexity, so it will be O(k), but since we have 2 for loops for covering every pair of vectors,
	the complexity will be O(n^2 * k)

	So, the final complexity is the sum of the 3 computed complexities, and we only consider the one that has the quickest growth, which is O(k*n^2)

	*/
	map<int, vector<int>> points;

	int x, y;
	char comma, bracket;

	while (f >> bracket >> x >> comma >> y >> bracket) {
		map<int, vector<int>>::iterator it;
		it = points.find(x);
		if (it != points.end()) {
			vector<int> value = points.at(x);
			value.push_back(y);
			points.at(x) = value;
		}
		else {
			vector<int> value;
			value.push_back(y);
			points[x] = value;
		}
		f >> comma;
	}

	int noRectangles = 0;

	for (map<int, vector<int>>::iterator it = points.begin(); it != points.end(); it++) {
		sort(it->second.begin(), it->second.end());
	}

	for (map<int, vector<int>>::iterator it = points.begin(); it != points.end(); it++) {
		if (it->second.size() < 2) continue;
		for (map<int, vector<int>>::iterator it2 = next(it, 1); it2 != points.end(); it2++) {
			if (it2->second.size() < 2) continue;
			int n = commonPoints(it->second, it2->second);
			noRectangles += computeCombinationsOf2(n);
		}
	}

	cout << noRectangles;

}

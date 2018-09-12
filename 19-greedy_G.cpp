// Greedy_priyanka.cpp : https://www.hackerrank.com/challenges/priyanka-and-toys/problem?h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter

int toys(vector <int> arr)
{
	if (arr.size() == 1) return 1;

	int answer = 0;

	sort(arr.begin(), arr.end());

	int mystart = arr[0];

	for (auto iter = arr.begin() + 1; iter != arr.end(); ++iter)
	{
		if (*iter > mystart + 4)
		{
			answer++;
			mystart = *iter;
		}

	}

	return answer + 1;
}


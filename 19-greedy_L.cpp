// Greedy_mincut.cpp : https://www.hackerrank.com/challenges/board-cutting/problem
//

#include "stdafx.h"
#include <iostream>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

typedef vector<int> I_vec;
typedef long long   LL;

struct CutPair
{
	LL cost;
	char type;
	bool operator< (const CutPair& rhs) const { return cost < rhs.cost; }
};

#define _R1(x) x.begin(), x.end()
#define _RR(x) x.rbegin(), x.rend()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define PRN(x) cout << x << endl

int boardCutting(I_vec cost_y, I_vec cost_x)
{
	const size_t HCutSize = cost_y.size();
	const size_t VCutSize = cost_x.size();
	const size_t cutSize = HCutSize + VCutSize;

	if (HCutSize < 1 || VCutSize < 1) exit(EXIT_FAILURE);

	vector<CutPair> theCuts;

	for (size_t i = 0; i < HCutSize; i++)
	{
		CutPair temp;
		temp.cost = cost_y[i];
		temp.type = 'H';
		theCuts.push_back(temp);
	}

	for (size_t i = 0; i < VCutSize; i++)
	{
		CutPair temp;
		temp.cost = cost_x[i];
		temp.type = 'V';
		theCuts.push_back(temp);
	}

	sort(_RR(theCuts));

	LL totalCost = 0, VCuts = 1, HCuts = 1;
	for (size_t i = 0; i < cutSize; i++)
	{
		if (theCuts[i].type == 'H')
		{
			totalCost += theCuts[i].cost * VCuts;
			HCuts++;
		}
		else
		{
			totalCost += theCuts[i].cost * HCuts;
			VCuts++;
		}
	}

	return totalCost % (1000000000L + 7);
}


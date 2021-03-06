// Greedy_fighting.cpp : https://www.hackerrank.com/challenges/fighting-pits/problem
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

typedef vector<int> I_vec;
typedef long long   LL;

void process_error(const string, const int);
#define _R1(x) x.begin(), x.end()
#define _RR(x) x.rbegin(), x.rend()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define PRN(x) cout << x << endl
#define ERR(X) process_error(X, __LINE__)

ifstream myinput("sample.txt", ios::in);
int ri() { int x; myinput >> x; return x; }

struct MyQuery
{
	int type;
	int strength;
	size_t teamOne;
	size_t teamTwo;
};

int matchTeams(I_vec team_x, I_vec team_y)
{
	int sizeX = team_x.size();
	int sizeY = team_y.size();

	if (sizeX == 0) return -1;

	int answer;
	while (true)
	{
		int strength = team_x[sizeX - 1];
		sizeY -= strength;

		if (sizeY <= 0) { answer = 1; break; }

		strength = team_y[sizeY - 1];
		sizeX -= strength;

		if (sizeX <= 0) { answer = 2; break; }
	}

	PRN(answer);

	return answer;
}

I_vec fightingPits(vector<I_vec> teams, vector<MyQuery> queries)
{
	for (size_t i = 0; i < teams.size(); i++)
	{
		sort(_R1(teams[i]));
	}

	I_vec answer;

	for (size_t i = 0; i < queries.size(); i++)
	{
		if (queries[i].type == 1)
			teams[queries[i].teamOne].push_back(queries[i].strength);
		else if (queries[i].type == 2)
		{
			size_t team_x = queries[i].teamOne;
			size_t team_y = queries[i].teamTwo;
			
			int result = matchTeams(teams[team_x], teams[team_y]);
			if (result == 1)
				answer.push_back(team_x + 1);
			else if (result == 2)
				answer.push_back(team_y + 1);
		}
		else ERR("invalid query");
	}

	return answer;
}


int main()
{
	if (!myinput) ERR("I/O error");

	int n = ri();
	int k = ri();
	int q = ri();

	vector<I_vec> teams(k);
	for (size_t i = 0; i < n; i++)
	{
		int strength = ri();
		int team_no = ri();

		if (team_no < 1 || team_no > k) ERR("invalid range");
		size_t team_ind = team_no - 1;

		teams[team_ind].push_back(strength);
	}
		
	vector<MyQuery> queries;
	for (size_t i = 0; i < q; i++)
	{
		MyQuery temp {0,0,0,0};

		temp.type = ri();

		if (temp.type == 1)
		{
			temp.strength = ri();
			temp.teamOne = ri() - 1;
		}
		else if (temp.type == 2)
		{
			temp.teamOne = ri() - 1;
			temp.teamTwo = ri() - 1;
		}
		else ERR("invalid query");

		queries.push_back(temp);
	}

	I_vec result = fightingPits(teams, queries);

    return 0;
}

void process_error(const string msg, const int line)
{
	cerr << __FILE__ << ", line " << line << endl;
	cerr << "Error: " << msg << endl;
	cerr << msg << endl;
	exit(EXIT_FAILURE);
}

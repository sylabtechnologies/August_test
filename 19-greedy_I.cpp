// Greedy_maxtoys.cpp : https://www.hackerrank.com/challenges/mark-and-toys/problem

#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter

// choose the max group
int maxToys(vector<int> prices, int k)	
{
	int answer = 0;

	sort(_R1(prices));

	// minimize for each subset
	for (_R2(prices))
	{
		if (*iter <= k)
		{
			answer++;
			k -= *iter;
		}
		else
			break;
	}

	return answer;
}

// Greedy_permutation.cpp : https://www.hackerrank.com/challenges/largest-permutation/problem
//


#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter

typedef std::pair<int, int> Special_pair;

vector<int> largestPermutation(int k, vector<int> arr)
{
	// sort with indices
	vector<Special_pair> temp;

	for (size_t i = 0; i < arr.size(); i++)
	{
		temp.push_back(std::make_pair(arr[i], i));
	}

	sort(temp.begin(), temp.end(),
		[](const Special_pair& lhs, const Special_pair& rhs) -> bool
		{ return lhs.first > rhs.first; } );

	// construct from first k numbers
	vector<int> answer(arr);
	for (size_t i = 0; i < k; i++)
	{
		answer[i] = temp[i].first;
		answer[temp[i].second] = arr[i];
	}

	return answer;
}

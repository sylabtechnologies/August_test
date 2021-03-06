// Greedy_permutation.cpp : https://www.hackerrank.com/challenges/largest-permutation/problem
//


#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter

const int screen = 20;

vector<int> largestPermutation(const int k, vector<int> arr)
{
	// sort with indices
	map<int, size_t> permutationMap;

	for (size_t i = 0; i < arr.size(); i++)
	{
		permutationMap.emplace(arr[i], i);

	}

	// do k permutations
	size_t count = 0;	// && break when count == k
	vector<int> answer(_R1(arr));

	for (map<int, size_t>::reverse_iterator iter = permutationMap.rbegin(); iter != permutationMap.rend(); ++iter)
	{
		cout << iter->first << "\t" << iter->second << endl;

		int swap = answer[count];
		answer[count] = iter->first;
		answer[iter->second] = swap;

		// we must swap the map
		permutationMap[swap] = iter->second;
		iter->second = count;

		count++;
		if (count >= k) break;
	}

	return answer;
}



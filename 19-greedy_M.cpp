// Greedy_botenergy.cpp : https://www.hackerrank.com/challenges/chief-hopper/problem
//

typedef vector<int> I_vec;
typedef long long   LL;

#define _R1(x) x.begin(), x.end()
#define _RR(x) x.rbegin(), x.rend()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define PRN(x) cout << x << endl

int chiefHopper(I_vec arr)
{
	int minEnergy = 0;

	for (auto iter = arr.rbegin(); iter != arr.rend(); ++iter)
	{
		minEnergy = (minEnergy + *iter + 1) / 2;
	}

	return minEnergy;
}

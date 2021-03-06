// Greedy_orders.cpp : https://www.hackerrank.com/challenges/jim-and-the-orders/problem
//

#define _R1(x) x.begin(), x.end()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter

struct Customer
{
	int serveTime;
	int custNumber;

	bool operator< (const Customer& rhs) const
	{
		if (serveTime == rhs.serveTime)
			return custNumber < rhs.custNumber;
		else
			return serveTime < rhs.serveTime;
	}

};

vector<int> jimOrders(vector<vector<int>> orders)
{
	vector<Customer> servetime;

	int cust_no = 0;
	for (size_t i = 0; i < orders.size(); i++)
	{
		cust_no++;
		Customer temp;

		temp.custNumber = cust_no;
		temp.serveTime = orders[i][0] + orders[i][1];

		servetime.push_back(temp);
	}

	sort(_R1(servetime));		// voila DO EXACTLY THE SPECIFIED PROCEDURE ###R/D!#

	vector<int> answer;
	for (_R2(servetime))
	{
		answer.push_back(iter->custNumber);
	}

	return answer;
}

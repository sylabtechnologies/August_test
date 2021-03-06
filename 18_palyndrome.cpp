#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

bool is_palyndrome(const string& s)
{
	if (s.length() <= 1) return true;

	if (s[0] != s[s.length() - 1]) return false;

	return is_palyndrome(s.substr(1, s.length() - 2));
}

int main()
{
	string s = "abracadaba";

	cout << is_palyndrome(s) << endl;

    return 0;
}


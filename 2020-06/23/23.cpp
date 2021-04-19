//[二进制求和](https://leetcode-cn.com/problems/add-binary/)
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a = "11";
	string b = "1";
	while (a.size() != b.size())
	{
		(a.size() < b.size()) ? a = '0' + a : b = '0' + b;
	}

	int c = 0;
	for (int i = a.size() - 1; i >= 0; i--)
	{
		int sum = a[i] - '0' + b[i] - '0' + c;
		a[i] = sum % 2 + '0';
		c = sum / 2;
	}
	if (c > 0)
	{
		a = '1' + a;
	}
	cout << a << endl;
	return 0;
}
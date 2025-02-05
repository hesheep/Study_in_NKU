#include<iostream>
#include <stdlib.h>
using namespace std;

//¼ÆËãÄ£ÔËËã
long long int fastModularExponentiation(long long int a, long long int m, long long int n) {
    //long long int result = 1;
	__int128 result = 1;
	//long long int c1 = a;
	__int128 c1 = a;
	c1 = c1 % n;
	while (m > 0) {
		if (m % 2 == 1) {
			result = (result * c1) % n;
		}
		c1 = (c1 * c1) % n;
		m /= 2;
	}
	return result;
}

bool MR(long long int n)
{
	long long int k = 0;
	long long int m = 0;
	long long int b = 0;
	long long int n1 = n - 1;
	//cout << "n-1=" << n1 << endl;
	while (n1/2)
	{
		n1 /= 2;
		k++;
		if (n1 % 2 == 1)
			break;
	}
	m = n1;
	//cout << "k=" << k << endl << "m=" << m << endl;
	int a = rand() % (n - 1) + 1;
	b = fastModularExponentiation(a, m, n);
	if (b % n == 1)
	{
		//cout << "Yes" << endl;
		return true;
	}
	for (long long int i = 0; i < k; i++)
	{
		if (b % n == n - 1)
		{
			//cout << "Yes" << endl;
			return true;
		}
		else
			b = fastModularExponentiation(b, 2, n);
	}
	return false;

}
int main()
{
	long long int n;
	cin >> n;
	if (MR(n))
		cout << "Yes";
	else
		cout << "No";
	return 0;
}
#include<iostream>
#include <conio.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	int a = 1, b = 1, c = 1;
	int n, count = 0;
	cout << "¬ведите количество чисел: ";
	cin >> n;
	while (count < n)
	{
		cout << c << endl;
		c = a + b;
		a = b;
		b = c;
		count++;
	}
	_getch();
	return 0;
}

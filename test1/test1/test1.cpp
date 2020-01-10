#include <iostream>
using namespace std;

int main()
{
	const char* a;
	a = new char[100];
	cout << sizeof(*a) << endl;
	delete[] a;
}
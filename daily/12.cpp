#include <iostream>

using namespace std;

template <typename T>
T fibonacci(T n)
{
	T x0 = 1;
	T x1 = 1;
	for(int i=2; i<=n; i++) {
		T x2 = x0 + x1;
		x0 = x1;
		x1 = x2;
	}
	return x1;
}

int main()
{
	unsigned n = fibonacci(4);
	cout << n << endl;
}
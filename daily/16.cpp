#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class CircularBuffer
{
public:
	CircularBuffer(size_t size) : v(size), last(0) {}
	void insert(T x)
	{
		v[last] = std::move(x);
		last = (last+1) % v.size();
	}
	T back(size_t i=0)
	{
		return v[(v.size()-i-1) % v.size()];
	}
private:
	unsigned last;
	vector<T> v;
};
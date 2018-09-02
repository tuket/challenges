#include <vector>
#include <array>
#include <iostream>
#include <cassert>

using namespace std;

template <typename T, unsigned DIMENSIONS>
struct Table
{
    static_assert(DIMENSIONS > 0);

    Table() {}
    Table(array<int, DIMENSIONS> dims)
        : dims(dims)
    {
        int n = 1;
        for(int d : dims) n *= d;
        values.resize(n);
    }

    void setAll(const T& val) { for(auto& x : values) x = val; }

    T& operator()(const array<int, DIMENSIONS>& indices) {
        int i = getOneIndex(indices);
        return values[i];
    }
    const T& operator()(const array<int, DIMENSIONS>& indices)const {
        int i = getOneIndex(indices);
        return values[i];
    }

    template <typename... Args>
    T& operator()(Args... indices)
    {
        int i = getOneIndex({indices...});
        return values[i];
    }

    template <typename... Args>
    const T& operator()(Args... indices)const
    {
        int i = getOneIndex({indices...});
        return values[i];
    }

    int getOneIndex(const array<int, DIMENSIONS>& indices)const {
        int i = 0;
        int n = 1;
        for(int j = 0; j < indices.size(); j++) {
            assert(indices[j] >= 0 && indices[j] < dims[j]);
            i *= n;
            i += indices[DIMENSIONS - j - 1];
            n *= dims[j];
        }
        return i;
    }

    int size(int i)const {
        assert(i >= 0 && i < DIMENSIONS);
        return dims[i];
    }

    int rows()const{ return dims[0]; }
    int cols()const{ return dims[1]; }

    int W()const{ return dims[0]; }
    int H()const{ return dims[1]; }

    array<int, DIMENSIONS> dims;
    vector<T> values;
};

int main()
{
    Table<int, 2> table({5, 2});
    cout << table(3, 1) << endl;
}
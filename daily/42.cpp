#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class C
{
public:
    C(const vector<int>& v, int k)
        : v(v), k(k), N(v.size()) {}
    
    vector<int> calcInds()
    {
        calcInds(N, k);
        auto it = D.find({N, k});
        if(it != D.end())
            return it->second;
        return {};
    }
private:
    void calcInds(int n, int k)
    {
        if()
    }

    vector<int> v;
    int k;
    unsigned N;
    unordered_map<pair<int, int>, vector<int>> D;
};

int main()
{
    
}
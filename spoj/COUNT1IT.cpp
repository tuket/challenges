#include <bits/stdc++.h>

using namespace std;

random_device randDevice;
mt19937 randGen(randDevice());

template <typename TX>
class TreapNode;

template <typename TX>
array<TreapNode<TX>*, 2> split(TreapNode<TX>*, TX x);

template <typename TX>
TreapNode<TX>* merge(TreapNode<TX>*, TreapNode<TX>*);

template <typename TX>
class TreapNode
{
public:
    void insert(TX x);
    void insert(TX, unsigned y);

    void erase(TX x);

private:
    TX _x;
    unsigned _y;
    TreapNode* _c1 = nullptr,
               _c2 = nullptr;

    friend array<TreapNode*, 2> split<TX>(TreapNode*, TX);
    friend TreapNode* merge<TX>(TreapNode*, TreapNode*);
};

// splits the tree t into two subtees:
// - a tree with all the keys _x < x
// - a tree with all the keys _x > x;
template <typename TX>
array<TreapNode<TX>*, 2> split(TreapNode<TX>* t, TX x)
{
    if(x == t->_x) {
        return {t->_c1, t->_c2};
    }
    array<TreapNode<TX>*, 2> res{nullptr, nullptr};
    if(x < t->_x) {
        res[1] = t;
        res[0] = t->_c1;
        while(res[0]) {
            if(res[0]->_c2 < x)
                break;
            res[0] = res[0]->_c1;
        }
    }
    else {
        res[0] = t;
        res[1] = t->_c2;
        while(res[1]) {
            if(res[1]->_c1 > x)
                break;
            res[1] = res[1]->_c2;
        }
    }
    return res;
}

// assumption: all _x in t1 < all _x in t2
// choose the as the of the tree the one with highest _y

template <typename TX>
TreapNode<TX>* merge(TreapNode<TX>* t1, TreapNode<TX>* t2)
{

}

int main()
{
    
}
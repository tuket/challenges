#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

template <typename T>
struct Node
{
    T val = 0;
    Node* a = nullptr, *b = nullptr;
};

int main()
{
    Node<int>* root = new Node<int> {
            0,
            new Node<int>{1},
            new Node<int>{
                0,
                new Node<int>{
                        1,
                        new Node<int>{1},
                        new Node<int>{1}
                },
                new Node<int>{0}
            }
    };

    int numNodes = 0;
    vector<Node<int>*> q = {root};
    unordered_map<Node<int>*, Node<int>*> parentOf;
    vector<Node<int>*> leafs;
    while(q.size())
    {
            numNodes++;
            Node<int>* node = q.back();
            q.pop_back();
            if(node->a) {
                q.push_back(node->a);
            parentOf[node->a] = node;
        }
            if(node->b) {
                q.push_back(node->b);
            parentOf[node->b] = node;
        }

            if(node->a == nullptr && node->b == nullptr)
                leafs.push_back(node);
    }
        
    int res = leafs.size();
    unordered_map<Node<int>*, int> mp;
    while(leafs.size())
    {
        Node<int>* node = leafs.back();
        leafs.pop_back();
        auto it = parentOf.find(node);
        if(it != parentOf.end()) {
            Node<int>* parent = it->second;
            auto it2 = mp.find(parent);
            if(it2 == mp.end()) {
                if(parent->val == node->val)
                    mp[parent] = node->val;
            }
            else {
                if(node->val == it2->second) {
                    res++;
                    leafs.push_back(parent);
                }
            }
        }
    }

    cout << res << endl;
}

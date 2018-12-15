#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Trie
{
public:
    struct Node
    {
        Node() : c(0) {}
        Node(char c) : c(c) {}
        char c;
        map<char, Node*> children;
    };

    void insert(const string& str)
    {
        Node* node = &root;
        for(char c : str)
        {
            auto& children = node->children;
            auto it = children.find(c);
            if(it == children.end())
            {
                children[c] = new Node(c);
                it = children.find(c);
            }
            node = it->second;
        }
    }

    bool isPrefix(const string& str)
    {
        Node* node = &root;
        for(char c : str)
        {
            auto& children = node->children;
            auto it = children.find(c);
            if(it == children.end())
                return false;
            node = it->second;
        }
    }

    Node root;
};

int solve(const vector<vector<char>>& v, int i, Trie::Node* node)
{
    if(v.size() == i)
        return 1;

    const vector<char>& vv = v[i];
    int res = 0;
    for(char c : vv)
    {
        const auto& children = node->children;
        auto it = children.find(c);
        if(it != children.end())
        {
            res += solve(v, i+1, it->second);
        }
    }
    return res;
}

int main()
{
    int L, D, N;
    cin >> L >> D >> N;
    Trie trie;
    for(int i=0; i<D; i++)
    {
        string str;
        cin >> str;
        trie.insert(str);
    }

    for(int kk=1; kk<=N; kk++)
    {
        vector<vector<char>> v;
        string str;
        cin >> str;
        for(int i=0; i<str.size(); i++)
        {
            char c = str[i];
            vector<char> vv;
            if(c == '(')
            {
                i++;
                while(str[i] != ')')
                {
                    vv.push_back(str[i]);
                    i++;
                }
            }
            else
            {
                vv.push_back(c);
            }
            v.push_back(vv);
        }
        cout << "Case #" << kk << ": " << solve(v, 0, &trie.root) << endl;
    }
}
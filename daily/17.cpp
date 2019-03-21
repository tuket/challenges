#include <iostream>
#include <vector>
#include <limits>
#include <functional>

using namespace std;

struct Node
{
    string name;
    vector<Node*> children;
};

Node* makeTree(const string& s)
{
    vector<size_t> ends;
    for(size_t i=0; i<s.size(); i++)
    {
        if(s[i] == '\n')
            ends.push_back(i);
    }
    ends.push_back(s.size());
    vector<Node*> d = {new Node{"", {}}};
    size_t start;
    size_t end = numeric_limits<size_t>::max(); // overflow in the first iteration
    for(size_t e : ends)
    {
        start = end + 1;
        end = e;
        size_t depth = 0;
        while(s[start+depth] == '\t')
            depth++;
        string name(s.begin()+start+depth, s.begin()+end);
        Node* node = new Node{name};
        d[depth]->children.push_back(node);
        d.resize(depth+2);
        d[depth+1] = node;
    }
    return d[0];
}

void print(Node* node, size_t depth = 0)
{
    for(size_t i=0; i<depth; i++)
        cout << "\t";
    cout << node->name << endl;
    for(Node* c : node->children)
        print(c, depth+1);
}

string findLongest(const Node* node)
{
    string res = "";
    function<void(const Node* node, string s)> rec;
    rec = [&res, &rec](const Node* node, string s)
    {
        s += node->name;
        cerr << node->name << endl;
        if(node->children.empty()) {
            if(s.size() > res.size())
                res = s;
        }
        else {
            for(const Node* c : node->children) {
                rec(c, s+'/');
            }
        }
    };
    rec(node, "");
    return res;
}

int main()
{
    string fs = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext";
    Node* root = makeTree(fs);
    print(root);
    string longest = findLongest(root);
    cout << longest << endl;
}
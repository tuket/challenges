#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

template<typename T>
struct TreeNode
{
    TreeNode<T>* parent;
    vector<TreeNode<T>> children;
    T val;

    TreeNode() {}
    TreeNode(const T& val) : val(val) {}
    TreeNode(const TreeNode& other)
    {
        val = other.val;
        children = other.children;
        for(auto& c : children) c.parent = this;
    }
    TreeNode(T val, const vector<TreeNode>& children)
        : children(children)
        , val(val)
    {
        for(auto c : this->children) c.parent = this;
    }

    string stringify()const {
        stringstream ss;
        addMeToStringStream(ss, 0, true);
        return ss.str();
    }

private:
    const char* indentString = "    ";
    void addMeToStringStream(stringstream& ss, int indent, bool isLast)const {
        for(int i=0; i<indent; i++) ss << indentString;
        if(children.empty()) {
            ss << val;
        }
        else {
            ss << "{ " << val << ", {" << endl;
            for(int i=0; i<children.size(); i++) {
                children[i].addMeToStringStream(ss, indent + 1, i == children.size() - 1);
            }
            for(int i=0; i<indent; i++) ss << indentString;
            ss << "}}";
        }
        if(!isLast) ss << ",";
        ss << endl;
    }
};

template <typename T>
struct Tree
{
    TreeNode<T> root;
    Tree() {}
    Tree(const Tree& other) : root(other.root) {}
    Tree(T val, const vector<TreeNode<T>>& children)
        : root(val, children)
    {}

    string stringify()const { return root.stringify(); }
};


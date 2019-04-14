#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <iomanip>

using namespace std;

struct Node
{
    float weight=-1;
    string feature="";
    Node *left=nullptr, *right=nullptr;
};

void skipSpaces(const char*& i, int inc = +1)
{
    for(; *i == ' ' || *i == '\t' || *i == '\n'; i+=inc);
}

void skipUntil(const char*& i, char c, int inc = +1)
{
    for(; *i != c; i += inc);
}

void skipUntilNum(const char*& i, int inc = +1)
{
    for(; !isdigit(*i); i += inc);
}

void skipUntilAlphaNum(const char*& i, int inc = +1)
{
    for(; !isalnum(*i); i += inc);
}

Node* toTree(const string& str, const char* i, const char* j)
{
    Node* node = new Node;
    skipUntil(i, '(', +1);
    skipUntil(j, ')', -1);
    i++; j--;
    skipUntilNum(i);
    char* afterNum;
    node->weight = strtof(i, &afterNum);
    i = afterNum;
    skipSpaces(i);
    if(*i != ')')
    {
        const char* endFeature;
        for(endFeature = i+1; endFeature < j && isalpha(*endFeature); endFeature++);
        node->feature = string(i, endFeature);
        i = endFeature;
        skipUntil(i, '(');
        const char* beg = i;
        int pc = 1;
        for(i++; pc; i++)
        {
            if(*i == '(') pc++;
            else if(*i == ')') pc--;
        }
        node->left = toTree(str, beg, i);
        skipUntil(i, '(', +1);
        skipUntil(j, ')', -1);
        node->right = toTree(str, i, j);
    }
    return node;
}

Node* toTree(const string& str)
{
    toTree(str, &str[0], &str[str.size()-1]);
}    

string toString(const Node* node, int tab=0)
{
    stringstream ss;
    for(int i=0; i<tab; i++)
            ss << "  ";
    if(node->left)
    {
        ss << "(" << node->weight << " " << node->feature << endl;
        ss << toString(node->left, tab+1);
        ss << toString(node->right, tab+1);
        for(int i=0; i<tab; i++)
            ss << "  ";
        ss << ")";
    }
    else
    {
        ss << "(" << node->weight << ")" << endl;
    }
    return ss.str();
}

void howCute(double& hc, const unordered_set<string>& features, Node* node)
{
    hc *= node->weight;
    if(node->left)
    {
        if(features.count(node->feature))
            howCute(hc, features, node->left);
        else
            howCute(hc, features, node->right);
    }
}

double howCute(const unordered_set<string>& features, Node* node)
{
    double hc = 1;
    howCute(hc, features, node);
    return hc;
}

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        cout << "Case #" << kk << ":" << endl;
        int NL; cin >> NL;
        string str, s;
        getline(cin, s);
        for(int l=0; l<NL; l++) {
            getline(cin, s);
            str += s;
        }
        Node* root = toTree(str);
        int numAnimals; cin >> numAnimals;
        for(int ia=0; ia<numAnimals; ia++)
        {
            cin >> s;
            int numFeatures; cin >> numFeatures;
            unordered_set<string> features;
            for(int i=0; i<numFeatures; i++) {
                cin >> s;
                features.insert(s);
            }
            double res = howCute(features, root);
            printf("%f\n", res);
            //cout << fixed << setprecision(9) << res << endl;
        }
    }
}
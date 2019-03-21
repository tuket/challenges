Class TrieNode
{
    Bool valid;
    map<char, TrieNode*> children;
}

vector<string> foo(const TrieNode* dict, const string& str, int i = 0, TrieNode* node = nullptr)
{
    if(!node) node = dict;
    String word = “”;
    for(; node; i++)
    {
        if(node->valid) {
            if(i == str.size())
        Return {word};
            vector<string> res = foo(dict, str, i, node);
            if(res.size() != 0) {
                res.push_back(word);
                Return res;
            }
        }
        Char c = str[i];
        if(node->children.count(c) == 0) {
            Node = nullptr;
        }
        Else {
            Node = node->children[c];
}
Word += c;
    }    
}



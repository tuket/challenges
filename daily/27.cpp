Void validBraquets(const string& s)
{
    Auto closeToOpen = [](char c)
    {
        switch(c) {
        Case ‘)’: return ‘(‘;
        Case ‘]’: return ‘[‘;
        Case ‘}’: return ‘{‘;
        Default: return 0;
    };
    vector<char> v;
    for(char c : s)
    {
        if(c == ‘(‘ || c == ‘[‘ || c == ‘{‘)
            v.push_back(c);
        Else if(c == ‘)’ || c == ‘]’ || c == ‘}’)
        {
            C = closeToOpen(c);
            if(c == v.back())
                v.pop_back();
            else 
                Return false;
        }
        Else return false;
    }
    Return v.size() == 0;
}

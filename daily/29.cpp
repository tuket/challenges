Struct Token
{
    Char c;
    Int n;
};

vector<Token> encode(const string& s)
{
    vector<Token> res;
    Token tk {‘0’, 0};
    for(char c : s)
    {
        if(c != tk.c)
        {
            if(tk.c != ‘0’) res.push_back(tk);
            Tk.c = c;
            Tk.n = 1;
        }
        Else tk.n++;
    }
    if(tk.c != ‘0’) res.push_back(tk);
    Return res;
}

String decode(const vector<Token>& tks)
{
    String res = “”;
    for(const Token& tk : tks)
    for(int i=0; i < tk.n; i++)
        Res += tk.c;
    Return res;
}

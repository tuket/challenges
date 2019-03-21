Int dist(const string& a, const string& b, int i = 0, int j = 0)
{
    Const int na = a.size() - i;
    Const int nb = b.size() - j;
    Int res = 0;
    if(na == nb)
    {
        for(;i < a.size(), i++, j++)
            if(a[i] != b[j]) res++;
        Return res;
    }
    Else if(na < nb)
    {
        for(; i < a.size() && a[i] == b[j]; i++, j++)
            Res++;
        if(i == a.size())
            Return res + b.size()-j; // add the rest
        Int ifChange = dist(a, b, i+1, j+1);
        Int ifAdd = dist(a, b, i, j+1);
        Return res + min(ifChange, ifAdd);
    }
    Else // na > nb
    {
        for(; j < b.size() && a[i] == b[j]; i++, j++)
            Res++;
        if(j == b.size())
            Return res + a.size()-i; // delete the rest
        Int ifChange = dist(a, b, i+1, j+1);
        Int ifAdd = dist(a, b, i+1, j);
        Return res + min(ifChange, ifAdd);
    }
}

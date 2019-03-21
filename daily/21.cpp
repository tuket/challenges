vector<pair<int, int>> v;
sort(v.begin(), v.end());
Int res = 0;
Int last = 0;
for(auto p : v)
{
    if(p.first >= last)
    {
        Res++;
        Last = p.last;
    }
}
Cout << res << endl;

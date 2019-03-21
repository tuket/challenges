Int rain(const vector<int>& v)
{
    Int res = 0;
    //forward pass
    Int high = 0;
    Auto step = [&](int i)
    {
        if(v[i] < high) res += high - v[i];
        Else if(v[i] > high) hight = v[i];
    }
    // step forwards
    for(int i=0; i<v.size(); i++)
        step(i);
    // step backbards
High = 0;
for(int i=v.size()-1; i>=0; i--)
step(i);
// substract
for(int i=0; i<v.size(); i++)
    Res -= high - v[i];
Return res;
}

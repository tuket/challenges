vector<string> justify(const vector<string>& ww, int k)
{
    vector<string> res;
    vector<string> lw;
    Int curLen = 0;
    for(const string& w : ww)
    {
        Int nextLen = curLen + w.size();
        if(lw.empty()) nextLen++;
        if(nextLen > k)
        {
            Int spacesToAdd = k-curLen;
            for(int i=0; i<lw.size()-1; i++)
            {
                Int sp = 1 + spacesToAdd / (lw.size()-1);
                if(i < spacesToAdd % (lw.size()-1)) sp++;
                for(int j=0; j<sp; j++)
                    Lw[i] += ‘ ‘;
            }
            String line;
            for(const string& w : lw) line += w;
            res.push_back(line);
            Lw = {w};
            curLen = w.size();
        }
        Else
        {
            lw.push_back(w);
            curLen += w.size();
        }
    }
    Return res;
}

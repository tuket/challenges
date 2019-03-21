Void removeKthLast(list<int>& l, int k)
{
    auto it0 = l.begin();
    auto it1 = l.begin();
    for(int i=0; i<k; i++)
        it1++;
    for(; it1 != l.end(); ++it0, ++it1);
    l.erase(it0);
}

Struct Vec2 {
    Int x, y;
};

Int minPath(const vector<vector<bool>>& M, Vec2 start, Vec2 end)
{
    Const int W = M[0].size();
    Const int H = M.size();
    Auto isValid = [&](Vec2 p)
    {
        if(p.x < 0 || p.x >= W || p.y < 0 || p.y >= H)
            Return false;
        Return M[p.y][p.x];
    };
    Static Const array<Vec2, 4> DIRS = {
        {-1, 0}, {+1, 0}, {0, -1}, {0, +1}
    };
    vector<vector<int>> C(vector<int>(W, INF), H);
    queue<Vec2> q = {start};
    while(q.size())
    {
        Vec2 p = q.front();
        q.pop_front();
        Int newVal = C[p.y][p.x] + 1;
        for(Vec2 dir : DIRS)
        {
            Vec2 np = p + dir;
            if(isValid(np))
            if(newVal < C[np.y][np.x])
            {
                C[np.y][np.x] = newVal;
                q.push(np)
            }
        }
    }
    Return C[end.y][end.x];
}

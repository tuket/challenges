Bool hasArbitrage(const vector<vector<double>>& A, int i = 0, double val = 1.0)
{
    Const double threshold = 1.000001;
    Const int n = A.size();
    if(val * A[i][0] > threshold)
        Return true;
    for(int j=i+1; j<n; j++)
    {
        if(hasArbitrage(A, j, val * A[i][j]))
            Return true;
    }
    Return false;
}

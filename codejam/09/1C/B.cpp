#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    int nn;
    cin >> nn;
    for(int kk=1; kk<=nn; kk++)
    {
        int n;
        cin >> n;
        double X, Y, Z, VX, VY, VZ;
        X = Y = Z = VX = VY = VZ = 0;
        for(int i=0; i<n; i++)
        {
            double x, y, z, vx, vy, vz;
            cin >> x >> y >> z >> vx >> vy >> vz;
            X += x;
            Y += y;
            Z += z;
            VX += vx;
            VY += vy;
            VZ += vz;
        }
        X /= n;
        Y /= n;
        Z /= n;
        VX /= n;
        VY /= n;
        VZ /= n;
        double V = sqrt(VX*VX + VY*VY + VZ*VZ);
        double ux = VX / V;
        double uy = VY / V;
        double uz = VZ / V;
        double dotProd = -X*ux - Y*uy - Z*uz;
        double dist = sqrt(X*X + Y*Y + Z*Z);
        if(V < 0.00000000001 || dotProd <= 0) {
            printf("Case #%d: %.8f %.8f\n", kk, dist, 0.0);
        }
        else {
            double time = dotProd / V;
            double closeDist = sqrt(max(0.0, dist*dist - dotProd*dotProd -0.000000001));
            printf("Case #%d: %.8f %.8f\n", kk, closeDist, time);
        }
    }
}
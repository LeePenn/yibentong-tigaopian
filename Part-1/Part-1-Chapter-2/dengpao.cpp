#include <bits/stdc++.h>

using namespace std;

int T;
double H, h, D;
const double EPS = 1e-8;

double calc(double m) {
    return D + H - m - D * (H - h) / m;
}

int main() {
    cin >> T;
    while (T--) {
        cin >> H >> h >> D;
        double l = D - h * D / H, r = D;
        while (r - l > EPS) {
            double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
            if (calc(m1) < calc(m2)) l = m1;
            else r = m2;
        }
        printf("%.3lf\n", calc(r));
    }
    return 0;
}
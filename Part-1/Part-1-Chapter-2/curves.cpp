#include <bits/stdc++.h>

using namespace std;

const int N = 100004;
int T, n;
double a[N], b[N], c[N];
double MAX = -1e10, EPS = 1e-11;

double calc(double x) {
    double ans = MAX;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, a[i] * x * x + b[i] * x + c[i]);
    }
    return ans;
}

int main() {
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
        double l = 0.0, r = 1000.0;
        while (r - l > EPS) {
            double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
            if (calc(m1) <= calc(m2)) r = m2;
            else l = m1;
        }
        printf("%.4lf\n", calc(r));
    
    }

    return 0;
}
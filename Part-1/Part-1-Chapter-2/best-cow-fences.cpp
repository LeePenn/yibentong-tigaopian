#include <bits/stdc++.h>

using namespace std;

const int N = 100004;
int n, L;
double a[N], b[N], sum[N];
double EPS = 1e-6;

bool check(double m) {
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] - m;
        sum[i] = (sum[i - 1] + b[i]);
    }
    double ans = -1e10, min_val = 1e10;
    for (int i = L; i <= n; i++) {
        min_val = min(min_val, sum[i - L]);
        ans = max(ans, sum[i] - min_val);
    }
    if (ans >= 0) return true;
    return false;
}

int main() {
    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &a[i]);
    }
    double l = -1e6, r = 1e6;
    while (r - l > EPS) {
        double mid = (r + l) / 2;
        if (check(mid)) {
            l = mid;
        } else r = mid;
    }
    
    cout << int(r * 1000) << endl;

    return 0;
}
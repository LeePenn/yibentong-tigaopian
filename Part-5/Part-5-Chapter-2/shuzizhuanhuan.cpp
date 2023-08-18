#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n;
int d1[N], d2[N], sum[N];

void init() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= n / i; ++j) {
            sum[i * j] += i;
        }
    }
}

void DP() {
    for (int i = n; i >= 1; --i) {
        if (sum[i] < i) {
            if (d1[i] + 1 > d1[sum[i]]) {
                d2[sum[i]] = d1[sum[i]];
                d1[sum[i]] = d1[i] + 1;
            } else if (d1[i] + 1 > d2[sum[i]]) {
                d2[sum[i]] = d1[i] + 1;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    init();
    DP();
    
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, d1[i] + d2[i]);
    }
    printf("%d\n", ans);
    
    return 0;
}
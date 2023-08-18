#include <bits/stdc++.h>

using namespace std;

int n, a[1000005];

int main() {
    cin >> n;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    sum /= n;
    for (int i = 1; i <= n; i++) {
        a[i] -= sum;
        a[i] += a[i - 1];
    }
    sort(a + 1, a + n + 1);
    int median = a[(n + 1) >> 1];
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += abs(median - a[i]);
    }
    cout << ans << endl;

    return 0;   
}
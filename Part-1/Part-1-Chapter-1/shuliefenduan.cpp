#include <bits/stdc++.h>

using namespace std;

int n, x, m;

int main() {
    cin >> n >> m;
    int ans = 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (sum + x > m) {
            ans++;
            sum = x;
        } else {
            sum += x;
        }
    }
    if (sum > 0) ans++;
    cout << ans << endl;


    return 0;
}
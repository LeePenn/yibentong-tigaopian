#include <bits/stdc++.h>

using namespace std;

int n, k, a[204], ans;

void dfs(int m) {
    if (n == 0) return;
    if (m == k) {
        if (n >= a[m - 1]) ans++;
        return;
    }
    
    for (int i = a[m - 1]; i <= n / (k - m + 1); ++i) {
        a[m] = i;
        n -= i;
        dfs(m + 1);
        n += i;
    }
}

int main() {
    cin >> n >> k;
    a[0] = 1;
    dfs(1);
    cout << ans << endl;
    
    return 0;
}
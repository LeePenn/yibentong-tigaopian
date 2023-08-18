#include <bits/stdc++.h>

using namespace std;

int n, m, a[100004];

bool check(int mid) {
    int cnt = 1;
    int last = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] - last >= mid) {
            cnt++;
            last = a[i];
        }
    }
    return cnt >= m;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    int l = a[1], r = a[n];
    int ans = 0x7fffffff >> 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
    
    return 0;
}
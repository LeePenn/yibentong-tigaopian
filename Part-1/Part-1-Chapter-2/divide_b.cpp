#include <bits/stdc++.h>

using namespace std;

int n, m, a[100004];

bool check(int mid) {
    int sum = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (sum + a[i] > mid) {
            cnt++;
            sum = a[i];
        } else sum += a[i];
    }
    if (sum > 0) cnt++;
    return cnt <= m;
}
    
int main() {    
    cin >> n >> m;
    int l = 0, r = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        l = max(l, a[i]);
        r += a[i];
    }
    int ans;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    cout << ans << endl;

    return 0;
}   
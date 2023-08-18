#include <bits/stdc++.h>

using namespace std;

int n;
struct line {
    int l, r;
}a[1000005];

bool cmp(const line &a, const line &b) {
    return a.r < b.r;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r;
    sort(a + 1, a + n + 1, cmp);
    int last = -1;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i].l < last) continue;
        last = a[i].r;
        ans++;
    }
    cout << ans << endl;
    return 0;

}
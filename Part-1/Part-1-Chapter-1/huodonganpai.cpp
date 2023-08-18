#include <bits/stdc++.h>

using namespace std;

int n;

struct activity {
    int s, e;
}a[1000];

bool cmp(const activity &a, const activity &b) {
    return a.e < b.e;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].s >> a[i].e;
    
    sort(a + 1, a + n + 1, cmp);
    int last = a[1].e;
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i].s < last) continue;
        ans++;
        last = a[i].e;
    }
    cout << ans << endl;

    return 0;
}
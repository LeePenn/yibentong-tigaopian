#include <bits/stdc++.h>

using namespace std;

int n;
struct work {
    int d, w;
} a[1000004];
int v[1000004];

int find(int x) {
    if (v[x] != x)
        v[x] = find(v[x]);

    return v[x];
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i].d >> a[i].w;

    sort(a + 1, a + n + 1, [](work a, work b) {
        return a.w > b.w;
    });

    for (int i = 1; i <= 1000004; i++)
        v[i] = i;

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        int fa = find(v[a[i].d]);

        if (fa != 0) {
            ans += a[i].w;
            v[fa] = fa - 1;
        }
    }

    cout << ans << endl;


    return 0;
}
#include <bits/stdc++.h>

using namespace std;

int m, n;
struct game {
    int d, w;
}a[504];
bool b[504];

bool cmp(const game &a, const game &b) {
    return a.w > b.w;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> m >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].d;
    for (int i = 1; i <= n; i++) cin >> a[i].w;
    sort(a + 1, a + n + 1, cmp);
    
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= n; i++) {
        bool ok = false;
        for (int j = a[i].d; j >= 1; j--) {
            if (!b[j]) {
                b[j] = true;
                ok = true;
                break;
            }
        }
        if (!ok) {
            m -= a[i].w;
            for (int j = n; j >= 1; j--) {
                if (!b[j]) {
                    b[j] = true;
                    break;
                }
            }
        }
    }
    cout << m << endl;

    return 0;
}
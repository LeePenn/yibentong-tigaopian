#include <bits/stdc++.h>

using namespace std;

struct sp {
    double s, e;
}a[15005];
int T, n;
double l, w;

bool cmp(const sp &a, const sp &b) {
    return a.s < b.s;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> T;
    while (T--) {
        cin >> n >> l >> w;
        int tot = 0;
        for (int i = 1; i <= n; i++) {
            double x, r;
            cin >> x >> r;
            if (r <= w / 2.0) continue;
            double y = sqrt(r * r - w * w / 4.0);
            a[++tot].s = max(x - y, 0.0);
            a[tot].e = min(x + y, l);
        }
        sort(a + 1, a + tot + 1, cmp);
    
        double last = 0.0;
        int i = 1;
        int ans = 0;
        bool ok = true;
        while (last < l) {
            ans++;
            double cur = last;
            for (; a[i].s <= cur && i <= tot; i++) {
                if (a[i].e > last) last = a[i].e;
            }
            
            if (cur == last && cur < l) {
                ok = false;
                break;
            }
        }
        
        if (!ok) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    
    }

    return 0;
}
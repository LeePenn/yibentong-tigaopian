#include <bits/stdc++.h>

using namespace std;

int n;
struct m {
    int a, b;
    int minn;
    int idx;
}c[1003];
int ans[1003];

bool cmp(const m &a, const m &b) {
    return a.minn < b.minn;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i].a;
    for (int i = 1; i <= n; i++) {
        cin >> c[i].b;
        c[i].minn = min(c[i].a, c[i].b);
        c[i].idx = i;
    }
    
    sort(c + 1, c + n + 1, cmp);
    int k1 = 0, k2 = n + 1;
    for (int i = 1; i <= n; i++) {
        if (c[i].minn == c[i].a) ans[++k1] = i;
        else ans[--k2] = i;
    }
    
    int t1 = 0, t2 = 0;
    for (int i = 1; i <= n; i++) {
        t1 += c[ans[i]].a;
        if (t2 < t1) t2 = t1;
        t2 += c[ans[i]].b;
    }
    cout << t2 << endl;
    for (int i = 1; i <= n; i++) cout << c[ans[i]].idx << " ";
    cout << endl;
    

    return 0;
}
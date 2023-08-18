#include <bits/stdc++.h>

using namespace std;

struct road {
    int b, e, t;
}a[30005];
int n, h;
bool tree[30005];

bool cmp(const road &a, const road &b) {
    return a.e < b.e;
}

int main() {    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> h;
    for (int i = 1; i <= n; i++) cin >> a[i].b >> a[i].e >> a[i].t;
    sort(a + 1, a + n + 1, cmp);
    
    memset(tree, 0, sizeof(tree));
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int cur = 0;
        for (int j = a[i].e; j >= a[i].b; j--) {
            if (tree[j]) cur++;
        }
        if (cur >= a[i].t) continue;
        
        for (int j = a[i].e; j >= a[i].b; j--) {
            if (!tree[j]) {
                ans++;
                cur++;
                tree[j] = true;
            } 
            if (cur >= a[i].t) break;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
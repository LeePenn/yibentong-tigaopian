#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a[1000010], c[1000010], maxx, c2[1000010];
signed main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];             //输入
        c[a[i]]++;               //桶存入
        maxx = max(maxx, a[i]);  //限制桶的范围
    }

    for (int i = 1; i <= maxx; i++) {
        if (c[i])                               // i在桶里面存在
            for (int j = i; j <= maxx; j += i) {  //将i的倍数统一加上i的个数
                c2[j] += c[i];
            }
    }

    for (int i = 1; i <= n; i++) {
        cout << c2[a[i]] - 1 << '\n';
    }

    return 0;
}
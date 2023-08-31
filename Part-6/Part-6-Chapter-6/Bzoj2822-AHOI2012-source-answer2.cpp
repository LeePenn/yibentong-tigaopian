#include <bits/stdc++.h>
#define _for(i, a, b) for(int i = (a); i <= (b); ++i)
using namespace std;
int f[550][500], len = 1;
void add(int u) {
    _for(i, 1, len) f[u][i] = f[u - 1][i] + f[u][i];
    _for(i, 1, len) f[u][i + 1] += f[u][i] / 10, f[u][i] %= 10;

    if (f[u][len + 1])
        len++;
}
int main() {
    int n;
    cin >> n;
    f[1][1] = 1;
    //f[i]:i级台阶方案数
    _for(i, 2, n + 1) _for(j, 1, i) add(j);

    for (int i = len; i > 0; i--)
        cout << f[n][i];

    return 0;
}
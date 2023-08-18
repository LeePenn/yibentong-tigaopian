#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e6 + 10;
LL s[N];
bool flag[N];
int n, q[N], hh, tt, oil[N], dist[N];
int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> oil[i] >> dist[i];
        s[i] = s[i + n] = oil[i] - dist[i]; //破环为链
    }

    for (int i = 1; i <= 2 * n; i++)
        s[i] += s[i - 1]; //处理前缀和

    hh = 0, tt = -1;

    for (int i = 2 * n; i; i--) {
        while (hh <= tt && q[hh] > i + n - 1)
            hh++;

        while (hh <= tt && s[q[tt]] >= s[i])
            tt--;

        q[++tt] = i;

        if (i <= n && s[q[hh]] - s[i - 1] >= 0)
            flag[i] = true;
    }

    dist[0] = dist[n]; //逆时针时每个点的s为oid[i]-dist[i-1]，而第一个点应该减去dist[n]，因此把dist[0]赋值为dist[n]
    hh = 0, tt = -1; //清空队列

    for (int i = n; i; i--)
        s[i] = s[i + n] = oil[i] - dist[i - 1]; //处理s的值

    for (int i = 2 * n; i; i--)
        s[i] += s[i + 1]; //处理后缀和

    for (int i = 1; i <= 2 * n; i++) { //对每个s[i]，需要s[j]-s[i+1]>=0(i-n+1<=j<=i)
        while (hh <= tt && q[hh] < i - n + 1)
            hh++;

        while (hh <= tt && s[q[tt]] >= s[i])
            tt--;

        q[++tt] = i;

        if (i > n && s[q[hh]] - s[i + 1] >= 0)
            flag[i - n] = true; //这里不要忘记了i-n让其回到在1~n中的原位置
    }

    for (int i = 1; i <= n; i++)
        if (flag[i])
            puts("TAK");
        else
            puts("NIE");

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;

int n, m;
int a[N], f[N];
deque<int> q;

int ReadInt() {
    int r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

void Read() {
    n = ReadInt(), m = ReadInt();

    for (int i = 1; i <= n; ++i)
        a[i] = ReadInt();
}

void DP() {
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    // 假设烽火只照亮前面的烽火台，对后面的没有影响，这样处理可以简化模型
    // f[0] 也要参与最值判断
    q.push_back(0);
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; ++i) {
        while (!q.empty() && q.front() < i - m)
            q.pop_front();

        f[i] = f[q.front()] + a[i];

        while (!q.empty() && f[q.back()] > f[i])
            q.pop_back();

        q.push_back(i);

        if (i >= n - m + 1)
            ans = min(ans, f[i]);

        // printf("$$ %d %d\n", f[i], ans);
    }

    printf("%d\n", ans);
}

int main() {
    Read();

    DP();


    return 0;
}
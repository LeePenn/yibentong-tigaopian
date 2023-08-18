#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
/*
    原题来自：NOIP 2010 提高组初赛 · 完善程序
    烽火台是重要的军事防御设施，一般建在交通要道或险要处。一旦有军情发生，
则白天用浓烟，晚上有火光传递军情。在某两个城市之间有n 座烽火台，每个烽火
台发出信号都有一定的代价。为了使情报准确传递，在连续 m 个烽火台中至少要有
一个发出信号。现在输入n,m 和每个烽火台的代价，请计算总共最少的代价在两城
市之间来准确传递情报。

*/
const int N = 2e5 + 10;
int n, m, w[N], f[N], q[N];

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> w[i];

    int ans = 2e9;
    int h = 1, t = 0;                     //清空队列

    for (int i = 1; i <= n; i++) {        //枚举序列
        while (h <= t && f[q[t]] >= f[i - 1])
            t--; //队尾出队(队列不空且新元素更优)

        q[++t] = i - 1;                     //队尾入队(存储下标 方便判断队头出队)

        if (q[h] < i - m)
            h++;                   //队头出队(队头元素滑出窗口)

        f[i] = f[q[h]] + w[i];              //转移

        if (i > n - m)
            ans = min(ans, f[i]);
    }

    cout << ans;
}
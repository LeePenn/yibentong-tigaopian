#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e6 + 10;
LL n, p[N], d[N], a[N], sum[N], q[N];
int head, tail;
LL f[N];
bool flag[N];

void Read() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i] >> d[i];
        sum[i] = sum[i + n] = p[i] - d[i];
    };
    
    for (int i = 1; i <= 2 * n; ++i) {
        sum[i] += sum[i - 1];
    }
}

void DP() {
    head = 1, tail = 0;
    for (int i = 2 * n; i >= 0; --i) {
        while (head <= tail && q[head] >= i + n) head++;
        while (head <= tail && sum[q[tail]] >= sum[i]) tail--;
        q[++tail] = i;
        
        if (i <= n && sum[q[head]] - sum[i - 1] >= 0) flag[i] = 1;
    }
    
    d[0] = d[n];
    for (int i = n; i >= 0; --i) {
        sum[i] = sum[i + n] = p[i] - d[i - 1];
    }
    
    for (int i = 2 * n; i >= 0; --i) {
        sum[i] += sum[i + 1];
    }
    
    head = 0, tail = -1;
    
    for (int i = 1; i <= 2 * n; ++i) {
        while (head <= tail && q[head] <= i - n) head++;
        while (head <= tail && sum[q[tail]] >= sum[i]) tail--;
        q[++tail] = i;
        if (i > n && sum[q[head]] - sum[i + 1] >= 0) flag[i - n] = 1;
    }
    
    for (int i = 1; i <= n; ++i) {
        if (flag[i]) printf("TAK\n");
        else printf("NIE\n");
    }
}

int main() {
    Read();
    
    DP();

    return 0;
}
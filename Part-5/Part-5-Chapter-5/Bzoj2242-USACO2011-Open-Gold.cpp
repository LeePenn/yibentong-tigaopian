#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
LL n, k;
LL a[N], sum[N], q[N], f[N][2];
int tail, head;

void Read() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
}

void DP() {
    head = 1, tail = 1;
    for (int i = 1; i <= n; ++i) {
        f[i][0] = max(f[i - 1][0], f[i - 1][1]);
        while (q[head] < i - k && head <= tail) head++;
        
        f[i][1] = f[q[head]][0] - sum[q[head]] + sum[i];
        while (f[i][0] - sum[i] > f[q[tail]][0] - sum[q[tail]] && head <= tail) tail--;
        q[++tail] = i;
    }
    
    cout << max(f[n][0], f[n][1]) << endl;
}

int main() {
    Read();

    DP();
    
    return 0;
}
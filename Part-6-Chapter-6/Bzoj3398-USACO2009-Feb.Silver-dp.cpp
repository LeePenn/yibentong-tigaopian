#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
LL n, k, f[N], sum[N], p = 5000011;

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

LL ReadLL() {
    LL r = 0, f = 1;
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

int main() {
    cin >> n >> k;
    f[0] = sum[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (i > k) {
            f[i] = sum[i - k - 1];
        } else f[i] = 1;
        
        sum[i] = (sum[i - 1] + f[i]) % p;
    }
    
    cout << sum[n] << endl;
    
    return 0;
}


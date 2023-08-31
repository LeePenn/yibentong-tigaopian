#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5;
LL C[N][5], ans;
LL n, m;

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

void Init() {
    for (int i = 0; i < N; ++i) C[i][0] = 1;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j <= 3; ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}

LL Gcd(LL a, LL b) {
    if (!b) return a;
    return Gcd(b, a % b);
}

/*
为了不与之前斜率一样的情况重复统计，这里首先固定两个点(1,1)和(x,y)然后通过gcd(x-1,y-1)+1算出这条斜线上的整点的个数，
减掉固定的两个端点，剩下的就是自由的可行的点，每个点都分别代表着一种不同的情况，
因为已经固定的两个点是这三个点之间距离最大的两个点，这个距离一定大于之前算的斜率相同的距离最大的两个点的距离，
所以易证不会和之前算的情况重合，对于每个(1,1)到(x,y)的线段，在这个矩阵里总共有(n-x+1)*(m-y+1)条，
最后统计一下即可算出答案（因为矩阵的对称性，这只是算出了线段的斜率大于0 的情况，还有对称的斜率小于0的情况，
所以斜线上减掉的不合法情况数要乘二）
*/
int main() {
    cin >> m >> n;
    m++; n++;
    Init();
    
    LL tot = m * n;
    ans = C[tot][3];
    // same col
    ans = ans - C[m][3] * n;
    // same row
    ans = ans - C[n][3] * m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ans = ans - (Gcd(i, j) - 1) * (n - i) * (m - j) * (LL)2;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}


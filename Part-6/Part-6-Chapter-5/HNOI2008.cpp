#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 20 + 5;
LL n, m, p;
char s[N];
int nxt[N];

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

struct Node {
    LL mat[N][N] = {0};
    Node(int x = 0) {
        for (int i = 0; i < N; ++i) {
            mat[i][i] = x;    
        }
    }
}base, ans;

Node matrixMulti(Node x, Node y) {
    Node ret(0);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                ret.mat[i][j] = (ret.mat[i][j] + x.mat[i][k] * y.mat[k][j] % p) % p;
            }
        }
    }
    
    return ret;
}

Node matrixMultiple(Node x, LL k) {
    Node t(1);
    while (k) {
        if (k & 1) {
            t = matrixMulti(t, x);
        }
        x = matrixMulti(x, x);
        k >>= 1;
    }
    return t;
}

/*
    这个题很容易想到dp, dp[i][j]代表n位数字代表的文本串s前i位的后j位与模式串t的前j位匹配上的方案数.
    那我们最后的答案就是∑(j = 0 ~ m - 1)dp[n][j]
    分析状态转移: dp[i][j]的状态转移到下一个状态的情况可能有
    1. dp[i + 1][k](0 <= k <= j)文本串的第i + 1位与模式串的j + 1位没有匹配上, 所以能匹配的位置跳到了具有相同
    前缀的地方(kmp)
    2. dp[i + 1][j + 1]文本串的第i + 1位与模式串的j + 1位匹配上了
    定义b[i][j]为转移矩阵, 前i位匹配成功了, 第j + 1位又匹配成功了, 则 + 1
*/
int main() {
    scanf("%lld%lld%lld", &n, &m, &p);
    scanf("%s", s + 1);
    nxt[1] = 0;
    int j = 0, slen = strlen(s + 1);
    
    for (int i = 1; i < slen; ++i) {
        while (j && s[j + 1] != s[i + 1]) j = nxt[j];
        if (s[j + 1] == s[i + 1]) j++;
        nxt[i + 1] = j;
    }
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= 9; ++j) {
            int k = i;
            while (k && s[k + 1] != j + '0') k = nxt[k];
            
            if (s[k + 1] == j + '0') k++;
            base.mat[i][k] = base.mat[i][k] + 1;
            
        }
    }
    // 边界条件: dp[0][0] = 1
    ans.mat[0][0] = 1;
    ans = matrixMulti(ans, matrixMultiple(base, n));
    
    LL sum = 0;
    for (int i = 0; i < m; ++i) {
        sum = (sum + ans.mat[0][i]) % p;
    }
    
    printf("%lld\n", sum);
    
    return 0;
}


#include <cstdio>

long long A, B;
long long f[15], p[15];
long long AnsA[10], AnsB[10];

void solve(long long x, long long *Ans) {
    int len = 0;

    while (p[len] <= x)
        ++len;

    for (int i = len - 1; i >= 0; --i) {
        int s = x / p[i] % 10;

        for (int j = 0; j <= 9; ++j)
            Ans[j] += s * f[i];

        for (int j = 0; j < s; ++j)
            Ans[j] += p[i];

        Ans[s] += x % p[i] + 1;
    }

    for (int i = 1; i <= len; ++i)
        Ans[0] -= p[len - i];
}

int main() {
    scanf("%lld%lld", &A, &B);

    p[0] = 1;

    for (int i = 1; i <= 13; ++i)
        p[i] = p[i - 1] * 10;

    f[0] = 0;

    for (int i = 1; i <= 13; ++i)
        f[i] = p[i - 1] + 10 * f[i - 1];

    solve(A - 1, AnsA);
    solve(B, AnsB);

    for (int i = 0; i <= 9; ++i)
        printf("%lld ", AnsB[i] - AnsA[i]);

    puts("");

    return 0;
}
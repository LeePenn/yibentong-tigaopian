#include <cstdio>
using namespace std;
int n, k, dp[100005], sum[100005], p = 5000011;
int main() {
    scanf("%d%d", &n, &k);
    dp[0] = sum[0] = 1;

    for (int i = 1; i <= n; i++) {
        if (i > k) {
            dp[i] = sum[i - k - 1];
        } else {
            dp[i] = 1;
        }

        sum[i] = sum[i - 1] + dp[i];
        sum[i] %= p;
        //  printf("%d ",dp[i]);
    }

    printf("%d", sum[n]);
    return 0;
}
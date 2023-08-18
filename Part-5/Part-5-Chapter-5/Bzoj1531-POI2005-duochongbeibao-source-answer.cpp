#include <bits/stdc++.h>
using namespace std;
int n, sum;
int m[100001], num[100001];
int dp[200001];
int main() {
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> m[i];

    for (int i = 1; i <= n; i++)
        cin >> num[i];

    cin >> sum;
    memset(dp, 0x3f3f3f3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= num[i]; j++) {
            for (int k = sum; k >= m[i]*j; k--)
                dp[k] = min(dp[k - j * m[i]] + j, dp[k]);
        }
    }

    //  for(int i=1;i<=sum;i++)
    //      cout<<dp[i]<<" ";
    cout << dp[sum];







    return 0;
}
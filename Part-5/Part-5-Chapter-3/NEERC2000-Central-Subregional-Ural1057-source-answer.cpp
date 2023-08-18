#include <iostream>
using namespace std;
typedef long long ll;
const int N = 35;
ll num[N];//转化为B进制
ll dp[N][N];//i位选j个
ll k, b;
void init() {
    for (int i = 0; i < N; i++)
        dp[i][0] = 1;

    for (int i = 0; i < N; i++) {
        for (int j = 1; j < N; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];//分别对应选这一位和不选这一位
        }
    }
}
ll f(ll n) {
    if (n == 0)
        return 0;

    int cnt = 0;

    while (n) {
        num[++cnt] = n % b;
        n /= b;
    }

    ll ans = 0, chosen_pos_num = 0;

    for (int i = cnt; i >= 1; i--) {
        if (num[i] != 0) {
            if (num[i] == 1) {
                ans += dp[i - 1][k - chosen_pos_num];//填0的情况

                //填1时后面不能随便取，到下一位再讨论
                if (chosen_pos_num == k)
                    break;//已放了k个1，不能再放了

                chosen_pos_num++;
            } else if (num[i] > 1) {
                ans += dp[i - 1][k - chosen_pos_num];//填0的情况

                if (k - 1 - chosen_pos_num > 0)
                    ans += dp[i - 1][k - 1 - chosen_pos_num];//填1的情况

                break;//不能填1以上，否则和题中b^x的格式不符，会变成y*b^x
            }
        }

        if (i == 1 && chosen_pos_num == k)
            ans++;
    }

    return ans;
}
int main() {
    ll l, r;

    cin >> l >> r >> k >> b;
    init();
    cout << f(r) - f(l - 1);
    return 0;
}
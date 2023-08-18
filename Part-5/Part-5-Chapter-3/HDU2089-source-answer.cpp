#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int N = 10;
int f[N][10];
void init() {
    for (int i = 0; i <= 9; i++)
        if (i != 4)
            f[1][i] = 1;

    for (int i = 2; i < N; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (j != 4 && k != 4 && j != 6)
                    f[i][j] += f[i - 1][k];
                else if (j == 6 && k != 2) {
                    f[i][j] += f[i - 1][k];
                }
            }
        }
    }
}
int dp(int n) {
    if (!n)
        return 1;

    vector<int>a;

    while (n)
        a.push_back(n % 10), n = n / 10;

    int last = 0;
    int ans = 0;

    for (int i = a.size() - 1; i >= 0; i--) {
        int x = a[i];

        for (int j = 0; j < x; j++) {
            if (j == 4)
                continue;

            if (last == 6 && j == 2)
                continue;

            ans += f[i + 1][j];
        }

        if (x == 4 || last == 6 && x == 2)
            break;
        else
            last = x;

        if (!i)
            ans++;
    }

    return ans;
}
int main() {
    init();

    int l, r;

    while (cin >> l >> r, l || r) {
        cout << dp(r) - dp(l - 1) << endl;
    }


}
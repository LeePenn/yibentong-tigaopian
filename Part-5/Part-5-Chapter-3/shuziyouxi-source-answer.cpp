#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int f[20][10][200], P;

int mod(int x, int y) {
    return (x % y + y) % y;
}

int dp(int n) {
    if (!n)
        return 1;

    vector<int> a;

    while (n) {
        a.push_back(n % 10);
        n /= 10;
    }

    int res = 0, last = 0;

    for (int i = a.size() - 1; i >= 0; i--) {
        int x = a[i];

        for (int j = 0; j < x; j++)
            res += f[i + 1][j][mod(-last, P)];

        last += x;

        if (!i && last % P == 0)
            res++;
    }

    return res;
}

int main() {
    int l, r, i, j, k, x;

    while (cin >> l >> r >> P) {
        memset(f, 0, sizeof(f));

        for (i = 0; i <= 9; i++)
            f[1][i][i % P]++;

        for (i = 2; i < 11; i++)
            for (j = 0; j <= 9; j++)
                for (k = 0; k < P; k++)
                    for (x = 0; x <= 9; x++)
                        f[i][j][k] += f[i - 1][x][mod(k - j, P)];

        cout << dp(r) - dp(l - 1) << endl;
    }

    return 0;
}
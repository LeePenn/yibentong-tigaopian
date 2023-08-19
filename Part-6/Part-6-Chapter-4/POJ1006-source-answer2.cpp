#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 21252;
int a, b, c, d, idx, ans;

int main() {
    cin.tie(0);

    while (1) {
        cin >> a >> b >> c >> d;

        if (a == -1)
            break;

        idx++;
        int ans = (5544 * a + 14421 * b + 1288 * c + N - d) % N;

        if (!ans)
            ans = N;

        cout << "Case " << idx << ": the next triple peak occurs in " << ans << " days." << endl;
    }

    return 0;
}
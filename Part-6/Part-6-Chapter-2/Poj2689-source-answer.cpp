#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5, MAXD = 1e6 + 10;

int l, r;
bool is_prime[MAXN + 10];
vector<int> prime;

bool vis[MAXD];

void get_primes() {
    for (int i = 2; i <= MAXN; i++)
        is_prime[i] = 1;

    for (int i = 2; i * i <= MAXN; i++)
        if (is_prime[i])
            for (int j = i * i; j <= MAXN; j += i)
                is_prime[j] = 0;

    for (int i = 2; i <= MAXN; i++)
        if (is_prime[i])
            prime.push_back(i);
}

int main() {
    get_primes();

    while (cin >> l >> r) {
        memset(vis, 0, sizeof(vis));

        for (int x : prime) {
            //          cout << x << endl;
            if ((long long)x * x > r)
                break;

            for (long long i = l / x * x; i <= r; i += x) {
                //              cout << i << endl;
                if (i >= l && i != x)
                    vis[i - l] = 1;
            }

        }

        int mind = INT_MAX, maxd = 0;
        int x1 = 0, y1, x2, y2;

        for (long long i = l, j = 0; i <= r; i++)
            if (i != 1 && !vis[i - l]) {
                //          cout << i << endl;
                if (j) {
                    int d = i - j;

                    if (d < mind)
                        mind = d, x1 = j, y1 = i;

                    if (d > maxd)
                        maxd = d, x2 = j, y2 = i;
                }

                j = i;
            }

        if (x1 == 0)
            puts("There are no adjacent primes.");
        else
            printf("%d,%d are closest, %d,%d are most distant.\n", x1, y1, x2, y2);
    }
}
#include <bits/stdc++.h>

using namespace std;

const int N = 1000005;
char s[N];
int p[N];
int n;

void work() {
    n = strlen(s + 1);
    p[1] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i + 1] != s[j + 1]) j = p[j];
        if (s[i + 1] == s[j + 1]) j++;
        p[i + 1] = j;
    }
    int len = n - p[n];
    if (n % len == 0) printf("%d\n", n / len);
    else printf("%d\n", 1);
}

int main() {
    while (scanf("%s", s + 1) == 1 && strcmp(s + 1, ".") != 0) {
        work();
    }

    return 0;
}
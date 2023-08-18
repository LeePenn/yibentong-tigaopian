#include <bits/stdc++.h>

using namespace std;

const int N = 1000004;
int n, p[N], p1[N];
char s[N];

void work() {
    p[1] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i + 1] != s[j + 1]) j = p[j];
        if (s[i + 1] == s[j + 1]) j++;
        p[i + 1] = j;
    }
    int n1 = n - p[n];
    if (p[n] >= n / 2) {
        printf("%d\n", n1);
        return;
    }
    for (int i = 1, j = 0; i < n1; i++) {
        while (j > 0 && s[i + 1] != s[j + 1]) j = p1[j];
        if (s[i + 1] == s[j + 1]) j++;
        p1[i + 1] = j;
    } 
    if (n1 % (n1 - p1[n1]) == 0) printf("%d\n", n1 - p1[n1]);
    else printf("1\n");
}

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    work();

    return 0;
}
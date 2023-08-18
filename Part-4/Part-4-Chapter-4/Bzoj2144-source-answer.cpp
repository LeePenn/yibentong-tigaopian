#include <bits/stdc++.h>
using namespace std;
struct node {
    int x, y, z;
} b1, b2;
int read() {
    int f = 1;
    char ch;

    while ((ch = getchar()) < '0' || ch > '9')
        if (ch == '-')
            f = -1;

    int res = ch - '0';

    while ((ch = getchar()) >= '0' && ch <= '9')
        res = res * 10 + ch - '0';

    return res * f;
}
void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }

    if (x > 9)
        write(x / 10);

    putchar(x % 10 + '0');
}
void Get(node &b) {
    if (b.x > b.y)
        swap(b.x, b.y);

    if (b.y > b.z)
        swap(b.y, b.z);

    if (b.x > b.z)
        swap(b.x, b.z);
}
int f1(node &b) {
    int step = 0;
    Get(b);

    while (b.x + b.z != b.y * 2) {
        int d1 = b.y - b.x, d2 = b.z - b.y;

        if (d1 < d2) {
            int p = d2 / d1;

            if (d2 % d1 == 0)
                p--;

            b.x += d1 * p;
            b.y += d1 * p;

            if (b.x > b.y)
                swap(b.x, b.y);

            step += p;
        } else {
            int p = d1 / d2;

            if (d1 % d2 == 0)
                p--;

            b.y -= d2 * p;
            b.z -= d2 * p;

            if (b.y > b.z)
                swap(b.y, b.z);

            step += p;
        }
    }

    return step;
}
bool pan(node b1, node b2) {
    if (b1.x == b2.x && b1.y == b2.y && b1.z == b2.z)
        return 1;
    else
        return 0;
}
node f2(node b, int l) {
    Get(b);

    while (l) {
        int d1 = b.y - b.x, d2 = b.z - b.y;

        if (d1 < d2) {
            int p = d2 / d1;

            if (d2 % d1 == 0)
                p--;

            if (p > l)
                p = l;

            b.x += p * d1;
            b.y += p * d1;

            if (b.x > b.y)
                swap(b.x, b.y);

            l -= p;
        } else {
            int p = d1 / d2;

            if (d1 % d2 == 0)
                p--;

            if (p > l)
                p = l;

            b.y -= p * d2;
            b.z -= p * d2;

            if (b.y > b.z)
                swap(b.y, b.z);

            l -= p;
        }
    }

    return b;
}
int main() {
    b1.x = read();
    b1.y = read();
    b1.z = read();
    b2.x = read();
    b2.y = read();
    b2.z = read();
    Get(b1);
    Get(b2);
    node bb1 = b1, bb2 = b2;
    int t1 = f1(bb1), t2 = f1(bb2);

    if (!pan(bb1, bb2)) {
        printf("NO");
        return 0;
    }

    int d = abs(t1 - t2);

    if (t1 > t2)
        b1 = f2(b1, d);
    else
        b2 = f2(b2, d);

    int l = 0, r = min(t1, t2), ff = 0;

    while (l <= r) {
        int m = l + r >> 1;
        bb1 = f2(b1, m);
        bb2 = f2(b2, m);

        if (pan(bb1, bb2)) {
            ff = m;
            r = m - 1;
        } else
            l = m + 1;
    }

    printf("YES\n");
    write(d + 2 * ff);
    return 0;
}
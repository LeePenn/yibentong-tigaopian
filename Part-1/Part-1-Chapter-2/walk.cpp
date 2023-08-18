#include <bits/stdc++.h>

using namespace std;

struct Line {
    double x1, y1, x2, y2;
}l[3];
double v1, v2, v3;
const double EPS = 1e-6;

double dis(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double check(double k, double x1, double y1) {
    double x2 = (l[2].x2 - l[2].x1) * k + l[2].x1;
    double y2 = (l[2].y2 - l[2].y1) * k + l[2].y1;
    double t1 = dis(l[1].x1, l[1].y1, x1, y1) / v1;
    double t2 = dis(x1, y1, x2, y2) / v3;
    double t3 = dis(l[2].x2, l[2].y2, x2, y2) / v2;
    return t1 + t2 + t3;
}

double calc(double k) {
    double x1 = (l[1].x2 - l[1].x1) * k + l[1].x1;
    double y1 = (l[1].y2 - l[1].y1) * k + l[1].y1;
    double left = 0.0, right = 1.0;
    while (right - left > EPS) {
        double m1 = left + (right - left) / 3, m2 = right - (right - left) / 3;
        if (check(m1, x1, y1) < check(m2, x1, y1)) right = m2;
        else left = m1;
    }
    
    return check(right, x1, y1);
}

int main() {
    cin >> l[1].x1 >> l[1].y1 >> l[1].x2 >> l[1].y2;
    cin >> l[2].x1 >> l[2].y1 >> l[2].x2 >> l[2].y2;
    cin >> v1 >> v2 >> v3;
    double left = 0.0, right = 1.0;
    while (right - left > EPS) {
        double m1 = left + (right - left) / 3, m2 = right - (right - left) / 3;
        if (calc(m1) < calc(m2)) right = m2;
        else left = m1;
    }
    printf("%.2lf\n", calc(right));
    

    return 0;
}
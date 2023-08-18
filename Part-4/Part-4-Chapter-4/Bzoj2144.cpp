#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y, z;
}b1, b2;

void Get(Node &b) {
    if (b.x > b.y) swap(b.x, b.y);
    if (b.y > b.z) swap(b.y, b.z);
    if (b.x > b.z) swap(b.x, b.z);
}

void Read() {
    scanf("%d%d%d", &b1.x, &b1.y, &b1.z);
    scanf("%d%d%d", &b2.x, &b2.y, &b2.z);
    Get(b1); Get(b2);
}

int f1(Node &b) {
    int step = 0;
    Get(b);
    
    while (b.x + b.z != 2 * b.y) {
        int d1 = b.y - b.x, d2 = b.z - b.y;
        
        if (d1 < d2) {
            int p = d2 / d1;
            if (d2 % d1 == 0) p--;
            
            b.x += d1 * p;
            b.y += d1 * p;
            
            step += p;
        } else {
            int p = d1 / d2;
            if (d1 % d2 == 0) p--;
            
            b.y -= d2 * p;
            b.z -= d2 * p;
            
            step += p;
        }
    }
    
    return step;
}

bool judge(const Node &b1, const Node &b2) {
    return b1.x == b2.x && b1.y == b2.y && b1.z == b2.z;
}

Node f2(Node b, int l) {
    Get(b);
    
    while (l) {
        int d1 = b.y - b.x, d2 = b.z - b.y;
        
        if (d1 < d2) {
            int p = d2 / d1;
            
            if (d2 % d1 == 0) p--;
            if (p > l) p = l;
            
            b.x += p * d1;
            b.y += p * d1;
            
            l -= p;
        } else {
            int p = d1 / d2;
            
            if (d1 % d2 == 0) p--;
            if (p > l) p = l;
            
            b.z -= p * d2;
            b.y -= p * d2;
            
            l -= p;
        }
    }
    
    return b;
}

/*
把每个状态看成树上的一个结点，两边向中间跳是向父亲走，中间向两边跳是向两个儿子跳。
问题转化为判断两个结点的根是否相同，所需方案就是树上距离。
可以先通过倍增求出结点到根的距离与根状态。
然后若两个状态根结点一样，就先跳至同一高度，再向上倍增，求 lca 。
关于向上跳的操作，例如 
(1,99999999,100000000) ，为了优化，我们就可以一次性跳到 
(1,2,3) 。
*/
int main() {
    Read();
    
    Node bb1 = b1, bb2 = b2;
    int t1 = f1(bb1), t2 = f1(bb2);
    
    if (!judge(bb1, bb2)) {
        printf("NO\n");
        return 0;
    }
    
    int d = abs(t1 - t2);
    
    if (t1 > t2) b1 = f2(b1, d);
    else b2 = f2(b2, d);

    int l = 0, r = min(t1, t2), ff = 0;
    while (l <= r) {
        int m = (l + r) >> 1;
        bb1 = f2(b1, m);
        bb2 = f2(b2, m);
        if (judge(bb1, bb2)) {
            ff = m;
            r = m - 1;
        } else l = m + 1;
    }
    printf("YES\n%d\n", d + 2 * ff);
    
    return 0;
}
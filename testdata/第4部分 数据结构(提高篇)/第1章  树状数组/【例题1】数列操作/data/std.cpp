#include <cstdio>                  
#include <cstring>  
#include <iostream>  
using namespace std;   
const int MaxN = 1e5 + 10;    //表示定义整型常量，1e5+10即为105+10  
int c[MaxN];  
  //c是树状数组，其中c[i]=a[i-2k+1]+…+a[i](k为i在二进制形式下末尾0的个数)
int n, m, k, a, b;   
int lowbit(int x)              //用lowbit(x)表示2k(k为x在二进制形式下末尾0的个数) 
{  
    return x & (-x);   
}  
void update(int x, int v)  //在序列第x个位置加上v，并在树状数组中修改相应元素
{     
while (x <= n)  
    {  
        c[x] += v;   
        x += lowbit(x);   
    }  
}  
int sum(int x)                 //计算序列中第1个位置到第x个位置的和
{  
    int res = 0;   
    while (x > 0)  
    {  
        res += c[x];   
        x -= lowbit(x);   
    }  
    return res;   
}  
  
int main()  
{  
	freopen("test10.in","r",stdin);
	freopen("test10.out","w",stdout);
    int v;   
    scanf("%d%d", &n, &m);  
    for (int i = 1; i <= n; ++i)  
    {  
        scanf("%d", &v);   
        update(i, v);   
     //开始每个元素的初始值为0，我们读入数列时直接在对应位置增加v即可
    }  
    for (int i = 1; i <= m; ++i)  
    {  
        scanf("%d%d%d", &k, &a, &b);   
        if (k == 0)  
            printf("%d\n", sum(b) - sum(a - 1));   
             //计算区间[a,b]的和时，可以分别算出[1,b]和[1,a-1]的和，相减即为[a,b]的和
        else  
            update(a, b);       //在第a个位置加上b 
    }  
    return 0;   
}  


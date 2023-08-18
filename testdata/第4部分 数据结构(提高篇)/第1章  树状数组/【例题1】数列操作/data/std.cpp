#include <cstdio>                  
#include <cstring>  
#include <iostream>  
using namespace std;   
const int MaxN = 1e5 + 10;    //��ʾ�������ͳ�����1e5+10��Ϊ105+10  
int c[MaxN];  
  //c����״���飬����c[i]=a[i-2k+1]+��+a[i](kΪi�ڶ�������ʽ��ĩβ0�ĸ���)
int n, m, k, a, b;   
int lowbit(int x)              //��lowbit(x)��ʾ2k(kΪx�ڶ�������ʽ��ĩβ0�ĸ���) 
{  
    return x & (-x);   
}  
void update(int x, int v)  //�����е�x��λ�ü���v��������״�������޸���ӦԪ��
{     
while (x <= n)  
    {  
        c[x] += v;   
        x += lowbit(x);   
    }  
}  
int sum(int x)                 //���������е�1��λ�õ���x��λ�õĺ�
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
     //��ʼÿ��Ԫ�صĳ�ʼֵΪ0�����Ƕ�������ʱֱ���ڶ�Ӧλ������v����
    }  
    for (int i = 1; i <= m; ++i)  
    {  
        scanf("%d%d%d", &k, &a, &b);   
        if (k == 0)  
            printf("%d\n", sum(b) - sum(a - 1));   
             //��������[a,b]�ĺ�ʱ�����Էֱ����[1,b]��[1,a-1]�ĺͣ������Ϊ[a,b]�ĺ�
        else  
            update(a, b);       //�ڵ�a��λ�ü���b 
    }  
    return 0;   
}  


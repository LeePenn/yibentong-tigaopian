#include<stdio.h>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
const int mod=2009;
void tt(int v[90][90],int n,int t)//一个n*n的矩阵v[][]的t次方，t>=0，注意取模之前的乘法是否溢出
{
	int e[90][90],a[90][90],i,j,k;
	memcpy(e,v,sizeof(e));
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(i==j)
				v[i][j]=1;
			else
				v[i][j]=0;
	while(t)
	{
		if(t&1)
		{
			memcpy(a,v,sizeof(a));
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
				{
					v[i][j]=0;
					for(k=0;k<n;k++)
						v[i][j]=(v[i][j]+a[i][k]*e[k][j]%mod)%mod;
				}
		}
		memcpy(a,e,sizeof(a));
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			{
				e[i][j]=0;
				for(k=0;k<n;k++)
					e[i][j]=(e[i][j]+a[i][k]*a[k][j]%mod)%mod;
			}
		t/=2;
	}
}
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	int t,n,i,j,z[90][90];
	char adj[16][16];
	scanf("%d%d",&n,&t);
	for(i=0;i<n;i++)
		scanf("%s",adj[i]);
	memset(z,0,sizeof(z));
	for(i=0;i<n;i++)
		for(j=0;j+1<9;j++)
			z[i*9+j][i*9+j+1]=1;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(adj[i][j]!='0')
				z[i*9+adj[i][j]-48-1][j*9]=1;
	tt(z,n*9,t);
	printf("%d\n",z[0*9][(n-1)*9]);
	return 0;
}

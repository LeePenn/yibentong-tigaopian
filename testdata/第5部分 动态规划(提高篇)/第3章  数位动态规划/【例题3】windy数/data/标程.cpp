#include<stdio.h>
#include<algorithm>
using namespace std;
int z[12][10];
int a[12];
int zz(int i,int j)
{
	if(z[i][j]!=-1)
		return z[i][j];
	if(!i)
		return z[i][j]=1;
	z[i][j]=0;
	int k;
	for(k=0;k<10;k++)
		if(abs(j-k)>=2)
			z[i][j]+=zz(i-1,k);
	return z[i][j];
}
int aa(int i)
{
	if(a[i]!=-1)
		return a[i];
	int j;
	a[i]=0;
	for(j=1;j<10;j++)
		a[i]+=zz(i,j);
	return a[i];
}
int tt(int n)
{
	int g,ans,i,j,lx[12];
	g=0;
	while(n)
	{
		lx[g++]=n%10;
		n/=10;
	}
	ans=0;
	g--;
	for(i=g-1;i>=0;i--)
		ans+=aa(i);
	bool ok=true;
	for(i=g;i>=0;i--)
	{
		if(i==g)
		{
			for(j=1;j<lx[i];j++)
				ans+=zz(i,j);
		}
		else if(ok)
		{
			for(j=0;j<lx[i];j++)
				if(abs(j-lx[i+1])>=2)
					ans+=zz(i,j);
			if(abs(lx[i]-lx[i+1])<2)
				ok=false;
		}
	}
	return ans;
}
int main()
{
	freopen("windy.in","r",stdin);
	freopen("windy.out","w",stdout);
	int low,high;
	scanf("%d%d",&low,&high);
	memset(z,0XFF,sizeof(z));
	memset(a,0XFF,sizeof(a));
	printf("%d\n",tt(high+1)-tt(low));
	return 0;
}

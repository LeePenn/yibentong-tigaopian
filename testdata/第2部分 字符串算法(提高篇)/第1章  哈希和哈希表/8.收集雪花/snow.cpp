#include<iostream>
using namespace std;

const long prime=9999991;

long hash[10000000];
long n,t;

int main(){
    freopen("snow0.in","r",stdin);
    freopen("snow0.out","w",stdout);
//    cin>>t;
    t=1;
    for(int k=1;k<=t;k++){
        memset(hash,0,sizeof(hash));
        cin>>n;
        if (n==0) { cout<<0<<endl; continue; }
        long x=0,flag=1,ans=0;
        for(int i=1;i<n;i++){
            scanf("%d",&x);
            x%=prime;
            if(hash[x]>=flag){   //数字x出现过,且在包装内両 
                if(i-flag>ans) ans=i-flag;                 
                flag=hash[x]+1;
            }
            hash[x]=i;
        }
        scanf("%d",&x); x%=prime;
        if((hash[x]>=flag)&&(n-flag>ans)) ans=n-flag;                 
        if((hash[x]< flag)&&(n-flag+1>ans)) ans=n-flag+1;
        cout<<ans<<endl;
    }
    return 0;
}
         

#include<fstream>
#include<cmath>
using namespace std;
ifstream cin("a.in");
ofstream cout("art1.in");
int n,m,k,j,i,x,y;
int main()
{  srand(time(NULL));//�����������   
   for(k=1;k<=6;k++)
   {  cin>>n;m=rand()%1000+2;
      cout<<n<<" "<<m<<endl;  
      for(int i=1;i<=n;i++)
      {  x=rand()%100+1;
         cout<<x<<" ";
      }
      cout<<endl;
   }
   //system("pause"); 
}

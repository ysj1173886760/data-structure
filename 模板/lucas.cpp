#include<iostream>
using namespace std;
const int maxn=1e5+10;
int n,m,p,t;
int a[maxn],b[maxn];
int fpow(int x,int y)
{
    int ans=1;
    while(y)
    {
        if(y&1)ans=1ll*ans*x%p;
        x=1ll*x*x%p;
        y>>=1;
    }
    return ans;
}
void init()
{
    a[1]=a[0]=1;
    b[0]=b[1]=1;
    for(int i=2;i<=p;i++)
        a[i]=1ll*a[i-1]*i%p;
    b[p-1]=p-1;
    for(int i=p-2;i>=1;i--)b[i]=1ll*b[i+1]*(i+1)%p;
}
int c(int x,int y)
{
    
    if(x<y)return 0;
    return 1ll*a[x]*b[x-y]*b[y]%p;
}
int lucas(int x,int y)
{
    if(x<p&&y<p)return c(x,y);
    return lucas(x/p,y/p)*c(x%p,y%p)%p;	
}
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>p;
        init();
        cout<<lucas(n+m,m)<<endl;
    }
    return 0;
}

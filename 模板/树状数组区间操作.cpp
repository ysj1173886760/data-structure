#include<cstdio>
using namespace std;
long long base[200005],delta[200005];
int n,m;
int lowbit(int x)
{
    return x&(-x);
}
long long sum(long long *a,int x)
{
    long long res=0;
    while(x)
    {
        res+=a[x];
        x-=lowbit(x);
    }
    return res;
}
void add(long long *a,int x,int del)
{
    while(x<=n)
    {
        a[x]+=del;
        x+=lowbit(x);
    }
}
int main()
{
    scanf("%d",&n);
    scanf("%d",&m);
    for(int i=1;i<=n;i++)
    {
        int temp=0;
        scanf("%d",&temp);
        add(base,i,temp);
    }
    
    for(int i=1;i<=m;i++)
    {
        int temp=0;
        scanf("%d",&temp);
        if(temp==1)
        {
            int x=0,y=0,k=0;
            scanf("%d%d%d",&x,&y,&k);
            add(base,x,-k*(x-1));
            add(base,y+1,k*y);
            add(delta,x,k);
            add(delta,y+1,-k);
        }
        else 
        {
            int x=0,y=0;
            scanf("%d%d",&x,&y);
            long long ans=0;
            ans-=sum(base,x-1)+sum(delta,x-1)*(x-1);
            ans+=sum(base,y)+sum(delta,y)*y;
            printf("%lld\n",ans);
        }
    }
    return 0;
}

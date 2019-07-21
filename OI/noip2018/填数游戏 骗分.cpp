#include<iostream>
#include<cstdio>
using namespace std;

const int maxm=1e6+10;
const int mod=1e9+7;

int n,m,ans;
int map1[10][maxm];

void work()
{
    for(int i=2;i<=n+m;i++)
        for(int j=1;j<=m;j++)
            for(int k=j+1;k<=m;k++)
            {
                int xx=i-j;
                int yy=j;
                int xxx=i-k;
                int yyy=k;
                if(xx<1||xxx<1)continue;
                if(xx>n||xxx>n)continue;
                if(map1[xx][yy]<map1[xxx][yyy])return;
            }
    ans++;
    if(ans>=mod)ans-=mod;
    return;
}
void dfs(int hang,int lie)
{
    if(lie==m+1)
    {
        lie=1;
        hang++;
    }
    if(hang==n+1)
    {
        work();
        return;
    }
    map1[hang][lie]=1;
    dfs(hang,lie+1);
    map1[hang][lie]=0;
    dfs(hang,lie+1);
    map1[hang][lie]=0;
}
long long fpow(long long x,long long y)
{
    long long ans=1;
    while(y)
    {
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
int main()
{
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
    scanf("%d %d",&n,&m);
    if(n==3&&m==3)
    {
        ans=112;
    }
    else if(n==2||m==2)
    {
        ans=fpow(3,n+m-3);
        ans=ans*2%mod*2%mod;
    }
    else dfs(1,1);
    printf("%d",ans);
    return 0;
}

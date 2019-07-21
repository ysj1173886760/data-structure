#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=13,inf=0x3f3f3f3f;
int n,m,ans=inf,cost,tot;
int map1[maxn][maxn],have[13],dep[13],sum[13],cango[13][13],mincost,nowsort;

void dfs(int num,int where)
{
    if(tot==n)
    {
        ans=min(ans,cost);
        return;
    }
    for(int k=num;k<=tot;k++)
    {
        int i=have[k];
        if(cost+mincost*dep[i]>=ans)return;
        for(int l=where;l<=sum[i];l++)
        {
            int j=cango[i][l];
            if(dep[j]==inf)
            {
                dep[j]=dep[i]+1;
                cost+=dep[i]*map1[i][j];
                have[++tot]=j;
                mincost-=map1[j][cango[j][1]];
                dfs(k,l);
                mincost+=map1[j][cango[j][1]];
                dep[j]=inf;
                cost-=dep[i]*map1[i][j];
                tot--;
            }
        }
        where=1;
    }
}
bool cmp(const int &a,const int &b)
{
    return map1[nowsort][a]<map1[nowsort][b];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    memset(map1,0x3f,sizeof(map1));
    for(int i=1;i<=m;i++)
    {
        int x=0,y=0,z=0;
        cin>>x>>y>>z;
        if(map1[x][y]==inf)
        {
            cango[x][++sum[x]]=y;
            cango[y][++sum[y]]=x;
        }
        map1[x][y]=min(map1[x][y],z);
        map1[y][x]=min(map1[y][x],z);
    }
    for(int i=1;i<=n;i++)
    {
        nowsort=i;
        sort(cango[i]+1,cango[i]+1+sum[i],cmp);
        mincost+=map1[i][cango[i][1]];
    }
    for(int i=1;i<=n;i++)
    {
        memset(dep,0x3f,sizeof(dep));
        mincost-=map1[i][cango[i][1]];
        tot=1;
        have[1]=i;
        dep[i]=1;
        cost=0;
        dfs(1,1);
        mincost+=map1[i][cango[i][1]];
    }
    cout<<ans;
    return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=2e2+10,inf=0x3f3f3f3f;
int n1,n2,n,tot,source,sink,mincost,maxcost;
int dis[maxn],q[maxn],g[maxn],now[maxn],a[maxn],b[maxn],cost[maxn][maxn];
bool vis[maxn];
struct line
{
    int to,next,w,cost;
}edge[maxn*maxn];

void add1(int a,int b,int c,int d)
{
    edge[++tot].to=b;
    edge[tot].w=c;
    edge[tot].cost=d;
    edge[tot].next=g[a];
    g[a]=tot;
}
bool min_spfa()
{
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++)now[i]=g[i];
    int h=0,t=1;
    q[t]=source;
    vis[q[t]]=true;
    dis[q[t]]=0;
    while(h!=t)
    {
        h=h%n+1;
        int x=q[h];
        for(int i=g[x];i;i=edge[i].next)
            if(edge[i].w&&dis[edge[i].to]>dis[x]+edge[i].cost)
            {
                dis[edge[i].to]=dis[x]+edge[i].cost;
                if(!vis[edge[i].to])
                {
                    t=t%n+1;
                    q[t]=edge[i].to;
                    vis[q[t]]=true;
                }
            }
        vis[x]=false;
    }
    return dis[sink]!=0x3f3f3f3f;
}
bool max_spfa()
{
    memset(vis,0,sizeof(vis));
    memset(dis,-0x3f,sizeof(dis));
    for(int i=1;i<=n;i++)now[i]=g[i];
    int h=0,t=1;
    q[t]=source;
    vis[q[t]]=true;
    dis[q[t]]=0;
    while(h!=t)
    {
        h=h%n+1;
        int x=q[h];
        for(int i=g[x];i;i=edge[i].next)
            if(edge[i].w&&dis[edge[i].to]<dis[x]+edge[i].cost)
            {
                dis[edge[i].to]=dis[x]+edge[i].cost;
                if(!vis[edge[i].to])
                {
                    t=t%n+1;
                    q[t]=edge[i].to;
                    vis[q[t]]=true;
                }
            }
        vis[x]=false;
    }
    return dis[sink]>=0;
}
int dfs(int cur,int flow)
{
    vis[cur]=true;
    if(cur==sink)return flow;
    int rest=flow;
    for(int i=now[cur];i;i=edge[i].next)
    {
        now[cur]=i;
        if((!vis[edge[i].to]||edge[i].to==sink)&&edge[i].w&&dis[edge[i].to]==dis[cur]+edge[i].cost)
        {
            int temp=dfs(edge[i].to,min(rest,edge[i].w));
            edge[i].w-=temp;
            edge[i^1].w+=temp;
            rest-=temp;
            if(!rest)break;
        }
    }
    return flow-rest;
}
void min_dinic()
{
    while(min_spfa())
    {
        vis[sink]=true;
        while(vis[sink])
        {
            memset(vis,0,sizeof(vis));
            int temp=dfs(source,inf);
            mincost+=dis[sink]*temp;
        }
    }
}
void max_dinic()
{
    while(max_spfa())
    {
        vis[sink]=true;
        while(vis[sink])
        {
            memset(vis,0,sizeof(vis));
            int temp=dfs(source,inf);
            maxcost+=dis[sink]*temp;
        }
    }
}
void init()
{
    memset(g,0,sizeof(g));
    tot=1;
    for(int i=1;i<=n1;i++)
        for(int j=1;j<=n2;j++)
        {
            int x=i+1,y=j+n1+1;
            add1(x,y,a[i],cost[i][j]);
            add1(y,x,0,-cost[i][j]);
        }
    for(int i=1;i<=n1;i++)add1(1,i+1,a[i],0),add1(i+1,1,0,0);
    for(int i=1;i<=n2;i++)add1(n1+1+i,n,b[i],0),add1(n,n1+1+i,0,0);
}
int main()
{
    scanf("%d %d",&n1,&n2);
    n=n1+n2+2;
    source=1,sink=n;
    for(int i=1;i<=n1;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n2;i++)scanf("%d",&b[i]);
    for(int i=1;i<=n1;i++)
        for(int j=1;j<=n2;j++)
            scanf("%d",&cost[i][j]);
    init();
    min_dinic();
    init();
    max_dinic();
    printf("%d\n%d",mincost,maxcost);
    return 0;
}

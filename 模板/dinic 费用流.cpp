#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

const int maxn=5e3+10,inf=0x3f3f3f3f;
int n,m,source,sink,tot=1,ans,mincost;
int q[maxn],dis[maxn],now[maxn],g[maxn];
bool vis[maxn];
struct line
{
    int to,next,w,cost;
}edge[maxn*20];

void add1(int a,int b,int c,int d)
{
    edge[++tot].to=b;
    edge[tot].w=c;
    edge[tot].cost=d;
    edge[tot].next=g[a];
    g[a]=tot;
}
bool spfa()
{
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
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
    if(dis[sink]==inf)return false;
    else return true;
}
int dfs(int cur,int flow)
{
    vis[cur]=true;
    if(cur==sink)return flow;
    int rest=flow;
    for(int i=now[cur];i;i=edge[i].next)
    {
        now[cur]=i;
        if((!vis[edge[i].to]||sink==edge[i].to)&&edge[i].w&&dis[edge[i].to]==dis[cur]+edge[i].cost)
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
void dinic()
{
    int minn=0;
    while(spfa())
    {
        vis[sink]=true;
        while(vis[sink])
        {
            memset(vis,0,sizeof(vis));
            minn=dfs(source,inf);
            ans+=minn;
            mincost+=dis[sink]*minn;
        }
    }
}

int main()
{
    scanf("%d %d %d %d",&n,&m,&source,&sink);
    for(int i=1;i<=m;i++)
    {
        int x=0,y=0,z=0,k=0;
        scanf("%d %d %d %d",&x,&y,&z,&k);
        add1(x,y,z,k);
        add1(y,x,0,-k);
    }
    dinic();
    printf("%d %d",ans,mincost);
    return 0;
}

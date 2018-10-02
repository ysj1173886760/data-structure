#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;

const int maxn=4e3+10;
const long long inf=0x3f3f3f3f3f3f3f3f;

int n,tot=1,source,sink,newcost,fasttime,fastcost,slowtime,slowcost;
long long mincost;
long long dis[maxn];
int q[maxn],now[maxn],need[maxn],g[maxn];
bool vis[maxn];
struct line
{
    int to,next,cost;
    long long w;
}edge[maxn*10];

void add1(int a,int b,long long c,int d)
{
    edge[++tot].to=b;
    edge[tot].w=c;
    edge[tot].cost=d;
    edge[tot].next=g[a];
    g[a]=tot;
}
bool spfa()
{
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=sink;i++)now[i]=g[i];
    int h=0,t=1;
    q[t]=source;
    vis[q[t]]=true;
    dis[q[t]]=0;
    while(h!=t)
    {
        h=h%sink+1;
        int x=q[h];
        for(int i=g[x];i;i=edge[i].next)
            if(dis[edge[i].to]>dis[x]+edge[i].cost&&edge[i].w)
            {
                dis[edge[i].to]=dis[x]+edge[i].cost;
                if(!vis[edge[i].to])
                {
                    t=t%sink+1;
                    q[t]=edge[i].to;
                    vis[q[t]]=true;
                }
            }
        vis[x]=false;
    }
    return dis[sink]!=inf;
}
int dfs(int cur,long long flow)
{
    vis[cur]=true;
    if(cur==sink)return flow;
    long long rest=flow;
    for(int i=now[cur];i;i=edge[i].next)
    {
        now[cur]=i;
        if((!vis[edge[i].to]||edge[i].to==sink)&&edge[i].w&&dis[edge[i].to]==dis[cur]+edge[i].cost)
        {
            long long temp=dfs(edge[i].to,min(rest,edge[i].w));
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
    while(spfa())
    {
        vis[sink]=true;
        while(vis[sink])
        {
            memset(vis,0,sizeof(vis));
            int minn=dfs(source,inf);
            mincost+=minn*dis[sink];
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&need[i]);
    scanf("%d %d %d %d %d",&newcost,&fasttime,&fastcost,&slowtime,&slowcost);
    source=1,sink=2*n+2;
    for(int i=1;i<=n;i++)
    {
        add1(1,i+1,need[i],newcost);
        add1(i+1,1,0,-newcost);
        
        add1(i+1,sink,need[i],0);
        add1(sink,i+1,0,0);
        
        add1(1,i+1+n,need[i],0);
        add1(i+1+n,1,0,0);
        
        if(i!=n)
        {
            add1(i+1+n,i+2+n,inf,0);
            add1(i+2+n,i+1+n,0,0);
        }
        
        if(i+fasttime<=n)
        {
            add1(i+1+n,i+1+fasttime,inf,fastcost);
            add1(i+1+fasttime,i+1+n,0,-fastcost);
        }
        
        if(i+slowtime<=n)
        {
            add1(i+1+n,i+1+slowtime,inf,slowcost);
            add1(i+1+slowtime,i+1+n,0,-slowcost);
        }
    }
    dinic();
    printf("%lld",mincost);
    return 0;
}

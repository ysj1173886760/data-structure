#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=1e2+10;
const int inf=0x3f3f3f3f;

int n,tot=1,mincost,source,sink,sum;
int have[maxn],g[maxn],dis[maxn],q[maxn],now[maxn];
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
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    for(int i=0;i<=n+1;i++)now[i]=g[i];
    int h=0,t=1;
    q[t]=source;
    vis[q[t]]=true;
    dis[q[t]]=0;
    while(h!=t)
    {
        h=h%(n+2)+1;
        int x=q[h];
        for(int i=g[x];i;i=edge[i].next)
            if(edge[i].w&&dis[edge[i].to]>dis[x]+edge[i].cost)
            {
                dis[edge[i].to]=dis[x]+edge[i].cost;
                if(!vis[edge[i].to])
                {
                    t=t%(n+2)+1;
                    q[t]=edge[i].to;
                    vis[q[t]]=true;
                }
            }
        vis[x]=false;
    }
    return dis[sink]!=inf;
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
void dinic()
{
    while(spfa())
    {
        vis[sink]=1;
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
    for(int i=1;i<=n;i++)scanf("%d",&have[i]),sum+=have[i];
    sum/=n;
    source=0,sink=n+1;
    for(int i=1;i<=n;i++)
    {
        int temp=have[i]-sum;
        if(temp>0)add1(0,i,temp,0),add1(i,0,0,0);
        if(temp<0)add1(i,n+1,-temp,0),add1(n+1,i,0,0);
    }
    for(int i=1;i<=n;i++)
    {
        int pre=i-1,nxt=i+1;
        if(pre==0)pre=n;
        if(nxt==n+1)nxt=1;
        add1(i,pre,inf,1);
        add1(pre,i,0,-1);
        add1(i,nxt,inf,1);
        add1(nxt,i,0,-1);
    }
    dinic();
    printf("%d",mincost);
    return 0;
}

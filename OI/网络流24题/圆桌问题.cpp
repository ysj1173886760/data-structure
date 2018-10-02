#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=5e2+10;
const int inf=0x3f3f3f3f;

int n1,n2,n,source,sink,tot=1,sum,ans;
int dep[maxn],q[maxn],now[maxn],g[maxn];
bool vis[maxn];
struct line
{
    int to,next,w;
}edge[maxn*maxn];

bool bfs()
{
    for(int i=1;i<=n;i++)now[i]=g[i],vis[i]=false;
    int h=0,t=1;
    q[t]=source;
    vis[q[t]]=true;
    dep[q[t]]=1;
    while(h!=t)
    {
        for(int i=g[q[++h]];i;i=edge[i].next)
            if(edge[i].w&&!vis[edge[i].to])
            {
                dep[edge[i].to]=dep[q[h]]+1;
                if(edge[i].to==sink)return true;
                q[++t]=edge[i].to;
                vis[q[t]]=true;
            }
    }
    return false;
}
int dfs(int cur,int flow)
{
    if(cur==sink)return flow;
    int rest=flow;
    for(int i=now[cur];i;i=edge[i].next)
    {
        now[cur]=i;
        if(edge[i].w&&dep[edge[i].to]==dep[cur]+1)
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
    while(bfs())
        while(minn=dfs(source,inf))ans+=minn;
}
void add1(int a,int b,int c)
{
    edge[++tot].to=b;
    edge[tot].w=c;
    edge[tot].next=g[a];
    g[a]=tot;
}
int main()
{
    scanf("%d %d",&n1,&n2);
    n=n1+n2+2;
    for(int i=1;i<=n1;i++)
    {
        int x=0;
        scanf("%d",&x);
        sum+=x;
        add1(1,i+1,x);
        add1(i+1,1,0);
    }
    for(int i=1;i<=n2;i++)
    {
        int x=0;
        scanf("%d",&x);
        add1(i+n1+1,n,x);
        add1(n,i+n1+1,0);
    }
    for(int i=1;i<=n1;i++)
        for(int j=1;j<=n2;j++)
        {
            int x=i+1,y=j+1+n1;
            add1(x,y,1);
            add1(y,x,0);
        }
    source=1,sink=n;
    dinic();
    if(ans==sum)
    {
        printf("1\n");
        for(int i=1;i<=n1;i++)
        {
            for(int j=g[i+1];j;j=edge[j].next)
                if(!edge[j].w)printf("%d ",edge[j].to-n1-1);
            printf("\n");
        }
    }
    else printf("0\n");
    return 0;
}

#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

const int maxn=1e5+10;
const int inf=0x3f3f3f3f;

int n,m,k,p,tot;
int g[maxn],dis[maxn],dp[maxn][60],q[maxn],rec[maxn][60];
bool vis[maxn],flag;
struct line
{
    int to,next,w;
}edge[maxn*2];
struct node
{
    int id,w;
    node(int iid,int ww){id=iid,w=ww;}
};
struct saveedge
{
    int x,y,z;
}se[maxn*2];
priority_queue<node>pq;

bool operator<(const node &a,const node &b)
{
    return a.w>b.w;
}
void add1(int a,int b,int c)
{
    edge[++tot].to=b;
    edge[tot].w=c;
    edge[tot].next=g[a];
    g[a]=tot;
}
void spfa()
{
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    int h=0,t=1;
    q[t]=1;
    vis[q[t]]=true;
    dis[q[t]]=0;
    while(h!=t)
    {
        h=h%n+1;
        int x=q[h];
        int temp=g[x];
        while(temp)
        {
            if(dis[edge[temp].to]>dis[x]+edge[temp].w)
            {
                dis[edge[temp].to]=dis[x]+edge[temp].w;
                if(!vis[edge[temp].to])
                {
                    t=t%n+1;
                    q[t]=edge[temp].to;
                    vis[q[t]]=true;
                }
            }
            temp=edge[temp].next;
        }
        vis[x]=false;
    }
}
int dfs(int cur,int sum)
{
//	cout<<cur<<" "; 
    if(flag)return 0;
    if(sum<0)return 0;
    if(dp[cur][sum])return dp[cur][sum];
    if(cur==1)dp[cur][sum]=1;
    else dp[cur][sum]=0;
    rec[cur][sum]++;
    if(rec[cur][sum]>1)
    {
        flag=true;
        return 0;
    }
    for(int i=g[cur];i;i=edge[i].next)
    {
        int remain1=sum-(dis[edge[i].to]+edge[i].w-dis[cur]);
        dp[cur][sum]=(dp[cur][sum]+dfs(edge[i].to,remain1))%p;
    }
    return dp[cur][sum];
}
int main()
{
//	freopen("test.in","r",stdin);
    int t=0;
    scanf("%d",&t);
    while(t--)
    {
        memset(g,0,sizeof(g));
        memset(dp,0,sizeof(dp));
        tot=0;
        scanf("%d %d %d %d",&n,&m,&k,&p);
        for(int i=1;i<=m;i++)
        {
            int x=0,y=0,z=0;
            scanf("%d %d %d",&x,&y,&z);
            add1(x,y,z);
            se[i].x=x,se[i].y=y,se[i].z=z;
        }
        spfa();
        tot=0;
        memset(g,0,sizeof(g));
        memset(rec,0,sizeof(rec));
        flag=false;
        for(int i=1;i<=m;i++)add1(se[i].y,se[i].x,se[i].z);
        int ans=dfs(n,k);
        if(flag)printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=5e3+10;

int n,m,cnt,tot,now;
int ans[maxn],temp[maxn],sum[maxn],g[maxn];
bool vis[maxn],map1[maxn][maxn];
struct rec
{
    int x,y,id;
}se[maxn*2];
struct line
{
    int to,next,id;
}edge[maxn*2];

void add1(int a,int b,int c)
{
    edge[++tot].to=b;
    edge[tot].id=c;
    edge[tot].next=g[a];
    g[a]=tot;
}
void dfs1(int cur)
{
    temp[++cnt]=cur;
    vis[cur]=true;
    for(int i=g[cur];i;i=edge[i].next)
    {
    	if(edge[i].id==now*2||edge[i].id==now*2-1)continue;
    	if(vis[edge[i].to])continue;
    	dfs1(edge[i].to);
    }
}
bool cmp(const rec &a,const rec &b)
{
    return a.y>b.y;
} 
void work60()
{
    dfs1(1);
    for(int i=1;i<=cnt;i++)printf("%d ",temp[i]);
}
void work100()
{
    memset(ans,0x3f,sizeof(ans));
    for(int i=1;i<=m;i++)
    {
        cnt=0;
        now=i;
        memset(vis,0,sizeof(vis));
        dfs1(1);
        bool flag=false;
        if(cnt!=n)continue;
        for(int i=1;i<=n;i++)
            if(temp[i]<ans[i])
            {
                flag=true;
                break;
            }
            else if(ans[i]<temp[i])break;
        if(flag)for(int i=1;i<=n;i++)ans[i]=temp[i];
    }
    for(int i=1;i<=n;i++)printf("%d ",ans[i]);
}
int main()
{
//	freopen("travel.in","r",stdin);
//	freopen("travel.out","w",stdout);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x=0,y=0;
        scanf("%d %d",&x,&y);
        se[i*2-1].x=x;
        se[i*2-1].y=y;
        se[i*2-1].id=i*2-1;
        se[i*2].x=y;
        se[i*2].y=x;
        se[i*2].id=i*2;
    }
    sort(se+1,se+1+2*m,cmp);
    for(int i=1;i<=2*m;i++)add1(se[i].x,se[i].y,se[i].id);
    if(m==n-1)work60();
    else work100();
    return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=1e5+10;
const long long inf=0x3f3f3f3f3f3f3f3f;

int n,tot,m;
char op[10];
int g[maxn],requ[maxn];
long long w[maxn],dp[maxn][2];
struct line
{
    int to,next;
}edge[maxn*2];

void add1(int a,int b)
{
    edge[++tot].to=b;
    edge[tot].next=g[a];
    g[a]=tot;
}
void dfs(int cur,int fa)
{
    if(requ[cur]==-1)
    {
        dp[cur][1]=w[cur];
        dp[cur][0]=0;
    }
    else if(requ[cur]==1)
    {
        dp[cur][1]=w[cur];
    }
    else if(requ[cur]==0)
    {
        dp[cur][0]=0;
    }
    for(int i=g[cur];i;i=edge[i].next)
    {
        if(edge[i].to==fa)continue;
        dfs(edge[i].to,cur);
        dp[cur][1]+=min(dp[edge[i].to][1],dp[edge[i].to][0]);
        dp[cur][0]+=dp[edge[i].to][1];
    }
}
void work44()
{
    for(int i=1;i<=m;i++)
    {
        int a=0,b=0,x=0,y=0;
        scanf("%d %d %d %d",&a,&x,&b,&y);
        memset(dp,0x3f,sizeof(dp));
        memset(requ,-1,sizeof(requ));
        requ[a]=x;
        requ[b]=y;
        dfs(1,1);
        long long temp=min(dp[1][1],dp[1][0]);
        if(temp>=inf)printf("-1\n");
        else printf("%lld\n",temp);
    //	printf("%lld",inf);
    }
}
int main()
{
//	freopen("defense.in","r",stdin);
//	freopen("defense.out","w",stdout);
    scanf("%d %d %s",&n,&m,op);
    for(int i=1;i<=n;i++)scanf("%lld",&w[i]);
    for(int i=1;i<n;i++)
    {
        int x=0,y=0;
        scanf("%d %d",&x,&y);
        add1(x,y);
        add1(y,x);
    }
    if(n<=2000)work44();
    else work44();//不会了QAQ
    //为什么不能让我多捞点分QAQ 
    //RP++
    return 0;
}

#include<iostream>
#include<cstring>
using namespace std;
const int maxn=1e4+10;
struct line
{
	int to,next;
}edge[10*maxn],nedge[maxn];
int n,tot,m,clk,top,sccnum,ntot;
int w[maxn],dfn[maxn],low[maxn],g[maxn],sccid[maxn],stack[maxn],nw[maxn],ng[maxn],ans,dp[maxn];
bool vis[maxn];
void add1(int a,int b)
{
	edge[++tot].to=b;
	edge[tot].next=g[a];
	g[a]=tot;
}
void add2(int a,int b)
{
	nedge[++ntot].to=b;
	nedge[ntot].next=ng[a];
	ng[a]=ntot;
}
void dfs(int cur)
{
	dfn[cur]=low[cur]=++clk;
	vis[cur]=true;
	stack[++top]=cur;
	for(int i=g[cur];i;i=edge[i].next)
	{
		if(!dfn[edge[i].to])
		{
			dfs(edge[i].to);
			low[cur]=min(low[edge[i].to],low[cur]);
		}
		else if(vis[edge[i].to])low[cur]=min(low[cur],dfn[edge[i].to]);
	}
	if(dfn[cur]==low[cur])
	{
		sccid[cur]=++sccnum;
		vis[cur]=false;
		nw[sccnum]+=w[cur];
		while(stack[top]!=cur)
		{
			sccid[stack[top]]=sccnum;
			vis[stack[top]]=false;
			nw[sccnum]+=w[stack[top]];
			top--;
		}
		top--;
	}
}
int dfs1(int cur)
{
	if(dp[cur])return dp[cur];
	for(int i=ng[cur];i;i=nedge[i].next)dp[cur]=max(dfs1(nedge[i].to),dp[cur]);
	dp[cur]+=nw[cur];
	return dp[cur];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>w[i];
	for(int i=1;i<=m;i++)
	{
		int x=0,y=0;
		cin>>x>>y;
		add1(x,y);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])dfs(i);
	for(int i=1;i<=n;i++)
		for(int temp=g[i];temp;temp=edge[temp].next)
			if(sccid[edge[temp].to]!=sccid[i])add2(sccid[i],sccid[edge[temp].to]);
	for(int i=1;i<=sccnum;i++)ans=max(ans,dfs1(i));
	cout<<ans;
	return 0;
}

#include<iostream>
using namespace std;
const int maxn=1e5+10;
struct line
{
	int to,next;
}edge[maxn*2];
int n,m,tot,clk,ans,dfn[maxn],low[maxn],g[maxn];
bool cutp[maxn];
void add1(int a,int b)
{
	edge[++tot].to=b;
	edge[tot].next=g[a];
	g[a]=tot;
}
void dfs(int cur,int fa)
{
	int sum=0;
	dfn[cur]=low[cur]=++clk;
	for(int i=g[cur];i;i=edge[i].next)
	{
		if(edge[i].to==fa)continue;
		if(!dfn[edge[i].to])
		{
			dfs(edge[i].to,cur);
			low[cur]=min(low[cur],low[edge[i].to]);
			sum++;
			if(low[edge[i].to]>=dfn[cur]&&cur!=fa&&!cutp[cur])ans++,cutp[cur]=true;	//防止重复，因为可能出现大于等于两棵子树满足low>=dfn 
		}
		else low[cur]=min(low[cur],dfn[edge[i].to]);
	}
	if(fa==cur&&sum>=2)ans++,cutp[cur]=true;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x=0,y=0;
		cin>>x>>y;
		add1(x,y);
		add1(y,x);
	}
	for(int i=1;i<=n;i++)if(!dfn[i])dfs(i,i);
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)if(cutp[i])cout<<i<<" ";
	return 0;
}

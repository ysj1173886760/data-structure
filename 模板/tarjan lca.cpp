#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=3e4+10;
int n,m,tot,qtot,ans;
int dep[maxn],g[maxn],query_g[maxn],fa[maxn];
bool vis[maxn];

struct line
{
	int to,next;
}edge[maxn*2],query_edge[maxn*2];

int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void add1(int a,int b)
{
	edge[++tot].to=b;
	edge[tot].next=g[a];
	g[a]=tot;
}
void add_query(int a,int b)
{
	query_edge[++qtot].to=b;
	query_edge[qtot].next=query_g[a];
	query_g[a]=qtot;
}
void dfs(int cur,int f)
{
	fa[cur]=cur;
	dep[cur]=dep[f]+1;
	for(int i=g[cur];i;i=edge[i].next)
	{
		if(edge[i].to==f)continue;
		dfs(edge[i].to,cur);
		fa[edge[i].to]=cur;
	}
	vis[cur]=true;
	for(int i=query_g[cur];i;i=query_edge[i].next)
		if(vis[query_edge[i].to])
			ans+=dep[cur]+dep[query_edge[i].to]-2*dep[find(query_edge[i].to)];
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x=0,y=0;
		scanf("%d %d",&x,&y);
		add1(x,y);
		add1(y,x);
	}
	scanf("%d",&m);
	int now=0;
	for(int i=1;i<=m;i++)
	{
		int x=0;
		scanf("%d",&x);
		if(now)add_query(x,now),add_query(now,x);
		now=x;
	}
	dfs(1,1);
	printf("%d",ans);
	return 0;
}

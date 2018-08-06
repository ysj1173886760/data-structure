#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=5e5+10;
int n,m,now,tot,s;
int top[maxn],dep[maxn],son[maxn],size[maxn],dfn[maxn],g[maxn],fa[maxn];
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
void dfs1(int cur,int f)
{
	dep[cur]=dep[f]+1;
	fa[cur]=f;
	size[cur]=1;
	for(int i=g[cur],maxson=0;i;i=edge[i].next)
	{
		if(edge[i].to==f)continue;
		dfs1(edge[i].to,cur);
		size[cur]+=size[edge[i].to];
		if(size[edge[i].to]>maxson)maxson=size[edge[i].to],son[cur]=edge[i].to;
	}
}
void dfs2(int cur,int tp)
{
	dfn[cur]=++now;
	top[cur]=tp;
	if(!son[cur])return;
	dfs2(son[cur],tp);
	for(int i=g[cur];i;i=edge[i].next)
		if(edge[i].to!=fa[cur]&&edge[i].to!=son[cur])dfs2(edge[i].to,edge[i].to);
}
inline int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		x=fa[top[x]];
	}
	return dep[x]>dep[y]?y:x;
}
int main()
{
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<n;i++)
	{
		int x=0,y=0;
		scanf("%d%d",&x,&y);
		add1(x,y);
		add1(y,x);
	}
	dfs1(s,0);
	dfs2(s,s);
	for(int i=1;i<=m;i++)
	{
		int x=0,y=0;
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
	return 0;
}

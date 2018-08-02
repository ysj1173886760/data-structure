#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=500050;
struct line
{
	int to,next;
}edge[2*maxn];
int n,m,s,tot;
int g[maxn],dep[maxn],log[maxn],fa[maxn][50];
void add1(int a,int b)
{
	edge[++tot].to=b;
	edge[tot].next=g[a];
	g[a]=tot;
}
void dfs(int u,int pre)
{
	fa[u][0]=pre;
	dep[u]=dep[pre]+1;
	for(int i=1;(1<<i)<=dep[u];i++)fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=g[u];i;i=edge[i].next)if(edge[i].to!=pre)dfs(edge[i].to,u);
}
int lca(int x,int y)
{
	if(dep[x]<dep[y])x^=y^=x^=y;
	while(dep[x]>dep[y])x=fa[x][log[dep[x]-dep[y]]];
	if(x==y)return x;
	for(int k=log[dep[x]];k>=0;k--)
		if(fa[x][k]!=fa[y][k])x=fa[x][k],y=fa[y][k];
	return fa[x][0];
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
	dfs(s,s);
	for(int i=1;i<=n;i++)log[i]=log[i-1]+(1<<log[i-1]+1==i);
	for(int i=1;i<=m;i++)
	{
		int x=0,y=0;
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
	return 0;
}

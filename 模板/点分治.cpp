#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=1e4+10;

struct line
{
	int to,w,next;
}edge[maxn*2];

int n,m,tot,root,cnt,sn;
int g[maxn],size[maxn],maxson[maxn],w[maxn],dis[maxn],ans[110],que[110];
bool vis[maxn];

void add1(int a,int b,int c)
{
	edge[++tot].to=b;
	edge[tot].w=c;
	edge[tot].next=g[a];
	g[a]=tot;
}
void dfs1(int cur,int f)
{
	size[cur]=1;
	maxson[cur]=0;
	for(int i=g[cur];i;i=edge[i].next)
	{
		if(edge[i].to==f||vis[edge[i].to])continue;
		dfs1(edge[i].to,cur);
		size[cur]+=size[edge[i].to];
		if(size[edge[i].to]>maxson[cur])maxson[cur]=size[edge[i].to];
	}
	maxson[cur]=max(maxson[cur],sn-size[cur]);
	if(maxson[cur]<maxson[root])root=cur;
}
void dfs2(int cur,int f)
{
	w[++cnt]=dis[cur];
	for(int i=g[cur];i;i=edge[i].next)
	{
		if(edge[i].to==f||vis[edge[i].to])continue;
		dis[edge[i].to]=dis[cur]+edge[i].w;
		dfs2(edge[i].to,cur);
	}
}
void solve(int cur,int pre,int op)
{
	dis[cur]=pre;
	cnt=0;
	dfs2(cur,cur);
	sort(w+1,w+1+cnt);
	for(int i=1;i<=m;i++)
		for(int l=1,r=cnt;l<r;)
		{
			if(w[l]+w[r]==que[i])ans[i]+=op;
			if(w[l]+w[r]<=que[i])l++;
			else r--;
		}
}
void dfs3(int cur)
{
	solve(cur,0,1);
	vis[cur]=true;
	for(int i=g[cur];i;i=edge[i].next)
	{
		if(vis[edge[i].to])continue;
		solve(edge[i].to,edge[i].w,-1);
		sn=size[edge[i].to];
		root=0;
		dfs1(edge[i].to,edge[i].to);
		dfs3(edge[i].to);
	}
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int x=0,y=0,z=0;
		scanf("%d %d %d",&x,&y,&z);
		add1(x,y,z);
		add1(y,x,z);
	}
	for(int i=1;i<=m;i++)scanf("%d",&que[i]);
	maxson[0]=0x3f3f3f3f;
	sn=n;
	dfs1(1,1);
	dfs3(root);
	for(int i=1;i<=m;i++)if(ans[i]>0)printf("AYE\n");
	else printf("NAY\n");
	return 0;
} 

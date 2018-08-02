#include<cstdio>
#define mid ((l+r)>>1)
using namespace std;
const int maxn=1e5+50;
struct line
{
	int to,next;
}edge[2*maxn];
int n,m,r,p,now,tot;
int w[maxn],g[maxn],fa[maxn],size[maxn],son[maxn],dep[maxn],dfn[maxn],nw[maxn],top[maxn],lazy[4*maxn],sum[4*maxn];
int min1(const int &a,const int &b)
{
	if(a>b)return b;
	return a;
}
int max1(const int &a,const int &b)
{
	if(a>b)return a;
	return b;
}
void add1(int a,int b)
{
	edge[++tot].to=b;
	edge[tot].next=g[a];
	g[a]=tot;
}
void dfs1(int x,int f)
{
	dep[x]=dep[f]+1;
	fa[x]=f;
	size[x]=1;
	for(int i=g[x],maxson=0;i;i=edge[i].next)
	{
		if(edge[i].to==f)continue;
		dfs1(edge[i].to,x);
		size[x]+=size[edge[i].to];
		if(size[edge[i].to]>maxson)maxson=size[edge[i].to],son[x]=edge[i].to;
	}
}
void dfs2(int x,int tp)
{
	dfn[x]=++now;
	nw[now]=w[x];
	top[x]=tp;
	if(!son[x])return;
	dfs2(son[x],tp);
	for(int i=g[x];i;i=edge[i].next)
	{
		if(edge[i].to==fa[x]||edge[i].to==son[x])continue;
		dfs2(edge[i].to,edge[i].to);
	}
}
void build(int t,int l,int r)
{
	if(l==r)
	{
		sum[t]=nw[l]%p;
		return;
	}
	build(t<<1,l,mid);
	build(t<<1|1,mid+1,r);
	sum[t]=(sum[t<<1]+sum[t<<1|1])%p;
}
void pushdown(int t,int len)
{
	sum[t]=(sum[t]+lazy[t]*len)%p;
	if(len!=1)
	{
		lazy[t<<1]+=lazy[t];
		lazy[t<<1|1]+=lazy[t];
	}
	lazy[t]=0;
}
int query(int t,int l,int r,int x,int y)
{
	if(lazy[t])pushdown(t,r-l+1);
	if(x<=l&&r<=y)return sum[t];
	int temp=0;
	if(x<=mid)temp+=query(t<<1,l,mid,x,y);
	if(y>mid)temp+=query(t<<1|1,mid+1,r,x,y);
	return temp%p;
}
int query1(int x,int y)
{
	int ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])x^=y^=x^=y;
		ans=(ans+query(1,1,n,dfn[top[x]],dfn[x]))%p;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])x^=y^=x^=y;
	ans=(ans+query(1,1,n,dfn[x],dfn[y]))%p;
	return ans;
}
int query2(int x)
{
	return query(1,1,n,dfn[x],dfn[x]+size[x]-1);
}
void update(int t,int l,int r,int x,int y,int z)
{
	if(lazy[t])pushdown(t,r-l+1);
	if(x<=l&&r<=y)
	{
		lazy[t]+=z;
		return;
	}
	int temp=min1(r,y)-max1(l,x)+1;
	sum[t]=(sum[t]+temp*z)%p;
	if(x<=mid)update(t<<1,l,mid,x,y,z);
	if(y>mid)update(t<<1|1,mid+1,r,x,y,z);
}
void update1(int x,int y,int z)
{
	z%=p;
	while(top[x]!=top[y])
	{
		if(dfn[top[x]]<dfn[top[y]])x^=y^=x^=y;
		update(1,1,n,dfn[top[x]],dfn[x],z);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])x^=y^=x^=y;
	update(1,1,n,dfn[x],dfn[y],z);
}
void update2(int x,int z)
{
	z%=p;
	update(1,1,n,dfn[x],dfn[x]+size[x]-1,z);
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&r,&p);
	for(int i=1;i<=n;i++)scanf("%d",&w[i]);
	for(int i=1;i<n;i++)
	{
		int x=0,y=0;
		scanf("%d%d",&x,&y);
		add1(x,y);
		add1(y,x);
	}
	dfs1(r,0);
	dfs2(r,r);
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int op=0,x=0,y=0,z=0;
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d",&x,&y,&z);
			update1(x,y,z);
		}
		else if(op==2)
		{
			scanf("%d%d",&x,&y);
			printf("%d\n",query1(x,y));
		}
		else if(op==3)
		{
			scanf("%d%d",&x,&z);
			update2(x,z);
		}
		else 
		{
			scanf("%d",&x);
			printf("%d\n",query2(x));
		}
	}
	return 0;
}

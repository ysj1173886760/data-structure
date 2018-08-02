#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=10000;
int n,m,tot,t;
struct line
{
	int w,to,next;
}edge[maxn];
int dis[maxn],g[maxn],cnt[maxn],q[maxn];
bool vis[maxn],flag;
void add1(int a,int b,int c)
{
	edge[++tot].to=b;
	edge[tot].w=c;
	edge[tot].next=g[a];
	g[a]=tot;
}
void spfa(int s)
{
	int h=0,t=1;
	q[t]=s;
	dis[s]=0;
	vis[s]=true;
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
					cnt[q[t]]++;
					if(cnt[q[t]]>n)
					{
						flag=true;
						return;
					}
				}
			}
			temp=edge[temp].next;
		}
		vis[x]=false;
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		tot=0;
		memset(vis,0,sizeof(vis));
		memset(dis,0x3f,sizeof(dis));
		memset(g,0,sizeof(g));
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=m;i++)
		{
			int x=0,y=0,z=0;
			scanf("%d%d%d",&x,&y,&z);
			add1(x,y,z);
			if(z>=0)add1(y,x,z);
		}
		for(int i=1;i<=n;i++)add1(0,i,0);
		flag=false;
		n++;
		spfa(0);
		if(flag)printf("YE5\n");
		else printf("N0\n");
	}
	return 0;
}



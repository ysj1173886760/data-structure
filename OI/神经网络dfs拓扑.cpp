#include<iostream>
using namespace std;
struct line
{
	int to,w,next;
}edge[100005];
int n,tot,p,now;
int u[101],c[101],g[101],s[100001],ind[101],outd[101];
bool vis[101];
void add1(int a,int b,int c)
{
	edge[++tot].to=b;
	edge[tot].w=c;
	edge[tot].next=g[a];
	g[a]=tot;
}
void dfs(int u)
{
	vis[u]=true;
	int temp=g[u];
	while(temp)
	{
		if(!vis[edge[temp].to])dfs(edge[temp].to);
		temp=edge[temp].next;
	}
	s[now--]=u;
}
void toposort()
{
	now=n;
	for(int i=1;i<=n;i++)if(ind[i]==0&&vis[i]==false)dfs(i);
}
int main()
{
	cin>>n>>p;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i]>>u[i];
		if(!c[i])c[i]-=u[i];
	}
	for(int i=1;i<=p;i++)
	{
		int x=0,y=0,z=0;
		cin>>x>>y>>z;
		add1(x,y,z);
		ind[y]++;
		outd[x]++;
	}
	toposort();
	for(int i=1;i<=n;i++)
	{
		if(c[s[i]]<=0)continue;
		int temp=g[s[i]];
		while(temp)
		{
			c[edge[temp].to]+=c[s[i]]*edge[temp].w;
			temp=edge[temp].next;
		}
	}
	int flag=0;
	for(int i=1;i<=n;i++)
	{
		if(outd[i]==0&&c[i]>0)
		{
			cout<<i<<" "<<c[i]<<endl;
			flag++;
		}
	}
	if(!flag)cout<<"NULL";
	return 0;
}

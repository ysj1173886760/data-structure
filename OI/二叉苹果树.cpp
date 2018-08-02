#include<iostream>
#include<cstring>
using namespace std;
struct line
{
	int w,to,next;
}edge[500];
struct node
{
	int l,r;
}t[101];
int n,q,tot,dp[101][101],g[101];	//dp[i][j] 根节点为i时剩余j个点的最大值 
void add1(int a,int b,int c)
{
	edge[++tot].to=b;
	edge[tot].w=c;
	edge[tot].next=g[a];
	g[a]=tot;
}
void build(int x,int fa)
{
	int temp=g[x];
	while(temp)
	{
		if(edge[temp].to==fa){temp=edge[temp].next;continue;}
		dp[edge[temp].to][1]=edge[temp].w;
		if(t[x].l==0)t[x].l=edge[temp].to;
		else t[x].r=edge[temp].to;
		build(edge[temp].to,x);
		temp=edge[temp].next;
	}
}
int dfs(int x,int m)
{
	if(dp[x][m]!=0)return dp[x][m];
	if(x==1&&m==1)return 0;
	if(m==0||x==0)return 0;
	int sum=0;
	for(int i=0;i<m;i++)
		sum=max(sum,dfs(t[x].l,i)+dfs(t[x].r,m-i-1)+dp[x][1]);
	dp[x][m]=sum;
	return sum;
}
int main()
{
	cin>>n>>q;
	for(int i=1;i<n;i++)
	{
		int x=0,y=0,z=0;
		cin>>x>>y>>z;
		add1(x,y,z);
		add1(y,x,z);
	}
	build(1,1);
	cout<<dfs(1,q+1);	//保存q条边，即使保存q+1个点 
	return 0;
}

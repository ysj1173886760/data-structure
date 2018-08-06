#include<iostream>
using namespace std;
const int maxn=1e5+10;
struct line
{
	int to,next;
}edge[maxn*2];
int n,m,tot,clk,ans,dfn[maxn],low[maxn],g[maxn];
bool cutbridge[maxn];
void add1(int a,int b)
{
	edge[++tot].to=b;
	edge[tot].next=g[a];
	g[a]=tot;
}
void dfs(int cur,int fa)
{
	dfn[cur]=low[cur]=++clk;
	bool flag=false;
	for(int i=g[cur];i;i=edge[i].next)
	{
		if(edge[i].to==fa&&!flag)		//Ŀ�����ڷ�ֹ�رߣ���һ�η��ظ��ڵ����������ɵģ�֮����������Է��ظ��ڵ�˵���������رߣ���ô������β������ɸ���low 
		{
			flag=true;
			continue;
		}
		if(!dfn[edge[i].to])
		{
			dfs(edge[i].to,cur);
			low[cur]=min(low[cur],low[edge[i].to]);
			if(low[edge[i].to]>dfn[cur])ans++,cutbridge[i]=true;	
		}
		else low[cur]=min(low[cur],dfn[edge[i].to]);
	}
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
	for(int i=1;i<=tot;i++)if(cutbridge[i])cout<<i<<" ";
	return 0;
}


#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=10005;
struct line
{
	int next,w,to;
}edge[500005];
struct node
{
	int dis,id;
	node& operator=(const node& a)		//÷ÿ‘ÿµƒ‘ÀÀ„∑˚ 
	{
		dis=a.dis;
		id=a.id;
		return *this;
	}
}heap[500010];
int n,m,s,tot,heapsize;
int g[maxn],dis[maxn];
bool judge[maxn];
void pop()
{
	int now=1,next=now*2;
	if(heap[next+1].dis<heap[next].dis&&next+1<=heapsize)next++;
	while(heap[next].dis<heap[heapsize].dis&&next<=heapsize)
	{
		heap[now]=heap[next];
		now=next;
		next*=2;
		if(heap[next+1].dis<heap[next].dis&&next+1<=heapsize)next++;
	}
	heap[now]=heap[heapsize];
	heapsize--;
}
void heapadd(node x)
{
	int now=++heapsize;
	int next=now/2;
	while(next&&heap[next].dis>x.dis)
	{
		heap[now]=heap[next];
		now=next;
		next/=2;
	}
	heap[now]=x;
}
void add1(int a,int b,int c)
{
	tot++;
	edge[tot].to=b;
	edge[tot].w=c;
	edge[tot].next=g[a];
	g[a]=tot;
}
void dijkstra()
{
	for(int i=1;i<=n;i++)dis[i]=2147483647;
	dis[s]=0;
	heap[1].id=s;
	heap[1].dis=0;
	heapsize++;
	while(heapsize)
	{
		int x=heap[1].id;
		pop();
		if(judge[x])continue;
		judge[x]=true;
		int temp=g[x];
		while(temp)
		{
			if(dis[edge[temp].to]>dis[x]+edge[temp].w)
			{
				dis[edge[temp].to]=dis[x]+edge[temp].w;
				node tt;
				tt.dis=dis[edge[temp].to];
				tt.id=edge[temp].to;
				heapadd(tt);
			}
			temp=edge[temp].next;
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=m;i++)
	{
		int x=0,y=0,z=0;
		scanf("%d%d%d",&x,&y,&z);
		add1(x,y,z);
	}
	dijkstra();
	for(int i=1;i<=n;i++)printf("%d ",dis[i]);
	return 0;
}

#include<iostream>
using namespace std;
struct line
{
	int to,w,next;
}edge[100005];
int n,tot,p;
int u[101],c[101],g[101],q[100001],ind[101],outd[101];
void add1(int a,int b,int c)
{
	edge[++tot].to=b;
	edge[tot].w=c;
	edge[tot].next=g[a];
	g[a]=tot;
}
void toposort()
{
	int h=0,t=0;
	for(int i=1;i<=n;i++)
	{
		if(ind[i]==0)
		{
			t++;
			q[t]=i;
		}
	}
	while(h!=t)
	{
		h++;
		int temp=g[q[h]];
		while(temp)
		{
			ind[edge[temp].to]--;
			if(ind[edge[temp].to]==0)
			{
				t++;
				q[t]=edge[temp].to;
			}
			temp=edge[temp].next;
		}
	}
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
		if(c[q[i]]<=0)continue;
		int temp=g[q[i]];
		while(temp)
		{
			c[edge[temp].to]+=c[q[i]]*edge[temp].w;
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

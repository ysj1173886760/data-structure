#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
using namespace std;
int rmq[100005][20],x,y;
inline int max1(int a,int b)
{
	if(a>b)return a;
	return b;
}
int query(int l,int r)
{
	int k=log2(r-l+1);
	return max1(rmq[l][k],rmq[r-(1<<k)+1][k]);
}
int main()
{
	ios::sync_with_stdio(false);
	int n=0,m=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&rmq[i][0]);
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			rmq[i][j]=max1(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",query(x,y));
	}
	return 0;
}

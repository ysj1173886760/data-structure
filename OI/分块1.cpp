#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=5e5+10;
int n,m,blocksz,blocksum;
int a[maxn],block[maxn],start[maxn],end[maxn],sum[maxn],blockid[maxn];
inline int mymin(const int &a,const int &b){return a>b?b:a;}
int main()
{
	scanf("%d%d",&n,&m);
	blocksz=int(sqrt(n));
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i+=blocksz)start[++blocksum]=i,end[blocksum]=mymin(n,i+blocksz-1);
	for(int i=1;i<=blocksum;i++)
		for(int j=start[i];j<=end[i];j++)blockid[j]=i,sum[i]+=a[j];
	for(int i=1;i<=m;i++)
	{
		int op=0,x=0,y=0;
		scanf("%d%d%d",&op,&x,&y);
		if(op==1){sum[blockid[x]]+=y,a[x]+=y;}
		else 
		{
			int ans=0;
			for(int i=blockid[x]+1;i<=blockid[y]-1;i++)ans+=sum[i];
			for(int i=x;i<=end[blockid[x]];i++)ans+=a[i];
			for(int i=start[blockid[y]];i<=y;i++)ans+=a[i];
			printf("%d\n",ans);
		}
	}
	return 0;
}

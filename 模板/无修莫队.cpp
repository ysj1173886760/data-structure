#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=5e4+10;
struct query
{
	int id,l,r;
	long long ans,ans2;
}q[maxn];
int n,m,a[maxn],blocksz,now[maxn];
long long tot;
bool cmp1(const query &a,const query &b)
{
	if(a.l/blocksz==b.l/blocksz)
		return a.r<b.r;
	return a.l/blocksz<b.l/blocksz;
}
bool cmp2(const query &a,const query &b)
{
	return a.id<b.id;
}
inline void add(int x)
{
	tot+=now[x];
	now[x]++;
}
inline void pop(int x)
{
	now[x]--;
	tot-=now[x];
}
long long gcd(const int &a,const int &b)
{
	return b==0?a:gcd(b,a%b);
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	blocksz=sqrt(n);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)
	{
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
		long long temp=q[i].r-q[i].l+1;
		q[i].ans2=(temp-1)*temp/2;
	}
	sort(q+1,q+1+m,cmp1);
	int l=q[1].l,r=q[1].l-1;
	for(int i=1;i<=m;i++)
	{
		while(l<q[i].l)pop(a[l++]);
		while(l>q[i].l)add(a[--l]);
		while(r<q[i].r)add(a[++r]);
		while(r>q[i].r)pop(a[r--]);
		q[i].ans=tot;
	}
	sort(q+1,q+1+m,cmp2);
	for(int i=1;i<=m;i++)
	{
		if(q[i].ans==0)
		{
			cout<<"0/1"<<endl;
			continue;
		}
		long long temp=gcd(q[i].ans,q[i].ans2);
		cout<<q[i].ans/temp<<"/"<<q[i].ans2/temp<<endl;
	}
	return 0;
}

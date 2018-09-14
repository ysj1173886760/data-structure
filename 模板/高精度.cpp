#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxl=1e4+10,base=1e4;
int n,aa,bb;
struct peo
{
	int a,b;
}p[1005];
struct bigint
{
	int a[maxl];
	bigint(){memset(a,0,sizeof(a));}
	bigint(char *s)
	{
		memset(a,0,sizeof(a));
		int len=strlen(s);
		a[0]=(len+3)/4;
		for(int i=0,times=1,now=0;i<len;i++,times*=10)
		{
			if(i%4==0)now++,times=1;
			else a[now]+=times*(s[len-i-1]-'0');
		}
	}
	bigint(int x)
	{
		memset(a,0,sizeof(a));
		int now=1;
		while(x)
		{
			a[now]=x%base;
			x/=base;
			a[0]++;
			now++;
		}
	}
	void print()
	{
		printf("%d",a[a[0]]);
		for(int i=a[0]-1;i>=1;i--)printf("%04d",a[i]);
		printf("\n");
	}
};


bool cmp(const peo &a,const peo &b)
{
	return a.a*a.b<b.a*b.b;
}
bool operator<(const bigint &x,const bigint &y)
{
	if(x.a[0]<y.a[0])return true;
	if(x.a[0]>y.a[0])return false;
	for(int i=x.a[0];i>=1;i--)if(x.a[i]!=y.a[i])return x.a[i]<y.a[i];
	return false;
}
bigint operator+(const bigint &x,const bigint &y)
{
	bigint temp;
	temp.a[0]=max(x.a[0],y.a[0]);
	for(int i=1;i<=temp.a[0];i++)
	{
		temp.a[i]+=x.a[i]+y.a[i];
		temp.a[i+1]+=temp.a[i]/10000;
		temp.a[i]%=10000;
	}
	if(temp.a[temp.a[0]+1])temp.a[0]++;
	return temp;
}
bigint operator-(const bigint &x,const bigint &y)
{
	bigint temp;
	temp=x;
	for(int i=1;i<=x.a[0];i++)
	{
		temp.a[i]-=y.a[i];
		if(temp.a[i]<0)temp.a[i]+=base,temp.a[i+1]--;
	}
	while(!temp.a[temp.a[0]]&&temp.a[0]>1)temp.a[0]--;
	return temp;
}
bigint operator*(const bigint &x,const bigint &y)
{
	bigint temp;
	temp.a[0]=x.a[0]+y.a[0];
	for(int i=1;i<=x.a[0];i++)
		for(int j=1;j<=y.a[0];j++)
		{
			temp.a[i+j-1]+=x.a[i]*y.a[j];
			if(temp.a[i+j-1]>=base)temp.a[i+j]+=temp.a[i+j-1]/base,temp.a[i+j-1]%=base;
		}
	while(!temp.a[temp.a[0]]&&temp.a[0]>1)temp.a[0]--;
	return temp;
}
bigint operator/(const bigint &x,const bigint &y)
{
	bigint times(base),ans,temp;
	for(int i=x.a[0];i>=1;i--)
	{
		temp=temp*times;
		temp.a[1]=x.a[i];
		int lb=0,ub=base;
		while(ub-lb>1)
		{
			int mid=(lb+ub)>>1;
			if(!(temp<mid*y))lb=mid;
			else ub=mid;
		}
		ans.a[i]=lb;
		temp=temp-lb*y;
	}
	ans.a[0]=x.a[0];
	while(ans.a[0]>1&&!ans.a[ans.a[0]])ans.a[0]--;
	return ans;
}

int main()
{
	scanf("%d",&n);
	scanf("%d %d",&aa,&bb);
	for(int i=1;i<=n;i++)scanf("%d %d",&p[i].a,&p[i].b);
	sort(p+1,p+1+n,cmp);
	bigint ans(aa);
	for(int i=1;i<n;i++)
	{
		bigint temp(p[i].a);
		ans=ans*temp;
	}
	bigint temp=p[n].b;
	ans=ans/temp;
	if(ans.a[0]==1&&ans.a[1]==0)cout<<1;
	else ans.print();
	return 0;
}

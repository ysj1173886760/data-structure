#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
struct info
{
	int h1,h2;
}a[10050];
int base=150,mod1=100007,mod2=1000007;
inline int tran(char *a,int mod)
{
	int len=strlen(a);
	long long temp=0;
	for(int i=0;i<len;i++)temp=(temp*base+a[i])%mod;
	return temp;
}
bool cmp(const info &a,const info &b)
{
	if(a.h1==b.h1)return a.h2<b.h2;
	else return a.h1<b.h1;
}
int main()
{
	int n=0,ans=0;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		char s[2000];
		cin>>s;
		a[i].h1=tran(s,mod1);
		a[i].h2=tran(s,mod2);
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
		if(a[i].h1!=a[i-1].h1||a[i].h2!=a[i-1].h2)ans++;
	cout<<ans;
	return 0;
}

#include<iostream>
#include<cstring>
using namespace std;
const int mod=1e9+7;
int n;
long long k;
struct Matrix
{
	int a[110][110];
	Matrix(){memset(a,0,sizeof(a));}
};
Matrix mul(const Matrix &x,const Matrix &y)
{
	Matrix temp;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				temp.a[i][j]=(temp.a[i][j]+(1ll*x.a[i][k]*y.a[k][j])%mod)%mod;
	return temp;
}
Matrix fpow(Matrix x,long long y)
{
	Matrix ans;
	ans=x;
	while(y)
	{
		if(y&1)ans=mul(ans,x);
		x=mul(x,x);
		y>>=1;
	}
	return ans;
}
int main()
{
	cin>>n>>k;
	Matrix temp;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)cin>>temp.a[i][j];
	temp=fpow(temp,k-1);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)cout<<temp.a[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}

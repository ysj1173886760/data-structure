#include<iostream>
#include<cstring>
#include<cstdio>
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
                temp.a[i][k]=(temp.a[i][k]+(1ll*x.a[i][j]*y.a[j][k])%mod)%mod;
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
int read()
{
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
int main()
{
    scanf("%d %lld",&n,&k);
    Matrix temp;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)temp.a[i][j]=read();
    temp=fpow(temp,k-1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)printf("%d ",temp.a[i][j]);
        printf("\n");
    }
    return 0;
}

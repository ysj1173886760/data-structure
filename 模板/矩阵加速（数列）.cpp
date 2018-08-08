#include<iostream>
#include<cstring>
using namespace std;
const int mod=1e9+7;
int n,t;
struct Matrix
{
    int a[4][4];
    Matrix(){memset(a,0,sizeof(a));}
}; 
inline Matrix mul(const Matrix &x,const Matrix &y)
{
    Matrix temp;
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            for(int k=1;k<=3;k++)
                temp.a[i][j]=(temp.a[i][j]+1ll*x.a[i][k]*y.a[k][j])%mod;
    return temp;
}
inline Matrix fpow(Matrix x,int y)
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
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>t;
    while(t--)
    {
        cin>>n;
        if(n<=3){cout<<1<<endl;continue;}
        Matrix temp;
        temp.a[1][1]=1;
        temp.a[3][1]=1;
        temp.a[1][2]=1;
        temp.a[2][3]=1;
        temp=fpow(temp,n-4);
        long long ans=0;
        for(int i=1;i<=3;i++)ans=(ans+temp.a[i][1])%mod;
        cout<<ans<<endl;
    }
    return 0;
}

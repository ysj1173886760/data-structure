
#include<iostream>
#define mid (l+r)/2
using namespace std;
const int maxn=1000000;
long long inc[maxn],mut[maxn],size[maxn],sum[maxn];
int n,m,x,y,z,a[maxn],mod;

void build(int t,int l,int r)
{
    size[t]=r-l+1;
    mut[t]=1;
    if(l==r)
    {
        sum[t]=a[l]%mod;
        return;
    }
    build(t*2,l,mid);
    build(t*2+1,mid+1,r);
    sum[t]=(sum[t*2]+sum[t*2+1])%mod;
}

void pushdown(int t)
{
    sum[t]=(sum[t]*mut[t]+size[t]*inc[t])%mod;
    if(size[t]!=1)
    {
        if(mut[t]==1&&inc[t]==0)return;
        mut[t*2]=mut[t]*mut[t*2]%mod;
        inc[t*2]=(inc[t*2]*mut[t]+inc[t])%mod;
        mut[t*2+1]=mut[t]*mut[t*2+1]%mod;
        inc[t*2+1]=(inc[t*2+1]*mut[t]+inc[t])%mod;
    }
    inc[t]=0;
    mut[t]=1;
}

void pushup(int t)
{
    pushdown(t*2);
    pushdown(t*2+1);
    sum[t]=(sum[t*2]+sum[t*2+1])%mod;
}

void add(int t,int l,int r)
{
    pushdown(t);
    if(x<=l&&r<=y)
    {
        inc[t]=z%mod;
        return;
    }
    long long len=min(r,y)-max(x,l)+1;
    sum[t]+=len*z;
    if(x<=mid)add(t*2,l,mid);
    if(y>mid)add(t*2+1,mid+1,r);
}

void multi(int t,int l,int r)
{
    pushdown(t);
    if(x<=l&&r<=y)
    {
        mut[t]=z%mod;
        return;
    }
    if(x<=mid)multi(t*2,l,mid);
    if(y>mid)multi(t*2+1,mid+1,r);
    pushup(t);
}

long long query(int t,int l,int r)
{
    pushdown(t);
    if(x<=l&&r<=y)
    {
        return sum[t];
    }
    long long temp=0;
    if(x<=mid)temp+=query(t*2,l,mid);
    if(y>mid)temp+=query(t*2+1,mid+1,r);
    return temp%mod;
}


int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);
    cin>>n>>m>>mod;
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int que=0;
        cin>>que;
        if(que==1)
        {
            cin>>x>>y>>z;
            multi(1,1,n);
        }
        else if(que==2)
        {
            cin>>x>>y>>z;
            add(1,1,n);
        }
        else
        {
            cin>>x>>y;
            cout<<query(1,1,n)<<endl;
        }
    }
    return 0;
}

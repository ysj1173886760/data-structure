#include<iostream>
#define mid (l+r)/2
using namespace std;
const int maxn=2000000;
long long sum[maxn],flag[maxn],size[maxn];
int n,m,x,y,z,a[maxn];

void build(int t,int l,int r)
{
    size[t]=r-l+1;
    if(l==r)
    {
        sum[t]=a[l];
        return;
    }
    build(t*2,l,mid);
    build(t*2+1,mid+1,r);
    sum[t]=sum[t*2]+sum[t*2+1];
}

void pushdown(int t)
{
    if(flag[t]==0)return;
    sum[t]+=size[t]*flag[t];
    if(size[t]!=1)
    {
        flag[t*2]+=flag[t];
        flag[t*2+1]+=flag[t];
    }
    flag[t]=0;
}

void add(int t,int l,int r)
{
   // pushdown(t);
    if(x<=l&&r<=y)
    {
        flag[t]+=z;
        return;
    }
    long long len=min(r,y)-max(l,x)+1;
    sum[t]+=len*z;
    if(x<=mid)add(t*2,l,mid);
    if(y>mid)add(t*2+1,mid+1,r);
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
    return temp;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int que=0;
        cin>>que;
        if(que==1)
        {
            cin>>x>>y>>z;
            add(1,1,n);
        }	
        else 
        {
            cin>>x>>y;
            cout<<query(1,1,n);
            cout<<endl;
        }
    }
    return 0;
}

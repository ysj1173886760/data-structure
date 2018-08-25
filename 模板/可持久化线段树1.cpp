#include<iostream>
#include<algorithm>
using namespace std;

const int maxn=2e5+10;
int a[maxn],b[maxn],root[maxn],sum[maxn*30],ls[maxn*30],rs[maxn*30];
int n,m,cnt,tot;

void build(int &t,int l,int r)
{
    t=++tot;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(ls[t],l,mid);
    build(rs[t],mid+1,r);
}
int modify(int t,int l,int r,int p)
{
    int now=++tot;
    ls[now]=ls[t],rs[now]=rs[t],sum[now]=sum[t]+1;
    if(l==r)return now;
    int mid=(l+r)>>1;
    if(p<=mid)ls[now]=modify(ls[t],l,mid,p);
    else rs[now]=modify(rs[t],mid+1,r,p);
    return now;	
}
int query(int lr,int rr,int l,int r,int k)
{
    int mid=(l+r)>>1,x=sum[ls[rr]]-sum[ls[lr]];
    if(l==r)return l;
    if(x>=k)return query(ls[lr],ls[rr],l,mid,k);
    else return query(rs[lr],rs[rr],mid+1,r,k-x);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    sort(a+1,a+1+n);
    cnt=unique(a+1,a+1+n)-a-1;
    build(root[0],1,cnt);
    for(int i=1;i<=n;i++)
    {
        int p=lower_bound(a+1,a+1+cnt,b[i])-a;
        root[i]=modify(root[i-1],1,cnt,p);
    }
    for(int i=1;i<=m;i++)
    {
        int l=0,r=0,k=0;
        cin>>l>>r>>k;
        int ans=query(root[l-1],root[r],1,cnt,k);
        cout<<a[ans]<<endl;
    }
    return 0;
}

#include<iostream>
#include<cstdio>
using namespace std;

const int maxn=5e5+10;

int n,m,q,rt,tot;
int root[maxn],ls[maxn*20],rs[maxn*20],size[maxn*20],cnt[maxn];
long long val[maxn*20];

int get_size(int l,int r)
{
    if(rt==n+1)
    {
        if(r<=n)return r-l+1;
        else if(l<=n)return n-l+1;
        else return 0;
    }
    if(r<m)return r-l+1;
    else if(l<m) return m-l;
    else return 0;
}
long long query(int &t,int l,int r,int x)
{
    if(!t)
    {
        t=++tot;
        size[t]=get_size(l,r);
        if(l==r)
        {
            if(rt<=n)val[t]=1ll*(rt-1)*m+l;
            else val[t]=1ll*m*l;
        }
    }
    size[t]--;
    if(l==r)return val[t];
    int mid=(l+r)>>1;
    if((!ls[t]&&x<=(mid-l+1))||x<=size[ls[t]])return query(ls[t],l,mid,x);
    else 
    {
        if(!ls[t])x-=(mid-l+1);
        else x-=size[ls[t]];
        return query(rs[t],mid+1,r,x);
    }
}
void modify(int &t,int l,int r,int x,long long v)
{
    if(!t)
    {
        t=++tot;
        size[t]=get_size(l,r);
        if(l==r)val[t]=v;
    }
    size[t]++;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(x<=mid)modify(ls[t],l,mid,x,v);
    else modify(rs[t],mid+1,r,x,v);
}

int main()
{
//	freopen("testdata.in","r",stdin);
//	freopen("test.out","w",stdout);
    scanf("%d %d %d",&n,&m,&q);
    int len=max(m,n)+q;
    for(int i=1;i<=q;i++)
    {
        int x=0,y=0;
        long long ans=0;
        scanf("%d %d",&x,&y);
        if(y==m)rt=n+1,ans=query(root[rt],1,len,x);
        else rt=x,ans=query(root[rt],1,len,y);
        rt=n+1,modify(root[rt],1,len,n+(++cnt[rt]),ans);
        if(y!=m)
        {
            long long temp=0;
            rt=n+1,temp=query(root[rt],1,len,x);
            rt=x,modify(root[rt],1,len,m-1+(++cnt[rt]),temp);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

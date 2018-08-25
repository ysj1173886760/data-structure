#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxn=5e5+10;
int n,m,tot;
long long ans;
int a1[maxn],a2[maxn],bit[maxn],sum[maxn*40],ls[maxn*40],rs[maxn*40],ll[maxn],rr[maxn],val[maxn],pos[maxn],root[maxn];

int read()
{
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return f*x;
}
inline int lowbit(const int &x){return x&-x;}
inline int bitsum(int pos)
{
    int sum=0;
    for(int i=pos;i;i-=lowbit(i))sum+=bit[i];
    return sum;
}
inline void bitadd(int pos,int x)
{
    for(int i=pos;i<=n;i+=lowbit(i))bit[i]+=x;
}
void modify(int &x,int l,int r,int pos,int val)
{
    if(!x)x=++tot;
    sum[x]+=val;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(pos<=mid)modify(ls[x],l,mid,pos,val);
    else modify(rs[x],mid+1,r,pos,val);
}
int querynxt(int l,int r,int v)
{
    l--;
    int totl=0,totr=0,temp=0,lb=1,ub=n;
    for(int i=l;i;i-=lowbit(i))ll[++totl]=root[i];
    for(int i=r;i;i-=lowbit(i))rr[++totr]=root[i];
    while(lb<ub)
    {
        int mid=(ub+lb)>>1;
        if(mid<v)
        {
            for(int i=1;i<=totl;i++)ll[i]=rs[ll[i]];
            for(int i=1;i<=totr;i++)rr[i]=rs[rr[i]];
            lb=mid+1;
        }
        else 
        {
            for(int i=1;i<=totl;i++)temp-=sum[rs[ll[i]]];
            for(int i=1;i<=totr;i++)temp+=sum[rs[rr[i]]];
            for(int i=1;i<=totl;i++)ll[i]=ls[ll[i]];
            for(int i=1;i<=totr;i++)rr[i]=ls[rr[i]];
            ub=mid;
        }
    }
    return temp;
}
int querypre(int l,int r,int v)
{
    l--;
    int totl=0,totr=0,temp=0,lb=1,ub=n;
    for(int i=l;i;i-=lowbit(i))ll[++totl]=root[i];
    for(int i=r;i;i-=lowbit(i))rr[++totr]=root[i];
    while(lb!=ub)
    {
        int mid=(lb+ub)>>1;
        if(mid<v)
        {
            for(int i=1;i<=totl;i++)temp-=sum[ls[ll[i]]];
            for(int i=1;i<=totr;i++)temp+=sum[ls[rr[i]]];
            for(int i=1;i<=totl;i++)ll[i]=rs[ll[i]];
            for(int i=1;i<=totr;i++)rr[i]=rs[rr[i]];
            lb=mid+1;
        }
        else 
        {
            for(int i=1;i<=totl;i++)ll[i]=ls[ll[i]];
            for(int i=1;i<=totr;i++)rr[i]=ls[rr[i]];
            ub=mid;
        }
    }
    return temp;
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
    {
        val[i]=read();pos[val[i]]=i;
        a1[i]=bitsum(n)-bitsum(val[i]);
        ans+=a1[i];
        bitadd(val[i],1);
    }
    memset(bit,0,sizeof(bit));
    for(int i=n;i>=1;i--)
    {
        a2[i]=bitsum(val[i]);
        bitadd(val[i],1);
    }
    for(int i=1;i<=m;i++)
    {
        printf("%lld\n",ans);
        int x=read();
        x=pos[x];
        ans-=(a1[x]+a2[x]-querynxt(1,x-1,val[x])-querypre(x+1,n,val[x]));
        for(int j=x;j<=n;j+=lowbit(j))modify(root[j],1,n,val[x],1);
    }
    return 0;
}

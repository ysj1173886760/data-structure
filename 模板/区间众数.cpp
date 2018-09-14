#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxn=2e5+10;
int n,m,blocksz,res;
int a[maxn],b[maxn],ans[maxn],cnt[maxn],sum[maxn];
struct que
{
    int l,r,id;
}q[maxn];

inline int read()
{
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
bool cmp(const que &a,const que &b)
{
    if(a.l/blocksz==b.l/blocksz)return a.r<b.r;
    return a.l<b.l;
}
inline void add1(int x)
{
    if(cnt[x]==res)res++;
    sum[cnt[x]]--;
    cnt[x]++;
    sum[cnt[x]]++;
}
inline void del(int x)
{
    if(res==cnt[x]&&sum[cnt[x]]==1)res--;
    sum[cnt[x]]--;
    cnt[x]--;
    sum[cnt[x]]++;
}

int main()
{
    n=read();m=read();
    blocksz=sqrt(n);
    for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i];
    sort(b+1,b+1+n);
    int tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
    for(int i=1;i<=m;i++)
    {
        q[i].l=read();
        q[i].r=read();
        q[i].id=i;
    }
    sort(q+1,q+1+m,cmp);
    int nl=q[1].l,nr=q[1].l-1;
    for(int i=1;i<=m;i++)
    {
        while(nl>q[i].l)add1(a[--nl]);
        while(nl<q[i].l)del(a[nl++]);
        while(nr<q[i].r)add1(a[++nr]);
        while(nr>q[i].r)del(a[nr--]);
        ans[q[i].id]=-res;
    }
    for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
    return 0;
}

#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn=5e4+10,maxv=1e6+10;
int n,m,blocksz,qtot,ctot,nl,nr,now,res;
int pos[maxn],val[maxn],ans[maxn],a[maxn],time1[maxn],pre[maxn],sum[maxv];
struct que
{
    int l,r,tim,id;
}q[maxn];

int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
bool cmp(const que &a,const que &b)
{
    if(a.l/blocksz!=b.l/blocksz)return a.l<b.l;
    if(a.r/blocksz!=b.r/blocksz)return a.r<b.r;
    return a.tim<b.tim;
}
void change(int x)
{
    if(pos[x]>=nl&&pos[x]<=nr)
    {
        sum[a[pos[x]]]--;
        if(!sum[a[pos[x]]])res--;
    }
    pre[x]=a[pos[x]];
    a[pos[x]]=val[x];
    if(pos[x]>=nl&&pos[x]<=nr)
    {
        if(!sum[a[pos[x]]])res++;
        sum[a[pos[x]]]++;
    }
}
void recall(int x)
{
    if(pos[x]>=nl&&pos[x]<=nr)
    {
        sum[a[pos[x]]]--;
        if(!sum[a[pos[x]]])res--;
    }
    a[pos[x]]=pre[x];
    if(pos[x]>=nl&&pos[x]<=nr)
    {
        if(!sum[a[pos[x]]])res++;
        sum[a[pos[x]]]++;
    }
}
void fixx(int cur)
{
    while(now<ctot&&cur>=time1[now+1])change(++now);
    while(now&&cur<time1[now])recall(now--);
}
void add(int x)
{
    if(!sum[x])res++;
    sum[x]++;
}
void del(int x)
{
    sum[x]--;
    if(!sum[x])res--;
}
int main()
{
    n=read();m=read();
    blocksz=exp((double)0.66666*log(n));
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=m;i++)
    {
        char op[2];
        scanf("%s",op);
        if(op[0]=='Q')
        {
            q[++qtot].l=read();
            q[qtot].r=read();
            q[qtot].id=qtot;
            q[qtot].tim=i;
        }
        else 
        {
            pos[++ctot]=read();
            val[ctot]=read();
            time1[ctot]=i;
        }
    }
    //blocksz=ceil(exp((log(n)+log(ctot))/3));
    //blocksz=exp((double)0.66666*log(n));
    //blocksz=1357;
    sort(q+1,q+1+qtot,cmp);
    nl=q[1].l,nr=q[1].l-1;
    for(int i=1;i<=qtot;i++)
    {
        fixx(q[i].tim);
        while(nr<q[i].r)add(a[++nr]);
        while(nr>q[i].r)del(a[nr--]);
        while(nl<q[i].l)del(a[nl++]);
        while(nl>q[i].l)add(a[--nl]);
        ans[q[i].id]=res;
    }
    for(int i=1;i<=qtot;i++)printf("%d\n",ans[i]);
    return 0;
}

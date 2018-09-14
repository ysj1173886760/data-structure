#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define mid ((l+r)>>1)
using namespace std;

const int maxn=1e3+10;
int n,tot;
double sum1[maxn<<3],sum2[maxn<<3],h[maxn<<1];
int cnt[maxn<<3];
struct seg
{
    double x,y1,y2;
    int dir;
}line[maxn<<3];

bool cmp(const seg &a,const seg &b)
{
    return a.x<b.x;
}
void pushup(int t,int l,int r)
{
    if(cnt[t]>=2)sum2[t]=h[r+1]-h[l];
    else if(cnt[t]==1)
    {
        sum1[t]=h[r+1]-h[l];
        if(l==r)sum2[t]=0;
        else sum2[t]=sum1[t<<1]+sum1[t<<1|1];
    }
    else 
    {
        if(l==r)sum2[t]=sum1[t]=0;
        else 
        {
            sum2[t]=sum2[t<<1]+sum2[t<<1|1];
            sum1[t]=sum1[t<<1]+sum1[t<<1|1];
        }
    }
}
void modify(int t,int l,int r,int x,int y,int z)
{
    if(x<=l&&r<=y)
    {
        cnt[t]+=z;
        pushup(t,l,r);
        return;
    }
    if(x<=mid)modify(t<<1,l,mid,x,y,z);
    if(y>mid)modify(t<<1|1,mid+1,r,x,y,z);
    pushup(t,l,r);
}
int main()
{
    int t=0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(sum1,0,sizeof(sum1));
        memset(sum2,0,sizeof(sum2));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++)
        {
            double x1=0,x2=0,y1=0,y2=0;
            scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);
            h[2*i-1]=y1;
            h[2*i]=y2;
            line[2*i-1].x=x1;
            line[2*i-1].y1=y1;
            line[2*i-1].y2=y2;
            line[2*i-1].dir=1;
            line[2*i].x=x2;
            line[2*i].y1=y1;
            line[2*i].y2=y2;
            line[2*i].dir=-1;
        }
        sort(h+1,h+1+2*n);
        sort(line+1,line+1+2*n,cmp);
        tot=unique(h+1,h+1+2*n)-h-1;
        double ans=0;
        for(int i=1;i<2*n;i++)
        {
            int l=lower_bound(h+1,h+1+tot,line[i].y1)-h;
            int r=lower_bound(h+1,h+1+tot,line[i].y2)-h;
            modify(1,1,tot-1,l,r-1,line[i].dir);
            ans+=(line[i+1].x-line[i].x)*sum2[1];
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define mid ((l+r)>>1)
using namespace std;

const int maxn=1e5+10;;
int n,tot;
struct seg
{
    int y1,y2,x;
    int dir;
}line[maxn<<1];
int cnt[maxn<<3],sum[maxn<<3],sumline[maxn<<3],h[maxn<<1];
bool lb[maxn<<3],ub[maxn<<3];

bool cmp(const seg &a,const seg &b)
{
    if(a.x==b.x)return a.dir>b.dir;
    return a.x<b.x;
}
void pushup(int t,int l,int r)
{
    if(cnt[t])
    {
        sum[t]=h[r+1]-h[l];
        lb[t]=ub[t]=true;
        sumline[t]=2;
    }
    else if(l==r)sum[t]=lb[t]=ub[t]=sumline[t]=0;
    else 
    {
        sum[t]=sum[t<<1]+sum[t<<1|1];
        lb[t]=lb[t<<1];
        ub[t]=ub[t<<1|1];
        sumline[t]=sumline[t<<1]+sumline[t<<1|1];
        if(ub[t<<1]&&lb[t<<1|1])sumline[t]-=2;
    }
}
void modify(int t,int l,int r,int x,int y,int z)
{
    if(x<=l&&r<=y)
    {
        cnt[t]+=z;
        pushup(t,l,r);
        return;
    }
    if(x<=mid)modify(t<<1,l,mid,x,y,z);
    if(y>mid)modify(t<<1|1,mid+1,r,x,y,z);
    pushup(t,l,r);
}

int main()
{
    while(scanf("%d",&n)==1)
    {
        tot=0;
        for(int i=1;i<=n;i++)
        {
            int x1=0,x2=0,y1=0,y2=0;
            scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
            line[i].x=x1;
            line[i].y1=y1;
            line[i].y2=y2;
            line[i].dir=1;
            line[i+n].x=x2;
            line[i+n].y1=y1;
            line[i+n].y2=y2;
            line[i+n].dir=-1;
            h[i]=y1;
            h[i+n]=y2;
        }
        sort(line+1,line+1+2*n,cmp);
        sort(h+1,h+1+2*n);
        tot=unique(h+1,h+1+2*n)-h-1;
        int ans=0,last=0;
        for(int i=1;i<=2*n;i++)
        {
            int l=lower_bound(h+1,h+1+tot,line[i].y1)-h;
            int r=lower_bound(h+1,h+1+tot,line[i].y2)-h;
            modify(1,1,tot-1,l,r-1,line[i].dir);
            ans+=sumline[1]*(line[i+1].x-line[i].x);
            ans+=abs(sum[1]-last);
            last=sum[1];
        }
        printf("%d\n",ans);
    }
    return 0;
}
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define mid ((l+r)>>1)
using namespace std;

const int maxn=110;
double h[maxn<<1],sum[maxn<<3];
int cnt[maxn<<3];
int n,tot;
struct seg
{
    double x,y1,y2;
    int dir;
}line[maxn<<1];

bool cmp(const seg &a,const seg &b)
{
    return a.x<b.x;
}
void pushup(int t,int l,int r)
{
    if(cnt[t]>0)sum[t]=h[r+1]-h[l];
    else if(l==r)sum[t]=0;
    else sum[t]=sum[t<<1]+sum[t<<1|1];
}
void modify(int t,int l,int r,int x,int y,int z)
{
    if(x<=l&&r<=y)
    {
        cnt[t]+=z;
        pushup(t,l,r);
        return;
    }
    if(x<=mid)modify(t<<1,l,mid,x,y,z);
    if(y>mid)modify(t<<1|1,mid+1,r,x,y,z);
    pushup(t,l,r);
}

int main()
{
    int t=0;
    while(1)
    {
        t++;
        scanf("%d",&n);
        if(n==0)return 0;
        memset(sum,0,sizeof(sum));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++)
        {
            double x1=0,x2=0,y1=0,y2=0;
            scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);
            line[2*i-1].x=x1;
            line[2*i-1].y1=y1;
            line[2*i-1].y2=y2;
            line[2*i-1].dir=1;
            line[2*i].x=x2;
            line[2*i].y1=y1;
            line[2*i].y2=y2;
            line[2*i].dir=-1;
            h[2*i-1]=y1;
            h[2*i]=y2;
        }
        sort(h+1,h+1+2*n);
        sort(line+1,line+1+2*n,cmp);
        tot=unique(h+1,h+1+2*n)-h-1;
        double ans=0;
        for(int i=1;i<2*n;i++)
        {
            int l=lower_bound(h+1,h+1+tot,line[i].y1)-h;
            int r=lower_bound(h+1,h+1+tot,line[i].y2)-h;
            modify(1,1,tot-1,l,r-1,line[i].dir);
            ans+=(line[i+1].x-line[i].x)*sum[1];
        }
        printf("Test case #%d\n",t);
        printf("Total explored area: %.2lf\n\n",ans);
    }
    return 0;
}

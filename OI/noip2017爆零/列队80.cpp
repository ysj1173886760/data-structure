#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=1e5+10;
const int maxn2=1e6+10;

int n,m,q,tot;

// 50pts
int hei[maxn];
long long map1[510][maxn],last[maxn];
struct thing1
{
    int x,y;
}que[maxn];

//80pts
int maxx;
int bit[maxn2];
long long pos[maxn2];

void work50()
{
    for(int i=1;i<=q;i++)
    {
        scanf("%d %d",&que[i].x,&que[i].y);
        hei[i]=que[i].x;
    }
    sort(hei+1,hei+1+q);
    tot=unique(hei+1,hei+1+q)-hei-1;
    for(int i=1;i<=tot;i++)
    {
        long long now=1ll*(hei[i]-1)*m;
        for(int j=1;j<=m;j++)map1[i][j]=++now;
    }
    for(int i=1;i<=n;i++)last[i]=last[i-1]+m;
    for(int t=1;t<=q;t++)
    {
        int nx=0,ny=que[t].y;
        for(int i=1;i<=tot;i++)
            if(que[t].x==hei[i])
            {
                nx=i;
                break;
            }
        long long ans=0;
        if(ny!=m)ans=map1[nx][ny];
        else ans=last[hei[nx]];
        //Ïò×ó
        if(ny!=m)
        {
            while(ny<m-1)map1[nx][ny]=map1[nx][ny+1],ny++;
            map1[nx][ny]=last[hei[nx]];
        }
        //ÏòÓÒ 
        for(int i=hei[nx];i<n;i++)last[i]=last[i+1];
        last[n]=ans;
        printf("%lld\n",ans);
    }
}
int lowbit(int x)
{
    return x&-x;
}
int find_kth(int k)
{
    int now=0,ans=0;
    for(int i=20;i>=0;i--)
    {
        ans+=(1<<i);
        if(ans>maxx||now+bit[ans]>=k)ans-=(1<<i);
        else now+=bit[ans];
    }
    return ans+1;
}
void add(int pos,int x)
{
    for(int i=pos;i<=maxx;i+=lowbit(i))bit[i]+=x;
}
void work80()
{
    maxx=n+m+q-1;
    int cnt=n+m-1;
    for(int i=1;i<=m;i++)pos[i]=i;
    for(int i=m+1;i<=n+m-1;i++)pos[i]=pos[i-1]+m;
    for(int i=1;i<=n+m-1;i++)add(i,1);
    for(int i=1;i<=q;i++)
    {
        int x=0,y=0;
        scanf("%d %d",&x,&y);
        int now=find_kth(y);
//		cout<<now<<endl;
        long long temp=pos[now];
        pos[now]=0;
        add(now,-1);
        pos[++cnt]=temp;
        add(cnt,1);
        printf("%lld\n",temp);
    }
}

int main()
{
//	freopen("testdata.in","r",stdin);
//	freopen("test.out","w",stdout);
    scanf("%d %d %d",&n,&m,&q);
    if(q<=500)work50();
    else work80();
//	work80();
    return 0;
}

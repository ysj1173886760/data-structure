#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=5e4+10;
const int inf=0x3f3f3f3f;

int n,m,tot,maxx,id;
int g[maxn],dis[maxn],w[maxn];
bool flag[maxn];
struct line
{
    int to,next,w;
}edge[maxn*2];

void add1(int a,int b,int c)
{
    edge[++tot].to=b;
    edge[tot].w=c;
    edge[tot].next=g[a];
    g[a]=tot;
}
void dfs(int cur,int fa)
{
    if(dis[cur]>maxx)maxx=dis[cur],id=cur;
    for(int i=g[cur];i;i=edge[i].next)
    {
        if(edge[i].to==fa)continue;
        dis[edge[i].to]=dis[cur]+edge[i].w;
        dfs(edge[i].to,cur);
    }
}
void work20()
{
    dfs(1,1);
    memset(dis,0,sizeof(dis));
    dfs(id,id);
    printf("%d",maxx);
}
void workpianfen()
{
    sort(w+1,w+n);
    printf("%d",w[1]);
}
bool check(int x)
{
    int cnt=0,now=0;
    for(int i=2;i<=n;i++)
    {
        now+=w[i];
        if(now>=x)now=0,cnt++;
    }
    return cnt>=m;
}
void worklian()
{
    int lb=1,ub=5e8+1;
    while(ub-lb>1)
    {
        int mid=(lb+ub)>>1;
        if(check(mid))lb=mid;
        else ub=mid;
    }
    printf("%d",lb);
}
void workdoushi1()
{
    int minn=0x3f3f3f3f;
    sort(w+2,w+n+1);
  //  for(int i=1;i<n;i++)cout<<w[i]<<" ";
    for(int i=1;i<=m;i++)minn=min(minn,w[n-2*m+i]+w[n-i+1]);
    printf("%d",minn);
}
int main()
{
    bool quandoushi1=true;
    bool shiyitiaolian=true;
    scanf("%d %d",&n,&m);
    for(int i=1;i<n;i++)
    {
        int x=0,y=0,z=0;
        scanf("%d %d %d",&x,&y,&z);
        add1(x,y,z);
        add1(y,x,z);
        w[y]=z;
        if(x!=1)quandoushi1=false;
        if(y!=x+1)shiyitiaolian=false;
    }
    if(m==1)work20();
    else if(m==n-1)workpianfen();
    else if(shiyitiaolian)worklian();
    else if(quandoushi1)workdoushi1();  
    else printf("RP++");
    return 0;
}

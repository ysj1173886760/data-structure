#include<iostream>
#include<cstdio>
using namespace std;

const int maxn=1e3+10;
int n,b,tot,blocknum,top;
int stack1[maxn],bel[maxn],head1[maxn],g[maxn];
struct line
{
    int to,next;
}edge[2*maxn];

inline void add1(int a,int b)
{
    edge[++tot].to=b;
    edge[tot].next=g[a];
    g[a]=tot;
}
void dfs(int cur,int fa)
{
    int now=top;
    for(int i=g[cur];i;i=edge[i].next)
    {
        if(edge[i].to==fa)continue;
        dfs(edge[i].to,cur);
        if(top-now>=b)
        {
            head1[++blocknum]=cur;
            while(top>now)bel[stack1[top--]]=blocknum;
        }
    }
    stack1[++top]=cur;
}


int main()
{
    scanf("%d %d",&n,&b);
    for(int i=1;i<n;i++)
    {
        int x=0,y=0;
        scanf("%d %d",&x,&y);
        add1(x,y);
        add1(y,x);
    }
    dfs(1,0);
    if(top)while(top)bel[stack1[top--]]=blocknum;
    printf("%d\n",blocknum);
    for(int i=1;i<=n;i++)printf("%d ",bel[i]);
    printf("\n");
    for(int i=1;i<=blocknum;i++)printf("%d ",head1[i]);
    return 0;
}

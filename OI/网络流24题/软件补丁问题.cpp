#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;

const int maxn=2e6+10;
int n,m,tot,mod;
int dis[maxn],q[maxn];
bool vis[maxn];
struct line
{
    int to,next,w;
    int need,no_need,bring,fix;
}edge[110];

void spfa()
{
    memset(dis,0x3f,sizeof(dis));
    int h=0,t=1;
    q[t]=(1<<n)-1;
    vis[q[t]]=true;
    dis[q[t]]=0;
    while(h!=t)
    {
        h=h%mod+1;
        int x=q[h];
        for(int i=1;i<=m;i++)
            if((x&edge[i].need)==edge[i].need&&(x&edge[i].no_need)==0)
            {
                int temp=edge[i].fix&x;
                int now=x^temp;
                now|=edge[i].bring;
                if(dis[now]>dis[x]+edge[i].w)
                {
                    dis[now]=dis[x]+edge[i].w;
                    if(!vis[now])
                    {
                        t=t%mod+1;
                        q[t]=now;
                        vis[q[t]]=true;
                    }
                }
            }
        vis[x]=false;
    }
}
void print(int x)
{
    if(!x)return;
    print(x>>1);
    cerr<<(x&1);
}
int main()
{
    scanf("%d %d",&n,&m);
    mod=(1<<n)-1;
    for(int i=1;i<=m;i++)
    {
        int x=0;
        char temp[30];
        scanf("%d",&x);
        edge[i].w=x;
        scanf("%s",temp+1);
        for(int j=1;j<=n;j++)
        {
            if(temp[j]=='+')edge[i].need|=1<<(j-1);
            if(temp[j]=='-')edge[i].no_need|=1<<(j-1);
        }
        scanf("%s",temp+1);
        for(int j=1;j<=n;j++)
        {
            if(temp[j]=='+')edge[i].bring|=1<<(j-1);
            if(temp[j]=='-')edge[i].fix|=1<<(j-1);
        }
    }
    spfa();
    if(dis[0]==0x3f3f3f3f)printf("0");
    else printf("%d",dis[0]);
    return 0;
}

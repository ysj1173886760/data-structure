#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=2e2+10;
int n,m,ans;
int match[maxn];
bool vis[maxn],map1[maxn][maxn];

bool dfs(int cur)
{
    for(int i=1;i<=n;i++)
        if(map1[cur][i]&&!vis[i])
        {
            vis[i]=true;
            if(!match[i]||dfs(match[i]))
            {
                match[i]=cur;
                return true;
            }
        }
    return false;
}
void maxmatch()
{
    for(int i=1;i<=m;i++)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i))ans++;
    }
}
int main()
{
    scanf("%d %d",&m,&n);
    while(1)
    {
        int x=0,y=0;
        scanf("%d %d",&x,&y);
        if(x==-1&y==-1)break;
        map1[x][y]=true;
    }
    maxmatch();
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        if(match[i])printf("%d %d\n",match[i],i);
    return 0;
}

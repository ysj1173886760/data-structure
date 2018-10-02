#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn=1e3+10;
int n,m,e,ans;
int match[maxn];
bool vis[maxn],map1[maxn][maxn];

bool dfs(int cur)
{
    for(int i=1;i<=m;i++)
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
    for(int i=1;i<=n;i++)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i))ans++;
    }
}
int main()
{
    scanf("%d %d %d",&n,&m,&e);
    for(int i=1;i<=e;i++)
    {
         int x=0,y=0;
         scanf("%d %d",&x,&y);
         if(x<=n&&y<=m)map1[x][y]=true;
    }
    maxmatch();
    printf("%d",ans);
    return 0;
}


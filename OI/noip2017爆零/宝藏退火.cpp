#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=13,inf=0x3f3f3f3f;
int map1[maxn][maxn],n,m,ans=0x3f3f3f3f;
bool vis[maxn];
struct node
{
    int dep,w,id;
    node(int x=0,int y=0,int z=0){dep=x,w=y,id=z;}
};

bool operator<(const node &a,const node &b)
{
    return a.w>b.w;
}
void init()
{
    ans=inf;
    cin>>n>>m;
    memset(map1,0x3f,sizeof(map1));
    for(int i=1;i<=m;i++)
    {
        int x=0,y=0,z=0;
        cin>>x>>y>>z;
        map1[x][y]=min(map1[x][y],z);
        map1[y][x]=min(map1[y][x],z);
    }
}
void SA_prim()
{
    for(int source=1;source<=n;source++)
    {
        node stack[10000];
        int cost=0,top=0;
        memset(vis,0,sizeof(vis));
        vis[source]=true;
        priority_queue<node>pq;
        for(int i=1;i<=n;i++)
            if(!vis[i]&&map1[source][i]!=inf)pq.push(node(2,map1[source][i],i));
        for(int i=1;i<n;i++)
        {
            node temp=pq.top();
            pq.pop();
            while(!pq.empty()&&(vis[temp.id]||rand()%n==0))
            {
                if(!vis[temp.id])stack[++top]=temp;
                temp=pq.top();
                pq.pop();
            }
            while(top)pq.push(stack[top--]);
            vis[temp.id]=true;
            cost+=temp.w;
            for(int j=1;j<=n;j++)
                if(!vis[j]&&map1[temp.id][j]!=inf)pq.push(node(temp.dep+1,temp.dep*map1[temp.id][j],j));
        }
        ans=min(ans,cost);
    }
}
int main()
{
    srand(time(NULL));
    init();
    for(int i=1;i<=500;i++)SA_prim();
    cout<<ans;
    return 0;
}

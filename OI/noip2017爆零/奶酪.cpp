#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;
struct dong
{
    long long x,y,z;
}ho[1005];
bool map[1005][1005];
bool vis[1005];
long long dis(dong a,dong b)
{
    return abs(a.x-b.x)*abs(a.x-b.x)+abs(a.y-b.y)*abs(a.y-b.y)+abs(a.z-b.z)*abs(a.z-b.z);
}
bool ok;
bool shang[1005];
bool xia[1005];
long long n,h,r;
void dfs(int x)
{
    vis[x]=true;
    if(shang[x]==true)
    {
        ok=true;
        return;
    }
    else 
    {
        for(int j=1;j<=n;j++)
        {
            if(map[x][j]==true&&vis[j]==false)
            {
                dfs(j);
            }
        }
    }
}
int main()
{
    std::ios::sync_with_stdio(false);
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        ok=false;
        memset(map,0,sizeof(map));
        memset(vis,0,sizeof(vis));
        cin>>n>>h>>r;
        for(int j=1;j<=n;j++)
            cin>>ho[j].x>>ho[j].y>>ho[j].z;
        for(int j=1;j<=n;j++)
        {
            shang[j]=false;
            xia[j]=false;
            if(ho[j].z<=r)xia[j]=true;
            if(abs(ho[j].z-h)<=r)shang[j]=true;
        }
        for(int j=1;j<=n;j++)
            for(int k=j+1;k<=n;k++)
            {
                if(dis(ho[j],ho[k])<=4*r*r)
                {
                    map[j][k]=true;
                    map[k][j]=true;
                }
            }
        for(int j=1;j<=n;j++)
        {
            if(xia[j]==true)
            {
                dfs(j);
            }
            if(ok)break;
        }
        if(ok)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}

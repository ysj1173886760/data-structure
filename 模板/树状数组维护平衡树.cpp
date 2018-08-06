#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxw=1e7+100,maxn=1e5+10;
int bit[2*maxw],maxx,n;
inline int lowbit(int x){return x&(-x);}
void add(int pos,int x)
{
    for(int i=pos;i<=2*maxw;i+=lowbit(i))bit[i]+=x;
}
inline int find_rank(int x)
{
    int ans=1;
    x--;
    for(int i=x;i;i-=lowbit(i))ans+=bit[i];
    return ans;
}
inline int find_val(int x)
{
    int now=0,ans=0;
    for(int i=maxx;i>=0;i--)
    {
        ans+=(1<<i);
        if(ans>2*maxw||now+bit[ans]>=x)ans-=(1<<i);
        else now+=bit[ans];
    }
    return ans+1;
}
inline int find_pre(int x)
{
    return find_val(find_rank(x)-1);
}
inline int find_next(int x)
{
    return find_val(find_rank(x+1));
}
int main()
{
    scanf("%d",&n);
    maxx=log2(maxw)+1;
    for(int i=1;i<=n;i++)
    {
        int opt=0,x=0;
        scanf("%d%d",&opt,&x);
        if(opt==1)add(x+maxw,1);
        else if(opt==2)add(x+maxw,-1);
        else if(opt==3)printf("%d\n",find_rank(x+maxw));
        else if(opt==4)printf("%d\n",find_val(x)-maxw);
        else if(opt==5)printf("%d\n",find_pre(x+maxw)-maxw);
        else printf("%d\n",find_next(x+maxw)-maxw);
    }
    return 0;
}

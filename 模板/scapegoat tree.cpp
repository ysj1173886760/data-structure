#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

const int maxn=1e5+10;
const double alpha=0.7;
int root,n,tot,top,pointer,badnode,fa;
int stack[maxn],temp[maxn];
struct node
{
    int size,sum,val;		//size°üº¬È«²¿ 
    bool flag;
    int son[2];
}t[maxn];

int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
bool isbad(int x)
{
    return (double)t[t[x].son[0]].size>(double)t[x].size*alpha||(double)t[t[x].son[1]].size>(double)t[x].size*alpha;
}
void update(int x)
{
    t[x].size=t[t[x].son[0]].size+t[t[x].son[1]].size+1;
    t[x].sum=t[t[x].son[0]].sum+t[t[x].son[1]].sum+!t[x].flag;
}
void dfs(int now)
{
    if(!now)return;
    dfs(t[now].son[0]);
    if(!t[now].flag)temp[++pointer]=now;
    else stack[++top]=now;
    dfs(t[now].son[1]);
}
int build(int l,int r)
{
    if(l>r)return 0;
    int mid=(l+r)>>1;
    int now=temp[mid];
    t[now].son[0]=build(l,mid-1);
    t[now].son[1]=build(mid+1,r);
    update(now);
    return now;
}
void rebuild(int &now)
{
    pointer=0;
    dfs(now);
    now=build(1,pointer);
}
void insert(int &now,int val,int f)
{
    if(!now)
    {
        if(top)now=stack[top--];
        else now=++tot;
        t[now].val=val;
        t[now].size=t[now].sum=1;
        t[now].flag=false;
        t[now].son[1]=t[now].son[0]=0;
        return;
    }
    else 
    {
        t[now].size++;
        t[now].sum++;
        if(val>t[now].val)insert(t[now].son[1],val,now);
        else insert(t[now].son[0],val,now);
    }
    if(isbad(now))fa=f,badnode=now;
}
void insert(int val)
{
    badnode=fa=0;
    insert(root,val,0);
    if(!badnode)return;
    if(badnode==root)rebuild(root);
    else 
    {
    //	int k=t[fa].son[1]==badnode;
        rebuild(t[fa].son[t[fa].son[1]==badnode]);
    }
}
int find_rank(int val)
{
    int now=root,sum=1;
    while(now)
    {
        if(t[now].val>=val)now=t[now].son[0];
        else sum+=!t[now].flag+t[t[now].son[0]].sum,now=t[now].son[1];
    }
    return sum;
}
void del(int now,int k)
{
    t[now].sum--;
    if(!t[now].flag&&t[t[now].son[0]].sum+1==k){t[now].flag=true;return;}
    if(t[t[now].son[0]].sum>=k)del(t[now].son[0],k);
    else del(t[now].son[1],k-t[t[now].son[0]].sum-!t[now].flag);
}
int find_kth(int x)
{
    int now=root;
    while(true)
    {
        if(!t[now].flag&&t[t[now].son[0]].sum+1==x)return t[now].val;
        else if(t[t[now].son[0]].sum>=x)now=t[now].son[0];
        else x-=t[t[now].son[0]].sum+!t[now].flag,now=t[now].son[1];
    }
}
void print(int now)
{
    if(t[now].son[0])print(t[now].son[0]);
    if(!t[now].flag)cerr<<t[now].val<<" ";
    if(t[now].son[1])print(t[now].son[1]);
}

int main()
{
    n=read();
    while(n--)
    {
        int op=0,x=0;
        op=read();x=read();
        if(op==1)insert(x);
        else if(op==2)del(root,find_rank(x));
        else if(op==3)printf("%d\n",find_rank(x));
        else if(op==4)printf("%d\n",find_kth(x));
        else if(op==5)printf("%d\n",find_kth(find_rank(x)-1));
        else printf("%d\n",find_kth(find_rank(x+1)));
    }
    return 0;
}

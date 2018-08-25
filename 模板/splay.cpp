#include<iostream>
#include<cstdio>
using namespace std;

const int maxn=1e5+10;
int n,tot,root;
struct node
{
    int val,fa,size,cnt;
    int son[2];
}t[maxn];

int read()
{
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return f*x;
}
void update(int x)
{
    t[x].size=t[t[x].son[0]].size+t[t[x].son[1]].size+t[x].cnt;
}
void rotate(int x)
{
    int y=t[x].fa;
    int z=t[y].fa;
    int k=t[y].son[1]==x;
    t[z].son[t[z].son[1]==y]=x,t[x].fa=z;
    t[t[x].son[k^1]].fa=y,t[y].son[k]=t[x].son[k^1];
    t[x].son[k^1]=y,t[y].fa=x;
    update(y),update(x);
}
void splay(int x,int to)
{
    while(t[x].fa!=to)
    {
        int y=t[x].fa;
        int z=t[y].fa;
        if(z!=to)
            (t[z].son[1]==y)^(t[y].son[1]==x)?rotate(x):rotate(y);
        rotate(x);
    }
    if(to==0)root=x;
}
void insert(int x)
{
    int now=root,fa=0;
    while(now&&t[now].val!=x)
    {
        fa=now;
        now=t[now].son[x>t[now].val];
    }
    if(now)t[now].cnt++;
    else 
    {
        now=++tot;
        if(fa)t[fa].son[x>t[fa].val]=tot;
        t[tot].fa=fa;
        t[tot].size=t[tot].cnt=1;
        t[tot].val=x;
    }
    splay(now,0);
}
void find(int x)
{
    int now=root;
    if(!root)return;
    while(t[now].son[x>t[now].val]&&t[now].val!=x)now=t[now].son[x>t[now].val];
    splay(now,0);
}
void destory(int x)
{
    find(x);
    if(t[root].val!=x)return;
    if(t[root].cnt>1)t[root].cnt--;
    else 
    {
        int now=t[root].son[0];
        while(t[now].son[1])now=t[now].son[1];
        splay(now,root);
        t[now].son[1]=t[root].son[1];
        t[t[root].son[1]].fa=now;
        t[now].fa=0;
        root=now;
    }
    update(root);
}
int find_pre(int x)
{
    find(x);
    if(t[root].val<x)return t[root].val;
    int now=t[root].son[0];
    while(t[now].son[1])now=t[now].son[1];
    return t[now].val;
}
int find_next(int x)
{
    find(x);
    if(t[root].val>x)return t[root].val;
    int now=t[root].son[1];
    while(t[now].son[0])now=t[now].son[0];
    return t[now].val;
}
int find_kth(int x)
{
    int now=root;
    if(t[now].size<x)return 0;
    while(1)
    {
        int y=t[now].son[0];
        if(x>t[y].size+t[now].cnt)
        {
            x-=t[y].size+t[now].cnt;
            now=t[now].son[1];
        }
        else if(t[y].size>=x)now=y;
        else return t[now].val;
    }
}
int find_rank(int x)
{
    find(x);
    return t[t[root].son[0]].size;
}

int main()
{
    n=read();
    insert(-2147483647);
    for(int i=1;i<=n;i++)
    {
        int op=0,x=0;
        op=read();x=read();
        if(op==1)insert(x);
        else if(op==2)destory(x);
        else if(op==3)printf("%d\n",find_rank(x));
        else if(op==4)printf("%d\n",find_kth(x+1));
        else if(op==5)printf("%d\n",find_pre(x));
        else printf("%d\n",find_next(x));
    }
}

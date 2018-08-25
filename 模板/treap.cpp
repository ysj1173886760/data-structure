#include<iostream>
#include<cstdio>
#define ls t[x].son[0]
#define rs t[x].son[1]
using namespace std;

const int maxn=1e5+10;
int root,tot,n,seed=552;
struct node
{
    int val,key,cnt,size;
    int son[2];
}t[maxn];

int myrand()
{
    return seed=int(seed*55266ll%2147483647);
}
int newnode(int v)
{
    int now=++tot;
    t[now].size=t[now].cnt=1;
    t[now].key=myrand();
    t[now].val=v;
    return now;
}
void update(int x)
{
    t[x].size=t[ls].size+t[rs].size+t[x].cnt;
}
void rotate(int &x,int k)
{
    int temp=t[x].son[k];
    t[x].son[k]=t[temp].son[k^1];
    t[temp].son[k^1]=x;
    x=temp;
    update(t[x].son[k^1]),update(x);
}
void insert(int &x,int v)
{
    if(!x){x=newnode(v);return;}
    if(t[x].val==v)t[x].cnt++;
    else 
    {
        int k=v>t[x].val;
        insert(t[x].son[k],v);
        if(t[t[x].son[k]].key>t[x].key)rotate(x,k);
    }
    update(x);
}
void del(int &x,int v)
{
    if(t[x].val==v)
    {
        if(t[x].cnt>1)t[x].cnt--;
        else if(ls+rs==0)x=0;
        else if(t[ls].key>t[rs].key)rotate(x,0),del(rs,v);
        else rotate(x,1),del(ls,v);
    }
    else del(t[x].son[v>t[x].val],v);
    update(x);
}
int find_kth(int x)
{
    int now=root;
    while(true)
    {
        int y=t[now].son[0];
        if(x>t[y].size+t[now].cnt)
        {
            x-=t[now].cnt+t[y].size;
            now=t[now].son[1];
        }
        else if(t[y].size>=x)now=y;
        else return t[now].val;
    }
}
int find_rank(int x)
{
    int now=root,sum=0;
    while(now)
    {
        if(x>t[now].val)sum+=t[now].cnt+t[t[now].son[0]].size,now=t[now].son[1];
        else now=t[now].son[0];
    }
    return sum;
}
int find_pre(int x)
{
    int now=root,pre=0;
    while(now)
    {
        if(t[now].val<x)pre=t[now].val,now=t[now].son[1];
        else now=t[now].son[0];
    }
    return pre;
}
int find_next(int x)
{
    int now=root,nxt=0;
    while(now)
    {
        if(t[now].val>x)nxt=t[now].val,now=t[now].son[0];
        else now=t[now].son[1];
    }
    return nxt;
}
int read()
{
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}

int main()
{
    n=read();
    insert(root,-0x3f3f3f3f);
    while(n--)
    {
        int x=0,op=0;
        op=read();x=read();
        if(op==1)insert(root,x);
        else if(op==2)del(root,x);
        else if(op==3)printf("%d\n",find_rank(x));
        else if(op==4)printf("%d\n",find_kth(x+1));
        else if(op==5)printf("%d\n",find_pre(x));
        else printf("%d\n",find_next(x));
    }
    return 0;
}

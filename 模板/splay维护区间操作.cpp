#include<iostream>
#include<cstdlib>
#include<cstdio>
#define lson t[x].son[0]
#define rson t[x].son[1]
#define test print(root),cout<<endl;
using namespace std;

const int maxn=1e7+10,inf=0x3f3f3f3f;
int n,m,root,tot,top;
int a[maxn],stack[maxn],id[maxn];
struct node
{
    int val,fa,size,sum,lm,rm,mm;
    int son[2];
    bool tag,rev;
}t[maxn];

inline void myswap(int &a,int &b){a^=b^=a^=b;}
inline void update(int x)
{
    
    t[x].size=t[lson].size+t[rson].size+1;
    t[x].sum=t[lson].sum+t[rson].sum+t[x].val;
    t[x].mm=max(t[lson].mm,max(t[rson].mm,t[rson].lm+t[lson].rm+t[x].val));
    t[x].lm=max(t[lson].lm,t[lson].sum+t[x].val+t[rson].lm);
    t[x].rm=max(t[rson].rm,t[rson].sum+t[x].val+t[lson].rm);
}
inline void pushdown(int x)
{
    if(t[x].tag)
    {
        t[x].rev=t[x].tag=0;
        if(lson)t[lson].tag=true,t[lson].val=t[x].val,t[lson].sum=t[lson].val*t[lson].size;
        if(rson)t[rson].tag=true,t[rson].val=t[x].val,t[rson].sum=t[rson].val*t[rson].size;
        if(t[x].val>=0)
        {
            if(lson)t[lson].lm=t[lson].mm=t[lson].rm=t[lson].sum;
            if(rson)t[rson].lm=t[rson].mm=t[rson].rm=t[rson].sum;
        }
        else 
        {
            if(lson)t[lson].lm=t[lson].rm=0,t[lson].mm=t[x].val;
            if(rson)t[rson].lm=t[rson].rm=0,t[rson].mm=t[x].val;
        }
    }
    if(t[x].rev)
    {
        t[x].rev=0;
        t[lson].rev^=1,t[rson].rev^=1;
        myswap(t[lson].lm,t[lson].rm),myswap(t[rson].lm,t[rson].rm);
        myswap(t[lson].son[0],t[lson].son[1]),myswap(t[rson].son[0],t[rson].son[1]);
    }
}
inline void rotate(int x)
{
    int y=t[x].fa;
    int z=t[y].fa;
    int k=t[y].son[1]==x;
    t[z].son[t[z].son[1]==y]=x,t[x].fa=z;
    t[t[x].son[k^1]].fa=y,t[y].son[k]=t[x].son[k^1];
    t[x].son[k^1]=y,t[y].fa=x;
    update(y),update(x);
}
inline void splay(int x,int to)
{
    while(t[x].fa!=to)
    {
        int y=t[x].fa;
        int z=t[y].fa;
        if(z!=to)(t[z].son[1]==y)^(t[y].son[1]==x)?rotate(x):rotate(y);
        rotate(x);
    }
    if(to==0)root=x;
}
inline int find_kth(int x)
{
    int now=root;
    while(true)
    {
        pushdown(now);
        int y=t[now].son[0];
        if(x>t[y].size+1)
        {
            x-=t[y].size+1;
            now=t[now].son[1];
        }
        else if(t[y].size>=x)now=y;
        else return now;
    }
}
inline void recycle(int x)
{
    if(lson)recycle(lson);
    if(rson)recycle(rson);
    stack[++top]=x;
    t[x].size=t[x].val=t[x].fa=lson=rson=t[x].tag=t[x].rev=0;
}
inline int split(int k,int tot)
{
    int l=find_kth(k-1);
    int r=find_kth(k+tot);
    splay(l,0),splay(r,root);
    return t[r].son[0];
}
inline int sum_query(int k,int tot)
{
    if(tot==0)return 0;
    int x=split(k,tot);
    return t[x].sum;
}
inline void modify(int k,int tot,int z)
{
    int x=split(k,tot);
    t[x].val=z,t[x].sum=t[x].size*z,t[x].tag=true;
    if(z>=0)t[x].lm=t[x].rm=t[x].mm=t[x].sum;
    else t[x].lm=t[x].rm=0,t[x].mm=t[x].val;
    update(t[x].fa),update(root);
}
inline void reserve(int k,int tot)
{
    int x=split(k,tot);
    if(t[x].tag)return;
    t[x].rev^=1;
    myswap(t[x].lm,t[x].rm);
    myswap(lson,rson);
    update(t[x].fa),update(root);
}
inline void destory(int k,int tot)
{
    int x=split(k,tot);
    int y=t[x].fa;
    t[y].son[0]=0;
    t[x].fa=0;
    recycle(x);
    update(y),update(root);
}
inline int build(int l,int r,int fa)
{
    if(l>r)return 0;
    int mid=(l+r)>>1,now=0;
    if(top)now=stack[top--];
    else now=++tot;
    t[now].fa=fa;
    t[now].size=1;
    t[now].sum=t[now].val=a[mid];
    t[now].tag=t[now].rev=0;
    t[now].son[0]=build(l,mid-1,now);
    t[now].son[1]=build(mid+1,r,now);
    update(now);
    return now;
}
inline void insert(int k,int tot)
{
    for(int i=1;i<=tot;i++)scanf("%d",&a[i]);
    int l=find_kth(k);
    int r=find_kth(k+1);
    splay(l,0),splay(r,root);
    t[r].son[0]=build(1,tot,r);
    update(r),update(root);
}
void print(int x)
{
    pushdown(x);
    if(lson)print(lson);
    cout<<t[x].val<<" ";
    if(rson)print(rson);
}

int main()
{
    scanf("%d%d",&n,&m);
    t[0].mm=a[1]=a[n+2]=-inf;
    for(int i=2;i<=n+1;i++)scanf("%d",&a[i]);
    root=build(1,n+2,0);
    for(int i=1;i<=m;i++)
    {
        char op[10];
        int k=0,tot=0;
        cin>>op;
        if(op[0]=='I')
        {
            scanf("%d %d",&k,&tot);
            insert(k+1,tot);
        }
        else if(op[0]=='D')
        {
            scanf("%d %d",&k,&tot);
            destory(k+1,tot);
        }
        else if(op[0]=='R')
        {
            scanf("%d %d",&k,&tot);
            reserve(k+1,tot);
        }
        else if(op[0]=='G')
        {
            scanf("%d %d",&k,&tot);
            printf("%d\n",sum_query(k+1,tot));
        }
        else if(op[5]=='S')
        {
            int c=0;
            scanf("%d %d %d",&k,&tot,&c);
            modify(k+1,tot,c);
        }
        else 
        {
            printf("%d\n",t[root].mm);
        }
    }
}

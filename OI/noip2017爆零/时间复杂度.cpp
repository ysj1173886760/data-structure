#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
char yi[10],er[10],san[10],si[10];
int stack[105];
int target,top,ans,flag,sum;
char fuzadu[10];
bool is_err;
bool rec[105];
void ERR(int x)
{
    char temp[10];
    for(int i=1;i<=x;i++)
    {
        scanf("%s",temp);
        if(temp[0]=='F')
            for(int j=1;j<=3;j++)scanf("%s",temp);
    }
    printf("ERR\n");
}
bool check(int x)
{
    for(int i=1;i<=top;i++)
        if(stack[i]==x)return false;
    return true;
}
int tran(char *s)
{
    if(s[0]=='n')return 1000;
    int sum=0,len=strlen(s);
    for(int i=0;i<len;i++)sum=sum*10+s[i]-'0';
    return sum;
}
void solve()
{
    memset(rec,0,sizeof(rec));
    int line=0;																//这一部分是初始化
    top=0,ans=0,sum=0,target=0;	
    flag=99999;
    scanf("%d",&line);
    scanf("%s",fuzadu);
    int len=strlen(fuzadu); 
    if(fuzadu[0]=='O'&&fuzadu[1]=='('&&fuzadu[2]=='1'&&fuzadu[3]==')')target=0;												//目标复杂度
    else for(int i=0;i<len;i++)
    {
        if(fuzadu[i]>='0'&&fuzadu[i]<='9')target=target*10+(fuzadu[i]-'0');
    }
    for(int i=1;i<=line;i++)												//开始处理 
    {
        scanf("%s",yi);
        if(yi[0]=='F')															//如果当前这一行为循环开始 
        {
            scanf("%s %s %s",er,san,si);
            int temp=er[0]-'a';
            if(!check(temp))												//判断有无重复定义的变量 
            {
                ERR(line-i);
                return;
            }
            top++;															//把当前变量压入栈内
            stack[top]=temp;																					
            int x=0,y=0;													
            x=tran(san);
            y=tran(si);
            if(x==y)
            {
                rec[top]=false;
                continue;
            }
            if(x>y)													//如果当前循环不能进入，那么之后的复杂度都不会造成贡献 ，但是需要判断是否有语法错误，所以有一个flag数组配合栈进行判断 
            {
                flag=min(flag,top);
                rec[top]=false;
                continue;
            }
            if(y-x>500&&top<=flag)
            {
                sum++;
                ans=max(ans,sum);
                rec[top]=true;
                continue;
            }
            if(y>x)
            {
                rec[top]=false;
                continue;
            }
        }
        else 																//如果是E的话就退栈； 
        {
            if(rec[top])sum--;
            top--;
            if(top<0)
            {
                ERR(line-i);
                return;
            }
            if(top<=flag)flag=99999;
        }
    }
    if(top>0)printf("ERR\n");
    else if(ans==target)printf("Yes\n");
    else printf("No\n");
} 
int main()
{
    int t=0;
    scanf("%d",&t);
    while(t--)solve();
}

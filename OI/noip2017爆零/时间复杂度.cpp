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
    int line=0;																//��һ�����ǳ�ʼ��
    top=0,ans=0,sum=0,target=0;	
    flag=99999;
    scanf("%d",&line);
    scanf("%s",fuzadu);
    int len=strlen(fuzadu); 
    if(fuzadu[0]=='O'&&fuzadu[1]=='('&&fuzadu[2]=='1'&&fuzadu[3]==')')target=0;												//Ŀ�긴�Ӷ�
    else for(int i=0;i<len;i++)
    {
        if(fuzadu[i]>='0'&&fuzadu[i]<='9')target=target*10+(fuzadu[i]-'0');
    }
    for(int i=1;i<=line;i++)												//��ʼ���� 
    {
        scanf("%s",yi);
        if(yi[0]=='F')															//�����ǰ��һ��Ϊѭ����ʼ 
        {
            scanf("%s %s %s",er,san,si);
            int temp=er[0]-'a';
            if(!check(temp))												//�ж������ظ�����ı��� 
            {
                ERR(line-i);
                return;
            }
            top++;															//�ѵ�ǰ����ѹ��ջ��
            stack[top]=temp;																					
            int x=0,y=0;													
            x=tran(san);
            y=tran(si);
            if(x==y)
            {
                rec[top]=false;
                continue;
            }
            if(x>y)													//�����ǰѭ�����ܽ��룬��ô֮��ĸ��Ӷȶ�������ɹ��� ��������Ҫ�ж��Ƿ����﷨����������һ��flag�������ջ�����ж� 
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
        else 																//�����E�Ļ�����ջ�� 
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

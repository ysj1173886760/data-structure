#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;
char s1[30],s2[30],s3[30];
int n;
bool vis[30];
int a[30];
void dfs(int x,int y,int next)
{
	//system("pause");
//	cout<<x<<" "<<y<<endl;
	for(int i=1;i<=y;i++)
	{
		int temp1=a[s1[i]-'A'];
		int temp2=a[s2[i]-'A'];
		int temp3=a[s3[i]-'A'];
		if(temp1==-1||temp2==-1||temp3==-1)continue;
		if((temp1+temp2+1)%n!=temp3&&(temp1+temp2)%n!=temp3)return;
	}
	if(y==0)
	{
		for(int i=0;i<n;i++)cout<<a[i]<<" ";
		exit(0);
	}
	if(x==1)
	{
		if(a[s1[y]-'A']!=-1)
		{
			dfs(2,y,next);
			return;
		}
		else 
			for(int i=n-1;i>=0;i--)
				if(!vis[i])
				{
					vis[i]=true;
					a[s1[y]-'A']=i;
					dfs(x+1,y,next);
					vis[i]=false;
					a[s1[y]-'A']=-1;
				}
			return;
	}
	int temp1=a[s1[y]-'A'];
	int temp2=a[s2[y]-'A'];
	int temp3=a[s3[y]-'A'];
	if(temp2!=-1)
	{
		if(temp3==-1)
		{
			int sum=temp1+temp2+next;
			int c=sum%n;
			vis[c]=true;
			a[s3[y]-'A']=c;
			dfs(1,y-1,sum/n);
			vis[c]=false;
			a[s3[y]-'A']=-1;
			return;
		}
		else 
		{
			int sum=temp1+temp2+next;
			if(sum%n==temp3)dfs(1,y-1,sum/n);
			return;
		}
	}
	else 
	{
		for(int i=n-1;i>=0;i--)
			if(!vis[i])
			{
				int sum=temp1+i+next;
				if((sum%n!=temp3&&temp3!=-1)||(temp3==-1&&vis[sum%n]))continue;
				if(temp3==-1)
				{
					vis[i]=true;
					a[s2[y]-'A']=i;
					vis[sum%n]=true;
					a[s3[y]-'A']=sum%n;
					dfs(1,y-1,sum/n);
					vis[i]=false;
					a[s2[y]-'A']=-1;
					vis[sum%n]=false;
					a[s3[y]-'A']=-1;
				}
				else 
				{
					vis[i]=true;
					a[s2[y]-'A']=i;
					dfs(1,y-1,sum/n);
					vis[i]=false;
					a[s2[y]-'A']=-1;
				}
			}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s1[i];
	for(int i=1;i<=n;i++)cin>>s2[i];
	for(int i=1;i<=n;i++)cin>>s3[i];
	for(int i=0;i<n;i++)a[i]=-1;
	dfs(1,n,0);
	return 0;
}

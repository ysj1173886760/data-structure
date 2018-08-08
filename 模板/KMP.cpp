#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=1e6+50;
char s1[maxn],s2[maxn];
int nxt[maxn];
int main()
{
	scanf("%s %s",s1+1,s2+1);
	int l1=strlen(s1+1),l2=strlen(s2+1);
	for(int i=2,j=0;i<=l2;i++)
	{
		for(;j&&s2[j+1]!=s2[i];j=nxt[j]);
		j+=(s2[j+1]==s2[i]);nxt[i]=j;
	}
	for(int i=1,j=0;i<=l1;i++)
	{
		for(;j&&s2[j+1]!=s1[i];j=nxt[j]);
		j+=(s2[j+1]==s1[i]);
		if(j==l2)cout<<i-l2+1<<endl,j=nxt[j];
	}
	for(int i=1;i<=l2;i++)cout<<nxt[i]<<" ";
	return 0;
}

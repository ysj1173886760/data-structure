#include<iostream>			//����ע�⣬���������Ż��Ķ��ر���������������Ϊ�����п��ܴ�dp[0]ת�����ġ� 
using namespace std;
const int maxv=1e5,maxn=1e5;
int dp[maxv],vq[maxn],q[maxn];
int n,m;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
    	int w=0,v=0,s=0;		//��ʡ�ռ� 
    	cin>>v>>w>>s;
    	for(int d=0;d<w;d++)
    	{
    		int h=1,t=0;
    		for(int j=0;d+j*w<=m;j++)
    		{
    			int val=dp[d+j*w]-j*v;	//�Ż����� 
    			while(h<=t&&vq[t]<=val)t--;//Ϊ���ֵ����Գ��� 
    			q[++t]=j,vq[t]=val;	//��� 
				if(q[h]+s<j)h++;//���ֶ��г��� 
    			dp[d+j*w]=vq[h]+j*v;//dp
    		}
    	}
    }
   	cout<<dp[m];
    return 0;
}

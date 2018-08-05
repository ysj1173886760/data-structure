#include<iostream>			//这里注意，单调队列优化的多重背包不是满包，因为都是有可能从dp[0]转移来的。 
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
    	int w=0,v=0,s=0;		//节省空间 
    	cin>>v>>w>>s;
    	for(int d=0;d<w;d++)
    	{
    		int h=1,t=0;
    		for(int j=0;d+j*w<=m;j++)
    		{
    			int val=dp[d+j*w]-j*v;	//优化常数 
    			while(h<=t&&vq[t]<=val)t--;//为保持单调性出队 
    			q[++t]=j,vq[t]=val;	//入队 
				if(q[h]+s<j)h++;//保持队列长度 
    			dp[d+j*w]=vq[h]+j*v;//dp
    		}
    	}
    }
   	cout<<dp[m];
    return 0;
}

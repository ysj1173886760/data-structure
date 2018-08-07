//推式子：
//对于一般的多重背包，我们有：dp[i][j]=max{dp[i-1][j-k*w[i]]+k*v[i]}   其中k满足：{0<=k<=(sum[i],j/w[i])} 
//对于状态转移方程形如dp[i]=max{dp[j]}+val，都可以用rmq来解决，多重背包比较特殊，满足range width 为定值，那么我们就可以使用单调队列进行优化。 
//首先转换一下dp方程,这里可以找一下规律，假设w和v都是1，那么dp[5]=max{dp[4]+1,dp[3]+2,dp[2]+3},发现里外加起来满足j，我们对于每个式子都减去 j*v[i]，则转换为 
//dp[i][j]=max{dp[i-1][j-k*w[i]]-k*v[i]}+j*v[i],这样我们就可以使用单调队列进行优化了。 
//至于后效性的话也是很显然的，我们先取了dp值压入队中再进行的dp，每个点只会入队一次，也就只会被更新一次，而用来更新的值是队列中的还未被更新的值，所以使用滚动数组即可。可以理解为队列代替的滚动数组。 
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

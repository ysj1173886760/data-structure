//��ʽ�ӣ�
//����һ��Ķ��ر����������У�dp[i][j]=max{dp[i-1][j-k*w[i]]+k*v[i]}   ����k���㣺{0<=k<=(sum[i],j/w[i])} 
//����״̬ת�Ʒ�������dp[i]=max{dp[j]}+val����������rmq����������ر����Ƚ����⣬����range width Ϊ��ֵ����ô���ǾͿ���ʹ�õ������н����Ż��� 
//����ת��һ��dp����,���������һ�¹��ɣ�����w��v����1����ôdp[5]=max{dp[4]+1,dp[3]+2,dp[2]+3},�����������������j�����Ƕ���ÿ��ʽ�Ӷ���ȥ j*v[i]����ת��Ϊ 
//dp[i][j]=max{dp[i-1][j-k*w[i]]-k*v[i]}+j*v[i],�������ǾͿ���ʹ�õ������н����Ż��ˡ� 
//���ں�Ч�ԵĻ�Ҳ�Ǻ���Ȼ�ģ�������ȡ��dpֵѹ������ٽ��е�dp��ÿ����ֻ�����һ�Σ�Ҳ��ֻ�ᱻ����һ�Σ����������µ�ֵ�Ƕ����еĻ�δ�����µ�ֵ������ʹ�ù������鼴�ɡ��������Ϊ���д���Ĺ������顣 
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

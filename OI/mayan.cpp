#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;
int n,sum[11];
int map[6][8];
bool vis[6][8],mark[6][8];
struct daan								//这个是记录答案的结构体 
{
	int x,y,op;							//op为操作，operator 
}ans[6];
inline void myswap(int &a,int &b)		//自己写的交换函数，当然可以a^=b^=a^=b;QAQ 
{
	int temp=a;
	a=b;
	b=temp;
}
void fall(int i,int j)					//这是是下降函数，找到下面为空的方块时就让他下降，递归处理 
{
	if(j==1)return;
	if(!map[i][j-1])
	{
		swap(map[i][j],map[i][j-1]);
		fall(i,j-1);
	}
}
void findlie(int x,int y)				//这个函数和下面那个函数作用是一样的，目的是找到可以消除的序列，这个是找列 
{
	int lietot=0;
	int l=y,r=y;						//这里注意x和y是反得，所以参数是给在了第二位，因为我们将整个图翻转了90度，那个(0,0)点在图中应该是(1,1) 
	while(map[x][y]==map[x][l])l--,lietot++;//l和r代表我们要找的那一列中满足消除条件的范围，只要满足条件，就扩大这个范围。 
	while(map[x][y]==map[x][r])r++,lietot++;
	lietot--;							//前面为了处理，这里不要忘记，两头都是从中间那个开始找的，第一步是重复的，所以要减1, 
	if(lietot>=3)						//只要满足了块数>=3这个条件说明 可以消除，那么我们给这些可以消除的块打上标记。 mark数组就是标记数组。被标记的就会消除。 
		for(int i=l+1;i<r;i++)mark[x][i]=true;
}
void find(int x,int y)					//和上面那个同理，就不一一解释了 
{
	int hangtot=0;
	int l=x,r=x;
	while(map[r][y]==map[x][y])r++,hangtot++;
	while(map[l][y]==map[x][y])l--,hangtot++;
	hangtot--;
	if(hangtot>=3)
		for(int i=l+1;i<r;i++)mark[i][y]=true;
	for(int i=l+1;i<r;i++)findlie(i,y);	//这里是找列，找完这一行的方块，就找同一列的，必定是可以找出能消除的方块的，因为进入这个find函数的条件就是如此。 
}
void clear()							//把所有的需要消除的方块找出来之后，扫一遍图，消除方块 
{
	for(int i=1;i<=5;i++)
		for(int j=1;j<=7;j++)if(mark[i][j])map[i][j]=0;
}
void recall(int temp[][8])				//这里是回溯，把temp数组赋给map，就相当于普通dfs中的回溯了。 
{
	for(int i=1;i<=5;i++)
		for(int j=1;j<=7;j++)map[i][j]=temp[i][j];
}
void save(int temp[][8])				//这是保存，保存当前状态的函数，刷新图后这个图就代表了当前状态，我们把它保存在temp数组中，以便回溯。 
{
	for(int i=1;i<=5;i++)
		for(int j=1;j<=7;j++)temp[i][j]=map[i][j];
}
bool judge()							//这个是一个剪枝。判断是否有剩余颜色的块数为1或者2，这样就消除不了了，return即可。 
{
	for(int j=7;j>=1;j--)
		for(int i=1;i<=5;i++)sum[map[i][j]]++;//sum储存的就是当前颜色块的数量 
	for(int i=1;i<=10;i++)if(sum[i]==1||sum[i]==2)return false;
	return true;
}
bool check()							//判断是否完成游戏，即所有块都被消除。 
{
	int sum1=0;
	for(int j=7;j>=1;j--)
		for(int i=1;i<=5;i++)if(map[j][i])sum1++;
	if(sum1==0)return true;
	return false;
}
void print()							//这是我当时调试的一个函数，输出当前的状态，无视即可。 
{
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)cout<<map[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}
bool canclear(int i,int j)				//这个就是判断是否可以消除方块，就不用每次都调用find函数浪费时间了。只有return true才能调用find。 
{
	if(map[i][j]==map[i-1][j]&&map[i][j]==map[i+1][j]&&map[i+1][j]==map[i-1][j])return true;
	if(map[i][j-1]==map[i][j]&&map[i][j-1]==map[i][j+1]&&map[i][j+1]==map[i][j])return true;
	return false;
}
bool refresh()							//核心函数，刷新图。 
{
	bool flag=false,accept=false;		//accept表示是否能进行clear。flag的意义在下方。 
	memset(sum,0,sizeof(sum));
	memset(vis,0,sizeof(vis));
	memset(mark,0,sizeof(mark));
	for(int i=1;i<=5;i++)				//先下降。			 
		for(int j=2;j<=7;j++)
			if(map[i][j]&&(!map[i][j-1]))
			{
				fall(i,j);
				flag=true;
			}
	for(int i=1;i<=5;i++)
		for(int j=1;j<=7;j++)
		{
			if(map[i][j])				//如果非零。 
			{
				if(!vis[i][j])			//且没有遇到过..（其实这一步没有必要，完全可以省略，因为我上次写不是这个写法，所以用了vis。） 
				{
					vis[i][j]=true;
					if(canclear(i,j))	//判断是否满足清楚方块的条件。 
					{
						accept=true;	//条件满足。 
						flag=true;		//如果可以清除方块，那么flag为true，说明还有再进行refresh的可能，因为可能清除 后方块可以下落，又可能再一次满足了清除的条件，所以只要可以清除 方块，就要继续refresh。 
						find(i,j);		//找出需要清除的方块。 
					}
				}
			}
		}
	if(accept)clear();					//清楚方块。 
	if(flag)return true;				//可以就return true 
	else return false;
}
void dfs(int dep)
{
	while(refresh());					//当可以进行刷新，就刷新，直到不再有方块需要清除为止。 
	int temp[6][8];						//用作backtrack的数组，这里注意一定要是全局变量，否则也会像map一样，在下一个状态中被修改。 
	save(temp);
	if(dep==n+1)						//走了n步。 
	{
		if(check())
		{
			for(int i=1;i<dep;i++)cout<<ans[i].x-1<<" "<<ans[i].y-1<<" "<<ans[i].op<<endl;
			exit(0);
		}
		else return;
	}
	if(dep>n+1)return;				//大于n步就返回，其实没必要，因为上面是else return 
	if(!judge())return;				//剪枝。上面解释过。 
	for(int i=1;i<=5;i++)									//向右 
		for(int j=1;j<=7;j++)
		{
			if(!map[i][j])continue;							//零的话没有交换的意义。 
			if(i!=5&&map[i][j]!=map[i+1][j])				//如果是5的话向右不能移动。这里我认为如果向右是颜色相同的块的话就不要更换了，可能有的人会说可以浪费一步，但是我觉得这毕竟是个真实存在的游戏。就像植物大战僵尸的一关一样，交换相同的东西貌似是不行的。仅代表个人见解。 
			{
				myswap(map[i][j],map[i+1][j]);				//交换 
				ans[dep].x=i;								//记录答案 
				ans[dep].y=j;
				ans[dep].op=1;
				dfs(dep+1);									//搜 
				recall(temp);								//回溯 
			}
			if((map[i-1][j]==0)&&i!=1)						//这是向左，同理的。注意 只有为0时才向左，毕竟会有字典序更小的解出现， 
			{
				myswap(map[i][j],map[i-1][j]);
				ans[dep].x=i;
				ans[dep].y=j;
				ans[dep].op=-1;
				dfs(dep+1);
				recall(temp);
			}
		}
}
int main()
{
	cin>>n;
	for(int i=1;i<=5;i++)
	{
		int j=1,temp=0;
		cin>>temp;
		while(temp)
		{
			map[i][j]=temp;
			j++;
			cin>>temp;
		}
	}
	dfs(1);				//dfs即可，如果dfs中没有exit（），说明无解，输出-1即可。 
	cout<<"-1";
/*	for(int i=1;i<=n;i++)cin>>ans[i].x>>ans[i].y>>ans[i].op;
	for(int i=1;i<=n;i++)
	{
		print();
		swap(map[ans[i].x+1][ans[i].y+1],map[ans[i].x+1+ans[i].op][ans[i].y+1]);
		while(refresh());
		print();
	}*/
	return 0;
}

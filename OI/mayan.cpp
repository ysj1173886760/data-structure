#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;
int n,sum[11];
int map[6][8];
bool vis[6][8],mark[6][8];
struct daan								//����Ǽ�¼�𰸵Ľṹ�� 
{
	int x,y,op;							//opΪ������operator 
}ans[6];
inline void myswap(int &a,int &b)		//�Լ�д�Ľ�����������Ȼ����a^=b^=a^=b;QAQ 
{
	int temp=a;
	a=b;
	b=temp;
}
void fall(int i,int j)					//�������½��������ҵ�����Ϊ�յķ���ʱ�������½����ݹ鴦�� 
{
	if(j==1)return;
	if(!map[i][j-1])
	{
		swap(map[i][j],map[i][j-1]);
		fall(i,j-1);
	}
}
void findlie(int x,int y)				//��������������Ǹ�����������һ���ģ�Ŀ�����ҵ��������������У���������� 
{
	int lietot=0;
	int l=y,r=y;						//����ע��x��y�Ƿ��ã����Բ����Ǹ����˵ڶ�λ����Ϊ���ǽ�����ͼ��ת��90�ȣ��Ǹ�(0,0)����ͼ��Ӧ����(1,1) 
	while(map[x][y]==map[x][l])l--,lietot++;//l��r��������Ҫ�ҵ���һ�����������������ķ�Χ��ֻҪ���������������������Χ�� 
	while(map[x][y]==map[x][r])r++,lietot++;
	lietot--;							//ǰ��Ϊ�˴������ﲻҪ���ǣ���ͷ���Ǵ��м��Ǹ���ʼ�ҵģ���һ�����ظ��ģ�����Ҫ��1, 
	if(lietot>=3)						//ֻҪ�����˿���>=3�������˵�� ������������ô���Ǹ���Щ���������Ŀ���ϱ�ǡ� mark������Ǳ�����顣����ǵľͻ������� 
		for(int i=l+1;i<r;i++)mark[x][i]=true;
}
void find(int x,int y)					//�������Ǹ�ͬ���Ͳ�һһ������ 
{
	int hangtot=0;
	int l=x,r=x;
	while(map[r][y]==map[x][y])r++,hangtot++;
	while(map[l][y]==map[x][y])l--,hangtot++;
	hangtot--;
	if(hangtot>=3)
		for(int i=l+1;i<r;i++)mark[i][y]=true;
	for(int i=l+1;i<r;i++)findlie(i,y);	//���������У�������һ�еķ��飬����ͬһ�еģ��ض��ǿ����ҳ��������ķ���ģ���Ϊ�������find����������������ˡ� 
}
void clear()							//�����е���Ҫ�����ķ����ҳ���֮��ɨһ��ͼ���������� 
{
	for(int i=1;i<=5;i++)
		for(int j=1;j<=7;j++)if(mark[i][j])map[i][j]=0;
}
void recall(int temp[][8])				//�����ǻ��ݣ���temp���鸳��map�����൱����ͨdfs�еĻ����ˡ� 
{
	for(int i=1;i<=5;i++)
		for(int j=1;j<=7;j++)map[i][j]=temp[i][j];
}
void save(int temp[][8])				//���Ǳ��棬���浱ǰ״̬�ĺ�����ˢ��ͼ�����ͼ�ʹ����˵�ǰ״̬�����ǰ���������temp�����У��Ա���ݡ� 
{
	for(int i=1;i<=5;i++)
		for(int j=1;j<=7;j++)temp[i][j]=map[i][j];
}
bool judge()							//�����һ����֦���ж��Ƿ���ʣ����ɫ�Ŀ���Ϊ1����2�����������������ˣ�return���ɡ� 
{
	for(int j=7;j>=1;j--)
		for(int i=1;i<=5;i++)sum[map[i][j]]++;//sum����ľ��ǵ�ǰ��ɫ������� 
	for(int i=1;i<=10;i++)if(sum[i]==1||sum[i]==2)return false;
	return true;
}
bool check()							//�ж��Ƿ������Ϸ�������п鶼�������� 
{
	int sum1=0;
	for(int j=7;j>=1;j--)
		for(int i=1;i<=5;i++)if(map[j][i])sum1++;
	if(sum1==0)return true;
	return false;
}
void print()							//�����ҵ�ʱ���Ե�һ�������������ǰ��״̬�����Ӽ��ɡ� 
{
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)cout<<map[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}
bool canclear(int i,int j)				//��������ж��Ƿ�����������飬�Ͳ���ÿ�ζ�����find�����˷�ʱ���ˡ�ֻ��return true���ܵ���find�� 
{
	if(map[i][j]==map[i-1][j]&&map[i][j]==map[i+1][j]&&map[i+1][j]==map[i-1][j])return true;
	if(map[i][j-1]==map[i][j]&&map[i][j-1]==map[i][j+1]&&map[i][j+1]==map[i][j])return true;
	return false;
}
bool refresh()							//���ĺ�����ˢ��ͼ�� 
{
	bool flag=false,accept=false;		//accept��ʾ�Ƿ��ܽ���clear��flag���������·��� 
	memset(sum,0,sizeof(sum));
	memset(vis,0,sizeof(vis));
	memset(mark,0,sizeof(mark));
	for(int i=1;i<=5;i++)				//���½���			 
		for(int j=2;j<=7;j++)
			if(map[i][j]&&(!map[i][j-1]))
			{
				fall(i,j);
				flag=true;
			}
	for(int i=1;i<=5;i++)
		for(int j=1;j<=7;j++)
		{
			if(map[i][j])				//������㡣 
			{
				if(!vis[i][j])			//��û��������..����ʵ��һ��û�б�Ҫ����ȫ����ʡ�ԣ���Ϊ���ϴ�д�������д������������vis���� 
				{
					vis[i][j]=true;
					if(canclear(i,j))	//�ж��Ƿ������������������� 
					{
						accept=true;	//�������㡣 
						flag=true;		//�������������飬��ôflagΪtrue��˵�������ٽ���refresh�Ŀ��ܣ���Ϊ������� �󷽿�������䣬�ֿ�����һ�����������������������ֻҪ������� ���飬��Ҫ����refresh�� 
						find(i,j);		//�ҳ���Ҫ����ķ��顣 
					}
				}
			}
		}
	if(accept)clear();					//������顣 
	if(flag)return true;				//���Ծ�return true 
	else return false;
}
void dfs(int dep)
{
	while(refresh());					//�����Խ���ˢ�£���ˢ�£�ֱ�������з�����Ҫ���Ϊֹ�� 
	int temp[6][8];						//����backtrack�����飬����ע��һ��Ҫ��ȫ�ֱ���������Ҳ����mapһ��������һ��״̬�б��޸ġ� 
	save(temp);
	if(dep==n+1)						//����n���� 
	{
		if(check())
		{
			for(int i=1;i<dep;i++)cout<<ans[i].x-1<<" "<<ans[i].y-1<<" "<<ans[i].op<<endl;
			exit(0);
		}
		else return;
	}
	if(dep>n+1)return;				//����n���ͷ��أ���ʵû��Ҫ����Ϊ������else return 
	if(!judge())return;				//��֦��������͹��� 
	for(int i=1;i<=5;i++)									//���� 
		for(int j=1;j<=7;j++)
		{
			if(!map[i][j])continue;							//��Ļ�û�н��������塣 
			if(i!=5&&map[i][j]!=map[i+1][j])				//�����5�Ļ����Ҳ����ƶ�����������Ϊ�����������ɫ��ͬ�Ŀ�Ļ��Ͳ�Ҫ�����ˣ������е��˻�˵�����˷�һ���������Ҿ�����Ͼ��Ǹ���ʵ���ڵ���Ϸ������ֲ���ս��ʬ��һ��һ����������ͬ�Ķ���ò���ǲ��еġ���������˼��⡣ 
			{
				myswap(map[i][j],map[i+1][j]);				//���� 
				ans[dep].x=i;								//��¼�� 
				ans[dep].y=j;
				ans[dep].op=1;
				dfs(dep+1);									//�� 
				recall(temp);								//���� 
			}
			if((map[i-1][j]==0)&&i!=1)						//��������ͬ��ġ�ע�� ֻ��Ϊ0ʱ�����󣬱Ͼ������ֵ����С�Ľ���֣� 
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
	dfs(1);				//dfs���ɣ����dfs��û��exit������˵���޽⣬���-1���ɡ� 
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

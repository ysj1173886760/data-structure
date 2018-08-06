bit[]
void add(int x,int z)
{
	for(int i=x;i<=n;i+=lowbit(i))bit[i]+=z;
}
void rank(int x)				
{
	int ans=0;
	for(int i=x-1;i;i-=lowbit(i))ans+=bit[i];
	return ans+1;									//ͬ���ֹ��ͬԪ�صĸ��� 
}
int find_range_kth(int k)
{
	int ans=0,now=0;
	for(int i=log2(n);i>=0;i--)
	{
		ans+=(1<<i);
		if(ans>n||now+bit[ans]>=k)ans-=(1<<i);		///���ڵ���k�����þ��Ƿ�ֹ�ظ�Ԫ�ء��������k�ڳ����ظ�Ԫ�ص�����¾ͻ���� 
		else now+=bit[ans];
	}
	return ans+1;
}
int pre(int x)
{
	return find_range_kth(rank(x)-1);
}
int next(int x)
{
	return find_range_kth(rank(x+1));
}

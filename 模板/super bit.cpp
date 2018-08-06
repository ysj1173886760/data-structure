bit[]
void add(int x,int z)
{
	for(int i=x;i<=n;i+=lowbit(i))bit[i]+=z;
}
void rank(int x)				
{
	int ans=0;
	for(int i=x-1;i;i-=lowbit(i))ans+=bit[i];
	return ans+1;									//同理防止相同元素的干扰 
}
int find_range_kth(int k)
{
	int ans=0,now=0;
	for(int i=log2(n);i>=0;i--)
	{
		ans+=(1<<i);
		if(ans>n||now+bit[ans]>=k)ans-=(1<<i);		///大于等于k的作用就是防止重复元素。如果大于k在出现重复元素的情况下就会出错 
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

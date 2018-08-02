//权值bit   
bit[];
int find_range_kth(int k)
{
	int ans=0,now=0;
	for(int i=log2(n);i>=0;i--)
	{
		ans+=(1<<i);
		if(ans>n||now+bit[ans]>=k)ans-=(1<<i);		///大于等于k的作用就是防止重复元素。如果大于k在出现重复元素的情况下就会出错 
		else cnt+=c[ans];
	}
	return ans++
}

int lowbit(const int &x){return x& -x;}
void init()
{
	for(int i=1;i<=n;i++)
	{
		bit[i]=a[i];
		for(int j=1;j<lowbit(i);j<<=1)
		{
			bit[i]=max(bit[i],bit[i-j]);
		}
	}
}
int query(int l,int r)
{
	int ans=0;
	while(l<=r)
	{
		ans=max(ans,a[r]);
		for(r-=1;r-l>=lowbit(r);r-=lowbit(r))ans=max(ans,bit[r]);			//�����r-l+1�����ܹ�ֱ������0���������0������ѭ������һ���Ĳ�����logn�ģ� ÿ����Ҫ-1��ÿ��for�ѵ�λ��lowbit���꣬Ȼ��r-1�ø�λ-1������logn�Ρ� 
	}
	return ans;
}
void modify(int x,int z)
{
	a[x]=z,bit[x]=z;
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=1;j<lowbit(i);j<<=1)bit[i]=max(bit[i],bit[i-j]);
}


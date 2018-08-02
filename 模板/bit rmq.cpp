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
		for(r-=1;r-l>=lowbit(r);r-=lowbit(r))ans=max(ans,bit[r]);			//如果是r-l+1会在能够直接跳到0的情况下跳0导致死循环。这一步的操作是logn的， 每次又要-1，每次for把低位的lowbit跳完，然后r-1让高位-1，最多减logn次。 
	}
	return ans;
}
void modify(int x,int z)
{
	a[x]=z,bit[x]=z;
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=1;j<lowbit(i);j<<=1)bit[i]=max(bit[i],bit[i-j]);
}


//p为质数 
//线性递推逆元
inv[]
void solve()
{
	inv[1]=1;
	for(int i=2;i<=n;i++)inv[i]=1ll*(p-p/i)*inv[p%i]%p;		//注意乘个1ll，不然没准会溢出 
} 

//费马小定理求逆元    快速幂 
int fpow(int x,int y,int mod)
{
	int ans=1;
	while(y)
	{
		if(y&1)ans=1ll*ans*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ans;
}
void solve()
{
	for(int i=1;i<=n;i++)inv[i]=fpow(i,p-2,p);
}

//扩展欧几里得算法求逆元 
void exgcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=(a/b)*x*1ll;
}

void solve()
{
	for(int i=1;i<=n;i++)
	{
		int x=0,y=0;
		exgcd(i,p,x,y);
		inv[i]=(x+p)%p;
	}
}

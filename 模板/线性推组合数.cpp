//线性推组合数 O(n)预处理 O(1)询问    a为阶乘，b为逆元前缀积   x*b[x]=b[x-1],,,inv[x]=b[x]*a[x-1]
a[],b[],mod;
void init()
{
	for(int i=1;i<=n;i++)a[i]=1ll*i*a[i-1]%mod;
	b[n]=fpow(a[n],mod-2);
	for(int i=n-1;i>=1;i--)b[i]=1ll*i*b[i+1]%mod;
} 
int c(int x,int y)
{
	return 1ll*a[x]*b[y]*b[x-y]%mod;
}
int lucas(int x,int y)
{
	if(x<=mod&&y<=mod)return c(x,y);
	else return 1ll*c(x/mod,y/mod)*(x%mod,y%mod);
}

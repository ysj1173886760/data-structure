#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=1e5+10;

int n;
int a[maxn];
long long ans;

int main()
{
//	freopen("road.in","r",stdin);
//	freopen("road.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)if(a[i]>a[i-1])ans+=a[i]-a[i-1];
    printf("%lld",ans);
    return 0;
}
